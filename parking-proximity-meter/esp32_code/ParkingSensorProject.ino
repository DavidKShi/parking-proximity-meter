#include <WiFi.h>
#include <WebServer.h>

// ===== WIFI =====
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ===== PINS =====
#define TRIG_PIN 13
#define ECHO_PIN 27
#define BUZZER_PIN 26

#define RED_LED_PIN 25
#define YELLOW_LED_PIN 33
#define GREEN_LED_PIN 32

// ===== THRESHOLDS =====
#define WARNING_DISTANCE 25
#define DANGER_DISTANCE 10

WebServer server(80);

// Global distance
long distance = 0;

// ===== HTML PAGE (LIVE DASHBOARD) =====
String getHTML() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Parking Sensor Meter</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">

  <style>
    body {
      font-family: Arial;
      text-align: center;
      background: #111;
      color: white;
    }

    h1 {
      margin-top: 20px;
    }

    .distance {
      font-size: 90px;
      margin: 20px;
    }

    .status {
      font-size: 40px;
      margin: 10px;
    }

    .bar-container {
      width: 80%;
      height: 40px;
      background: #333;
      margin: auto;
      border-radius: 20px;
      overflow: hidden;
    }

    .bar {
      height: 100%;
      width: 0%;
      background: green;
      transition: width 0.2s, background 0.2s;
    }
  </style>
</head>

<body>
  <h1>Parking Sensor Meter</h1>

  <div class="distance" id="dist">--</div>
  <div class="status" id="status">--</div>

  <div class="bar-container">
    <div class="bar" id="bar"></div>
  </div>

<script>
async function updateData() {
  try {
    const res = await fetch('/data');
    const data = await res.json();

    let d = data.distance;

    document.getElementById("dist").innerHTML = d + " cm";

    let status = "";
    let color = "green";

    if (d <= 10) {
      status = "DANGER";
      color = "red";
    } else if (d <= 25) {
      status = "WARNING";
      color = "orange";
    } else {
      status = "SAFE";
      color = "green";
    }

    document.getElementById("status").innerHTML = status;
    document.getElementById("status").style.color = color;

    let percent = Math.max(0, Math.min(100, 100 - d));

    document.getElementById("bar").style.width = percent + "%";
    document.getElementById("bar").style.background = color;

  } catch (err) {
    console.log("Error:", err);
  }
}

setInterval(updateData, 200);
updateData();
</script>

</body>
</html>
)rawliteral";

  return html;
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(YELLOW_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  // MAIN PAGE
  server.on("/", []() {
    server.send(200, "text/html", getHTML());
  });

  // LIVE DATA API
  server.on("/data", []() {
    String json = "{";
    json += "\"distance\":" + String(distance);
    json += "}";
    server.send(200, "application/json", json);
  });

  server.begin();
}

// ===== LOOP =====
void loop() {

  // Ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0344) / 2;

  // ===== LED + BUZZER LOGIC =====
  if (distance <= DANGER_DISTANCE) {

    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(80);
    digitalWrite(BUZZER_PIN, LOW);
    delay(80);

  } 
  else if (distance <= WARNING_DISTANCE) {

    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(BUZZER_PIN, HIGH);
    delay(400);
    digitalWrite(BUZZER_PIN, LOW);
    delay(400);

  } 
  else {

    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);

    digitalWrite(BUZZER_PIN, LOW);
  }

  server.handleClient();
  delay(50);
}