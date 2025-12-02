 

/*
#include <ESP8266WiFi.h>

String apiKey = "TUX7NV4ZG63KH0OU";  // Your ThingSpeak API key
const char *ssid = "realme 11 5G";
const char *pass = "99999999";
const char* server = "api.thingspeak.com";

// Ultrasonic Sensor Pins
const int trigPin1 = 14;  // D5 -> GPIO14
const int echoPin1 = 12;  // D6 -> GPIO12

// **Ultrasonic Sensor 2 (Side)**
const int trigPin2 = 4;   // D2 -> GPIO4
const int echoPin2 = 5;   // D1 -> GPIO5

WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");
}

// Function to get distance from ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;  // cm
  return distance;
}

void loop() {
  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm | Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=" + String(distance1);
    postStr += "&field2=" + String(distance2);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.println("Data sent to ThingSpeak!");
  }

  client.stop();

  Serial.println("Waiting 20s before next update...");
  delay(20000); // Minimum 15s delay required by ThingSpeak
}
*/

#include <ESP8266WiFi.h>

const char* ssid = "realme 11 5G";
const char* password = "99999999";

const char* server = "api.thingspeak.com";
String apiKey = "TUX7NV4ZG63KH0OU";

// Ultrasonic Sensor 1
const int trigPin1 = 14;  // D5
const int echoPin1 = 12;  // D6

// Ultrasonic Sensor 2
const int trigPin2 = 4;   // D2
const int echoPin2 = 5;   // D1

WiFiClient client;

void setup() {
  Serial.begin(115200);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  connectWiFi();
}

void connectWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
  } else {
    Serial.println("\n❌ WiFi failed. Restarting...");
    ESP.restart(); // Safe restart
  }
}

long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;

  if (distance <= 0 || distance > 400) return -1;
  return distance;
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  long distance1 = getDistance(trigPin1, echoPin1);
  long distance2 = getDistance(trigPin2, echoPin2);

  Serial.print("Distance1: ");
  Serial.print(distance1);
  Serial.print(" cm | Distance2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  if (distance1 > 0 && distance2 > 0 && client.connect(server, 80)) {
    String postData = "field1=" + String(distance1) + "&field2=" + String(distance2);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + apiKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(postData.length());
    client.println();
    client.print(postData);

    Serial.println("✅ Data sent to ThingSpeak!");

    client.flush();
    client.stop();
  } else {
    Serial.println("❌ Connection to ThingSpeak failed.");
    client.stop();  // Ensure it's closed
  }

  delay(20000);  // Wait 20s before next loop
}
