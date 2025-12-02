#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "RobotBot";
const char* password = "12345678";

ESP8266WebServer server(80);

// Motor Pins
#define MOTOR_A1 16
#define MOTOR_A2 4
#define MOTOR_B1 0
#define MOTOR_B2 2
#define PWM_A 5
#define PWM_B 3

// Ultrasonic Pins
#define FRONT_TRIG 15
#define FRONT_ECHO 13
#define LEFT_TRIG 14
#define LEFT_ECHO 12

int SPEED = 120;
int turnTime = 2800;
int moveTime = 1000;

float x = 0, y = 0;
int heading = 0;
bool trackingEnabled = false;
bool isTurning = false;

unsigned long lastMoveTime = 0;
unsigned long turnStartTime = 0;

const char htmlPage[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Robot Control UI</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <style>
    body { font-family: Arial; margin: 0; background: #f2f2f2; }
    h1 { text-align: center; background: #0f3057; color: white; padding: 1rem; }
    .container { display: flex; flex-wrap: wrap; justify-content: center; gap: 20px; padding: 20px; }
    .card {
      background: white;
      padding: 20px;
      border-radius: 15px;
      box-shadow: 0 0 15px rgba(0,0,0,0.2);
      width: 420px;
    }
    canvas { background: #e6e6e6; display: block; margin: auto; }
    button {
      background-color: #0f3057;
      color: white;
      border: none;
      padding: 15px 30px;
      margin: 10px;
      font-size: 16px;
      border-radius: 10px;
      cursor: pointer;
    }
    button:hover { background-color: #00587a; }
    .info { text-align: center; font-size: 18px; margin-top: 10px; }
  </style>
</head>
<body>
  <h1>Real-Time Robot Control</h1>
  <div class="container">
    <div class="card">
      <h2 style="text-align:center;">Radar System</h2>
      <canvas id="radar" width="400" height="400"></canvas>
      <div class="info">Front: <span id="front">0</span> cm | Left: <span id="left">0</span> cm</div>
    </div>
    <div class="card">
      <h2 style="text-align:center;">Pathway Tracker</h2>
      <canvas id="map" width="400" height="400"></canvas>
      <div class="info">X: <span id="x">0</span> cm | Y: <span id="y">0</span> cm</div>
    </div>
  </div>
  <div style="text-align:center;">
    <button onclick="start()">Start</button>
    <button onclick="stop()">Stop</button>
  </div>

<script>
let intervalId;
const radarCanvas = document.getElementById('radar');
const radarCtx = radarCanvas.getContext('2d');

const mapCanvas = document.getElementById('map');
const mapCtx = mapCanvas.getContext('2d');
let path = [];

function drawRadar(front, left) {
  radarCtx.clearRect(0, 0, 400, 400);
  radarCtx.beginPath();
  radarCtx.arc(200, 200, 180, 0, 2 * Math.PI);
  radarCtx.strokeStyle = '#333';
  radarCtx.stroke();

  drawRay(front, 0, 'red'); // front
  drawRay(left, 90, 'green'); // left
}

function drawRay(distance, angle, color) {
  let rad = angle * Math.PI / 180;
  let dx = Math.cos(rad) * distance * 4;
  let dy = Math.sin(rad) * distance * 4;

  radarCtx.beginPath();
  radarCtx.moveTo(200, 200);
  radarCtx.lineTo(200 + dx, 200 - dy);
  radarCtx.strokeStyle = color;
  radarCtx.lineWidth = 3;
  radarCtx.stroke();
}

function drawMap(x, y) {
  mapCtx.clearRect(0, 0, 400, 400);
  mapCtx.strokeStyle = '#ccc';
  for (let i = 0; i <= 400; i += 20) {
    mapCtx.beginPath(); mapCtx.moveTo(i, 0); mapCtx.lineTo(i, 400); mapCtx.stroke();
    mapCtx.beginPath(); mapCtx.moveTo(0, i); mapCtx.lineTo(400, i); mapCtx.stroke();
  }

  path.push({x, y});
  mapCtx.fillStyle = 'red';
  path.forEach(p => {
    mapCtx.fillRect(200 + p.x, 400 - p.y, 5, 5);
  });
}

function fetchData() {
  fetch('/data')
    .then(res => res.json())
    .then(data => {
      document.getElementById('x').innerText = data.x;
      document.getElementById('y').innerText = data.y;
      document.getElementById('front').innerText = data.front;
      document.getElementById('left').innerText = data.left;
      drawRadar(data.front, data.left);
      drawMap(data.x, data.y);
    });
}

function start() {
  fetch('/start');
  intervalId = setInterval(fetchData, 500);
}
function stop() {
  fetch('/stop');
  clearInterval(intervalId);
}
</script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_A1, OUTPUT); pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT); pinMode(MOTOR_B2, OUTPUT);
  pinMode(PWM_A, OUTPUT); pinMode(PWM_B, OUTPUT);
  pinMode(FRONT_TRIG, OUTPUT); pinMode(FRONT_ECHO, INPUT);
  pinMode(LEFT_TRIG, OUTPUT); pinMode(LEFT_ECHO, INPUT);

  WiFi.softAP(ssid, password);
  server.on("/", []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/start", []() {
    trackingEnabled = true;
    server.send(200, "text/plain", "started");
  });

  server.on("/stop", []() {
    trackingEnabled = false;
    stopBot();
    server.send(200, "text/plain", "stopped");
  });

  server.on("/data", []() {
    int front = getDistance(FRONT_TRIG, FRONT_ECHO);
    int left = getDistance(LEFT_TRIG, LEFT_ECHO);
    String json = "{";
    json += "\"x\":" + String(x) + ",";
    json += "\"y\":" + String(y) + ",";
    json += "\"front\":" + String(front) + ",";
    json += "\"left\":" + String(left) + "}";
    server.send(200, "application/json", json);
  });

  server.begin();
}

void loop() {
  server.handleClient();
  if (!trackingEnabled) return;

  unsigned long currentTime = millis();

  if (isTurning) {
    if (currentTime - turnStartTime >= turnTime) {
      stopBot();
      isTurning = false;
      lastMoveTime = currentTime;
    }
    return;
  }

  int frontDist = getDistance(FRONT_TRIG, FRONT_ECHO);
  int leftDist = getDistance(LEFT_TRIG, LEFT_ECHO);

  if ((frontDist > 0 && frontDist < 10) || (leftDist > 0 && leftDist < 10)) {
    stopBot();
    delay(1000);
    turnLeft();
    heading = (heading + 1) % 4;
    isTurning = true;
    turnStartTime = millis();
    return;
  }

  if (currentTime - lastMoveTime >= moveTime) {
    moveForward();
    delay(moveTime);
    updatePosition();
    stopBot();
    lastMoveTime = currentTime;
  }
}

void moveForward() {
  digitalWrite(MOTOR_A1, HIGH); digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, HIGH); digitalWrite(MOTOR_B2, LOW);
  analogWrite(PWM_A, SPEED); analogWrite(PWM_B, SPEED);
}

void stopBot() {
  digitalWrite(MOTOR_A1, LOW); digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW); digitalWrite(MOTOR_B2, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_A1, HIGH); digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW); digitalWrite(MOTOR_B2, HIGH);
  analogWrite(PWM_A, SPEED); analogWrite(PWM_B, SPEED);
}

int getDistance(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long duration = pulseIn(echo, HIGH, 30000);
  if (duration == 0) return 0;
  return duration * 0.034 / 2;
}

void updatePosition() {
  switch (heading) {
    case 0: y += 20; break;  // forward
    case 1: x += 20; break;  // right
    case 2: y -= 20; break;  // back
    case 3: x -= 20; break;  // left
  }
}