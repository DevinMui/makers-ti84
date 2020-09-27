// GET request
void getText() {
  HTTPClient http;
  http.begin(URL);
  int code = http.GET();
  Serial.print("Printing response: ");
  Serial.println(http.getString());
  http.end();
}

void postText(String message) {
  // POST request
  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "text/plain");
  http.POST(message);
  Serial.print("Printing response: ");
  Serial.println(http.getString());
  http.end();
}
