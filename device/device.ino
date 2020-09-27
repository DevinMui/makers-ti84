#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "text.h"
#include "json.h"
#include "credentials.h"

#define URL "http://f4d5afdfbd82.ngrok.io"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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

  getText();
  postText("d");
//  getJSON();
//  postJSON("devin");
}

void loop() {
  // put your main code here, to run repeatedly:
}
