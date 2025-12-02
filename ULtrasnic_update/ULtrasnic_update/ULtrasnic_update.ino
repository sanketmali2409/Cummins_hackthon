#include <ESP8266WiFi.h>

// Motor & Sensor PINs
const int trigPin = 14;  // D5 -> GPIO14
const int echoPin = 12;  // D6 -> GPIO12

#define IN1  15  // L298N in1 Right Motor  -> GPIO15(D8)
#define IN2  13  // L298N in2 Right Motor  -> GPIO13(D7)
#define IN3  2   // L298N in3 Left Motor   -> GPIO2(D4)
#define IN4  0   // L298N in4 Left Motor   -> GPIO0(D3)

int move = 0;       // Movement state
int lastMove = -1;  // Previous movement state

void setup() {
  Serial.begin(115200);

  // Initialize sensor & motor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  carStop(); // Ensure motors are off at start
}

void loop() {
  int distance = getDistance();

  // Update movement based on distance
  int prevMove = move;
  if (distance < 10) {
    move = 5; // Stop
  } else if (distance < 50) {
    move = 4; // Turn Right
  } else if (distance < 100) {
    move = 3; // Turn Left
  } else if (distance < 150) {
    move = 2; // Move Backward
  } else if (distance < 200) {
    move = 1; // Move Forward
  } else {
    move = 0; // No movement
  }

  // Add a short stop if changing from forward to backward or vice versa
  if ((prevMove == 1 && move == 2) || (prevMove == 2 && move == 1)) {
    carStop();
    delay(200); // Pause before switching direction
  }

  // Execute movement if it has changed
  if (move != lastMove) {
    lastMove = move;
    smartcar();
  }

  delay(100);  // Prevent excessive sensor polling
}

// Function to measure distance using the Ultrasonic sensor
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout added
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}

// Function to control car movement
void smartcar() {
  switch (move) {
    case 1:
      carForward();
      Serial.println("Car moving forward");
      break;
    case 2:
      carBackward();
      Serial.println("Car moving backward");
      break;
    case 3:
      carTurnLeft();
      Serial.println("Car turning left");
      break;
    case 4:
      carTurnRight();
      Serial.println("Car turning right");
      break;
    case 5:
      carStop();
      Serial.println("Car stopped");
      break;
    default:
      carStop();
      Serial.println("Car in idle state");
      break;
  }
}

// Motor control functions
void carForward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carBackward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carTurnLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carTurnRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
