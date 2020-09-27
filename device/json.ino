#include "json.h"
#include <ArduinoJson.h>

// GET JSON
void getJSON() {
  HTTPClient http;
  String urlstr = URL;
  urlstr += "/json";
  http.begin(urlstr);
  int code = http.GET();
  Serial.print("Printing response: ");
  String res = http.getString();
  Serial.println(res);
  Serial.println();
  // Parse it!
  // Supposedly 4 objects with 2 members each (but doesn't work :P)
  const int capacity = 4 * JSON_OBJECT_SIZE(2);
  StaticJsonDocument<capacity> doc;
  DeserializationError e = deserializeJson(doc, res);
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
  } else {
    Serial.print("Printing parsed response: ");
    const char* message = doc["message"];
    Serial.println(message);
  }
  http.end();
}

// POST JSON
void postJSON(String message) {
  const int capacity = 4 * JSON_OBJECT_SIZE(2);
  StaticJsonDocument<capacity> doc;
  doc["message"] = message;
  String postStr;
  serializeJson(doc, postStr);
  Serial.println(postStr);

  HTTPClient http;
  String urlstr = URL;
  urlstr += "/json";
  http.begin(urlstr);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(postStr);
  Serial.print("Printing response: ");
  String res = http.getString();
  Serial.println(res);
  Serial.println();
  DeserializationError e = deserializeJson(doc, res);
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
  } else {
    Serial.print("Printing parsed response: ");
    const char* m = doc["message"];
    Serial.println(m);
  }
}
