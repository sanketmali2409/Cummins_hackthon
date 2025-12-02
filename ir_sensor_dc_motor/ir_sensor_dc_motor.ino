/*#include <ESP8266WiFi.h>

// IR Sensor Pin
const int inputPin = 4; // D2 -> GPIO4 (IR Sensor)

#define EN_A 5   // Enable Pin for Right Motor -> GPIO5 (D1)
#define EN_B 14  // Enable Pin for Left Motor  -> GPIO14 (D5)
// Motor Control Pins
#define IN1  15  // L298N in1 motors Right -> GPIO15(D8)
#define IN2  13  // L298N in2 motors Right -> GPIO13(D7)
#define IN3  2   // L298N in3 motors Left  -> GPIO2(D4)
#define IN4  0   // L298N in4 motors Left  -> GPIO0(D3)

// Movement states
enum Movement { STOP, FORWARD, BACKWARD, LEFT, RIGHT };
Movement move = FORWARD; // Initial movement state

void setup() {
  Serial.begin(115200);

  // Setup motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  
  // Setup IR sensor pin
  pinMode(inputPin, INPUT);

  carStop(); // Ensure motors are off at start
}

void loop() {
  int sensorValue = digitalRead(inputPin); // Read IR sensor

  if (sensorValue == LOW) {  // Object detected
    Serial.println("Object Detected! Turning Right...");
    moveRight();
    delay(1000); // Give time to turn

    sensorValue = digitalRead(inputPin); // Check again
    if (sensorValue == HIGH) { // No object on right
      Serial.println("No Object on Right, Moving Forward 100cm...");
      moveForward(100);
      
      Serial.println("Turning Left...");
      moveLeft();
      delay(1000);

      Serial.println("Checking Left Side...");
      sensorValue = digitalRead(inputPin);
      if (sensorValue == HIGH) { // No object on left
        Serial.println("No Object on Left, Moving Backward 100cm...");
        moveBackward(100);
        
        Serial.println("Turning Left Again...");
        moveLeft();
        delay(1000);
        
        Serial.println("Moving Forward 100cm...");
        moveForward(100);
      } 
    }
  } else {
    Serial.println("No Object, Moving Forward...");
    moveForward(10); // Keep moving forward in small increments
  }

  delay(100);  // Prevent excessive polling
}

// Function to move forward by a specified distance
void moveForward(int distance) {
  Serial.println("Moving Forward...");
  carForward();
  delay(distance * 10);  // Approximate time to move the distance
  carStop();
}

// Function to move backward by a specified distance
void moveBackward(int distance) {
  Serial.println("Moving Backward...");
  carBackward();
  delay(distance * 10);
  carStop();
}

// Function to turn left
void moveLeft() {
  Serial.println("Turning Left...");
  carTurnLeft();
  delay(800); // Adjust timing for 90-degree turn
  carStop();
}

// Function to turn right
void moveRight() {
  Serial.println("Turning Right...");
  carTurnRight();
  delay(800);
  carStop();
}

// Motor control functions
void carForward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carBackward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carTurnLeft() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carTurnRight() {
   digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
} */


/*#include <ESP8266WiFi.h>

// IR Sensor Pin
const int inputPin = 4; // D2 -> GPIO4 (IR Sensor)

#define EN_A 5   // Enable Pin for Right Motor -> GPIO5 (D1)
#define EN_B 14  // Enable Pin for Left Motor  -> GPIO14 (D5)

// Motor Control Pins
#define IN1  15  // L298N in1 motors Right -> GPIO15(D8)
#define IN2  13  // L298N in2 motors Right -> GPIO13(D7)
#define IN3  2   // L298N in3 motors Left  -> GPIO2(D4)
#define IN4  0   // L298N in4 motors Left  -> GPIO0(D3)

// Movement states
enum Movement { STOP, FORWARD, BACKWARD, LEFT, RIGHT };
Movement move = FORWARD; // Initial movement state

void setup() {
  Serial.begin(115200);

  // Setup motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  
  // Setup IR sensor pin
  pinMode(inputPin, INPUT);

  carStop(); // Ensure motors are off at start
}

void loop() {
  int sensorValue = digitalRead(inputPin); // Read IR sensor
  sensorValue = !sensorValue; // **Invert the sensor logic**

  if (sensorValue == HIGH) {  // Object detected (Previously LOW)
    Serial.println("Object Detected! Turning Right...");
    moveRight();
    delay(1000); // Give time to turn

    sensorValue = !digitalRead(inputPin); // Check again
    if (sensorValue == LOW) { // No object on right (Previously HIGH)
      Serial.println("No Object on Right, Moving Forward 100cm...");
      moveForward(100);
      
      Serial.println("Turning Left...");
      moveLeft();
      delay(1000);

      Serial.println("Checking Left Side...");
      sensorValue = !digitalRead(inputPin);
      if (sensorValue == LOW) { // No object on left
        Serial.println("No Object on Left, Moving Backward 100cm...");
        moveBackward(100);
        
        Serial.println("Turning Left Again...");
        moveLeft();
        delay(1000);
        
        Serial.println("Moving Forward 100cm...");
        moveForward(100);
      } 
    }
  } else {
    Serial.println("No Object, Moving Forward...");
    moveForward(10); // Keep moving forward in small increments
  }

  delay(100);  // Prevent excessive polling
}

// Function to move forward by a specified distance
void moveForward(int distance) {
  Serial.println("Moving Forward...");
  carForward();
  delay(distance * 10);  // Approximate time to move the distance
  carStop();
}

// Function to move backward by a specified distance
void moveBackward(int distance) {
  Serial.println("Moving Backward...");
  carBackward();
  delay(distance * 10);
  carStop();
}

// Function to turn left
void moveLeft() {
  Serial.println("Turning Left...");
  carTurnLeft();
  delay(800); // Adjust timing for 90-degree turn
  carStop();
}

// Function to turn right
void moveRight() {
  Serial.println("Turning Right...");
  carTurnRight();
  delay(800);
  carStop();
}

// Motor control functions
void carForward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carBackward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carTurnLeft() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carTurnRight() {
   digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}*/

#include <ESP8266WiFi.h>

// IR Sensor Pin
const int inputPin = 4; // D2 -> GPIO4 (IR Sensor)

#define EN_A 5   // Enable Pin for Right Motor -> GPIO5 (D1)
#define EN_B 14  // Enable Pin for Left Motor  -> GPIO14 (D5)

// Motor Control Pins
#define IN1  15  // L298N in1 motors Right -> GPIO15(D8)
#define IN2  13  // L298N in2 motors Right -> GPIO13(D7)
#define IN3  2   // L298N in3 motors Left  -> GPIO2(D4)
#define IN4  0   // L298N in4 motors Left  -> GPIO0(D3)

// Movement states
enum Movement { STOP, FORWARD, BACKWARD, LEFT, RIGHT };
Movement move = FORWARD; // Initial movement state

void setup() {
  Serial.begin(115200);

  // Setup motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  
  // Setup IR sensor pin
  pinMode(inputPin, INPUT);

 // carStop(); // Ensure motors are off at start
}

void loop() {
  int sensorValue = digitalRead(inputPin); // Read IR sensor

  if (sensorValue == HIGH) {  // Object detected
    Serial.println("Object Detected! Turning Right...");
    moveRight();
    delay(1000); // Give time to turn

    sensorValue = digitalRead(inputPin); // Check again
    if (sensorValue == LOW)
     { // No object on right
      Serial.println("No Object on Right, Moving Forward 100cm...");
     goAhead();
      
      Serial.println("Turning Left...");
      moveLeft();
      delay(1000);

      
      } 
    }
  } else {  
    // No object detected → Move forward continuously
    Serial.println("No Object Detected, Moving Forward...");
    stopRobot();
  }

  delay(100);  // Prevent excessive polling
}

// Function to move forward by a specified distance
void moveForward(int distance) {
  Serial.println("Moving Forward...");
  carForward();
  delay(distance * 10);  // Approximate time to move the distance
  carStop();
}

// Function to move backward by a specified distance
void moveBackward(int distance) {
  Serial.println("Moving Backward...");
  carBackward();
  delay(distance * 10);
  carStop();
}

// Function to turn left
void moveLeft() {
  Serial.println("Turning Left...");
  carTurnLeft();
  delay(800); // Adjust timing for 90-degree turn
  carStop();
}

// Function to turn right
void moveRight() {
  Serial.println("Turning Right...");
  carTurnRight();
  delay(800);
  carStop();
}

// Motor control functions
void carForward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carBackward() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carTurnLeft() {
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void carTurnRight() {
   digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void carStop() {
  digitalWrite(EN_A, LOW);
  digitalWrite(EN_B, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
  }

  void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

