Smart Parking Sensor System 
A real-time IoT-based parking assistance system built using an ESP32, ultrasonic sensor, LEDs, buzzer, and a live WiFi dashboard. This project helps drivers park safely by measuring the distance between a vehicle and obstacles, while providing both visual and audio alerts.

 Features
Real-time distance measurement using an ultrasonic sensor
 Live web dashboard hosted directly from the ESP32
 LED indicators for parking status
Green → Safe
Yellow → Warning
Red → Danger
Smart buzzer alert system
Slow beep in warning zone
Fast beep in danger zone
Mobile-friendly responsive dashboard
Fast live updates using JSON API + JavaScript fetch requests

Hardware Used
Component
Quantity
ESP32 Dev Board
1
HC-SR04 Ultrasonic Sensor
1
Buzzer
1
Red LED
1
Yellow LED
1
Green LED
1
Resistors
3
Breadboard + Jumper Wires
1 Set


Pin Configuration
Component
ESP32 Pin
Ultrasonic Trigger
GPIO 13
Ultrasonic Echo
GPIO 27
Buzzer
GPIO 26
Red LED
GPIO 25
Yellow LED
GPIO 33
Green LED
GPIO 32


System Logic
Distance Zones
Distance
Status
LEDs
Buzzer
> 25 cm
SAFE
Green ON
OFF
10–25 cm
WARNING
Yellow ON
Slow Beep
≤ 10 cm
DANGER
Red ON
Fast Beep


Web Dashboard
The ESP32 hosts a live dashboard accessible through any device connected to the same WiFi network.
Dashboard Features
Live distance display
Dynamic parking status
Animated progress bar
Real-time updates every 200ms
Responsive mobile UI

Getting Started
1️. Install Required Libraries
Install the following libraries in Arduino IDE:
WiFi.h
WebServer.h
These are included with the ESP32 board package.

2️. Install ESP32 Board Package
In Arduino IDE:
Go to:
 File → Preferences
Add this URL in Additional Boards Manager URLs:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
Open:
 Tools → Board → Boards Manager
Search for:
 ESP32
Install the package by Espressif Systems

3️. Configure WiFi Credentials
Inside the code, update:
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

4️. Upload the Code
Select your ESP32 board
Select the correct COM port
Upload the sketch

5️. Open the Dashboard
After upload, open the Serial Monitor at:
115200 baud
You will see:
Connected!
192.168.x.x
Open the displayed IP address in your browser to access the live dashboard.
How It Works
The HC-SR04 ultrasonic sensor measures object distance.
ESP32 processes the sensor data.
LEDs and a buzzer react based on distance thresholds.
ESP32 hosts a web server over WiFi.
Dashboard fetches live distance data from /data endpoint every 200ms.
Safety Notes
HC-SR04 works best in stable indoor environments
Avoid water exposure
Ensure correct ESP32 voltage compatibility
Use proper resistors for LEDs

Possible Applications
Smart parking systems
Garage parking assistant
Reverse parking aid
Obstacle detection
Robotics distance sensing
License
This project is licensed under the MIT License.

Author
Developed by David Shi



