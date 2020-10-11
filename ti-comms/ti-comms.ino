#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "credentials.h"
#include "json.h"
#include "CBL2.h"
#include "TIVar.h"

CBL2 cbl;
const int lineRed = DEFAULT_TIP;
const int lineWhite = DEFAULT_RING;

#define URL "http://f9e17b4a5712.ngrok.io"
#define MAXDATALEN 255

uint8_t header[16];
uint8_t data[MAXDATALEN];

// Forward declaration of onRequest() and onReceived() functions
int onReceived(uint8_t type, enum Endpoint model, int datalen);
int onRequest(uint8_t type, enum Endpoint model, int* headerlen,
              int* datalen, data_callback* data_callback);

// im bad with variable names
String myName = "";
String otherName = "";

void setup() {
    Serial.begin(115200);

    // setup WiFi

    WiFi.begin(WIFI_NAME, WIFI_PASS);
    Serial.println();
    Serial.print("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected at ");
    Serial.println(WiFi.localIP());

    sendMsg("devin", "some", "hello!");
    Serial.println(getMsg("devin", "some"));
    
    // set up connection with the TI 84
    cbl.setLines(lineRed, lineWhite);
    cbl.resetLines();
    // tell the lib to send data to functions
    cbl.setupCallbacks(header, data, MAXDATALEN, onReceived, onRequest);
}

void loop() {
    cbl.eventLoopTick();
}

// receive data from the TI 84 through string variable changes
// Send
int onReceived(uint8_t type, enum Endpoint model, int datalen) {
    if (type != VarTypes82::VarString) {
        Serial.println("Received invalid data type");
        return -1; // Can only accept strings
    }

    String str = TIVar::strVarToString8x(data, model);
    Serial.println(str.c_str());
    
    // check which one
    switch(str[0]) {
      // send your name
      case '0':
        myName = str.substring(1);
        break;
      // select person
      case '1':
        otherName = str.substring(1);
        break;
      // send msg
      case '2':
        sendMsg(myName, otherName, str.substring(1));
        break;
      default:
        break;
    }
    
    return 0;
}

// send data to the TI 84 when the TI 84 requests for data
// Get
int onRequest(uint8_t type, enum Endpoint model, int* headerlen,
              int* datalen, data_callback* data_callback)
{
    // error handling
    if (type != VarTypes82::VarString) {
        Serial.println("Received request for invalid data type");
        return -1; // Can only return strings
    }
    
    // receive message
    String msg = getMsg(otherName, myName);
    int val = TIVar::stringToStrVar8x(msg, data, model);
    if (val < 0) {
        return -1;
    }
    *datalen = val;

    // send message
    memset(header, 0, sizeof(header));
    TIVar::intToSizeWord(val, header);
    header[2] = VarTypes82::VarString; // Variable type
    header[3] = 0xAA; // Variable name (tVarStr)
    header[4] = 0x00; // ^ (tStr1)
    *headerlen = 13;

    return 0;
}
