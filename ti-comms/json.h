//#include <ArduinoJson.h>
//
//StaticJsonDocument<8 * JSON_OBJECT_SIZE(8)> getJSON(String);
//StaticJsonDocument<8 * JSON_OBJECT_SIZE(8)> postJSON(String, StaticJsonDocument<8 * JSON_OBJECT_SIZE(8)>);
String getMsg(String, String);
bool sendMsg(String, String, String);
