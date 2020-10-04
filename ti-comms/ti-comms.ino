/*************************************************
 *  HelloWorld.ino                               *
 *  Example from the ArTICL library              *
 *           Created by Alex Cordonnier, 2017    *
 *                                               *
 *  Use Get(Str1) to request a string from the   *
 *  Arduino. Use Send(Str1) to send a string to  *
 *  the Arduino.                                 *
 *************************************************/

#include "CBL2.h"
#include "TIVar.h"

CBL2 cbl;
const int lineRed = DEFAULT_TIP;
const int lineWhite = DEFAULT_RING;

#define MAXDATALEN 255

uint8_t header[16];
uint8_t data[MAXDATALEN];

// Forward declaration of onRequest() and onReceived() functions
int onReceived(uint8_t type, enum Endpoint model, int datalen);
int onRequest(uint8_t type, enum Endpoint model, int* headerlen,
              int* datalen, data_callback* data_callback);

void setup() {
    Serial.begin(115200);
    Serial.setTimeout(500);
    Serial.println("Opened serial");
    // set up connection with the TI 84
    cbl.setLines(lineRed, lineWhite);
    cbl.resetLines();
//    cbl.setVerbosity(true, &Serial);      // Comment this in for message information
    // tell the lib to send data to functions
    cbl.setupCallbacks(header, data, MAXDATALEN, onReceived, onRequest);
}

void loop() {
    cbl.eventLoopTick();
}

// receive data from the TI 84 through string variable changes
int onReceived(uint8_t type, enum Endpoint model, int datalen) {
    if (type != VarTypes82::VarString) {
        Serial.println("Received invalid data type");
        return -1; // Can only accept strings
    }

    String str = TIVar::strVarToString8x(data, model);
    Serial.println(str.c_str());
    // do stuff with the data
    return 0;
}

// send data to the TI 84 when the TI 84 requests for data
int onRequest(uint8_t type, enum Endpoint model, int* headerlen,
              int* datalen, data_callback* data_callback)
{
    // error handling
    if (type != VarTypes82::VarString) {
        Serial.println("Received request for invalid data type");
        return -1; // Can only return strings
    }
    
    // receive message
//    String hello = Serial.readString();
//    Serial.println(hello);
    String hello = "hello world!";
    int val = TIVar::stringToStrVar8x(hello, data, model);
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
