// messy code up ahead
// feel free to refactor

#include "json.h"
#include <ArduinoJson.h>
// random byte capacity
const int capacity = 8 * JSON_OBJECT_SIZE(8);

// GET JSON
StaticJsonDocument<capacity> getJSON(String uri) {
  HTTPClient http;
  String urlstr = URL;
  urlstr += uri;
  http.begin(urlstr);
  int code = http.GET();
  String res = http.getString();
  http.end();
  // Parse it!
  StaticJsonDocument<capacity> doc;
  DeserializationError e = deserializeJson(doc, res);
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
  }
  return doc;
}

// POST JSON
StaticJsonDocument<capacity> postJSON(String uri, StaticJsonDocument<capacity> doc) {
  // convert json -> str
  String postStr;
  serializeJson(doc, postStr);

  HTTPClient http;
  String urlstr = URL;
  urlstr += uri;
  http.begin(urlstr);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(postStr);  
  String res = http.getString();
  http.end();
  Serial.println("http end");
  StaticJsonDocument<capacity> newDoc;
  DeserializationError e = deserializeJson(newDoc, res);
  Serial.println("deserialize");
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
  }
  return newDoc;
}
//
//// from, to
//String getMsg(String sender, String receiver) {
//  String uri = "/from=" + sender + "&to=" + receiver;
//  StaticJsonDocument<capacity> doc = getJSON(uri);
//  String val = doc["msg"];
//  return val;
//}
//
//bool sendMsg(String sender, String receiver, String msg) {
//  String uri = "/messages";
//  StaticJsonDocument<capacity> doc;
//  doc["from"] = sender;
//  doc["to"] = receiver;
//  doc["msg"] = msg;
//  StaticJsonDocument<capacity> newDoc = postJSON(uri, doc);
//  return true;
//}

// from
// to
String getMsg(String sender, String receiver) {
  String uri = "/messages?from=" + sender + "&to=" + receiver;
  HTTPClient http;
  String urlstr = URL;
  urlstr += uri;
  http.begin(urlstr);
  int code = http.GET();
  String res = http.getString();
  http.end();
  // Parse it!
  StaticJsonDocument<capacity> doc;
  DeserializationError e = deserializeJson(doc, res);
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
  }
  String val = doc["msg"];
  return val;
}

bool sendMsg(String sender, String receiver, String msg) {
  String uri = "/messages";
  StaticJsonDocument<capacity> doc;
  doc["from"] = sender;
  doc["to"] = receiver;
  doc["msg"] = msg;
  // convert json -> str
  String postStr;
  serializeJson(doc, postStr);

  HTTPClient http;
  String urlstr = URL;
  urlstr += uri;
  http.begin(urlstr);
  http.addHeader("Content-Type", "application/json");
  int code = http.POST(postStr);  
  String res = http.getString();
  http.end();
  StaticJsonDocument<capacity> newDoc;
  DeserializationError e = deserializeJson(newDoc, res);
  if(e) {
    Serial.println("big F");
    Serial.println(e.c_str());
    return false;
  }
  return true;
}
