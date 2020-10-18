# Internet of Things TI-84

This project demonstrates how to connect a TI-84 to a ESP-8266 microcontroller to send HTTP requests to API services.

### Prerequisites

You'll need these softwares to run this project.

-   [Arduino IDE](https://www.arduino.cc/en/main/software)
-   [TI Connect](https://education.ti.com/en/products/computer-software/ti-connect-ce-sw)
-   [ArtiCl Library](https://github.com/KermMartian/ArTICL)
-   [ArduinoJson Library](https://arduinojson.org)
-   [ESP8266 Libraries](https://github.com/esp8266/Arduino)

### Running

#### Arduino

Open `ti-comms/ti-comms.ino` in the Arduino editor. Replace line 12 with:

```c
...
#define URL "http://ti.devinmui.com"
...
```

Or run the test server under the `test-server` directory and expose the web server to the public internet.

Create a new tab in the Arduino IDE with the `ti-comms.ino` open. Name it `credentials.h`. The contents of this file should include the WiFi name and password you intend the ESP8266 to connect to. Below is an example template:

```c
#define WIFI_NAME "<your wifi name>"
#define WIFI_PASS "<your wifi pass>"
```

Upload the sketch to the ESP8266. If the changes were successful, you should see a bunch of dots in the serial before it reports that it connected along with your device's private IP address.

#### TI-Basic

Open TI Connect. Click the three boxes icon on the side panel to open the Program Editor workspace. Click open program and select `cheat.8xp`. Upload the program.

On your TI-84, press the `PRGM` button and find the `CHEAT` program. Press ENTER to execute the program.

### Using

To use the program, after executing the TI-Basic program, connect the ESP8266 to the TI with the link cable. Enter your name and the recipient name on the TI-84. Hold ENTER to send text to the recipient.

### License

MIT License

Copyright (c) 2020 Devin Mui

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
