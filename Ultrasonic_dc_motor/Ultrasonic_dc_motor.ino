/*Nodemcu ESP8266 WIFI control car.
 * This code created by sritu hobby team.
 * https://srituhobby.com
 */
 

#include <ESP8266WiFi.h>

 
//Motor PINs
const int trigPin = 14;  // D5 -> GPIO14
const int echoPin = 12;  // D6 -> GPIO12

#define IN1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN4  0           // L298N in4 motors Left            GPIO0(D3)

 
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int move;

 
 
void setup() {

  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 
 
  
}
 

 

 
void smartcar() {
  if (move == 1) {
    carforward();
    Serial.println("carforward");
  } else if (move == 2) {
    carbackward();
    Serial.println("carbackward");
  } else if (move == 3) {
    carturnleft();
    Serial.println("carfleft");
  } else if (move == 4) {
    carturnright();
    Serial.println("carright");
  } else if (move==5) {
    carStop();
    Serial.println("carstop");
  }

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout added
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance<10)
  {
    move =5;

  }
  else if(distance<50)
  {
    move=4;
  }
   else if(distance<100)
  {
    move=3;
  }
   else if(distance<150)
  {
    move=2;
  }
   else if(distance<200)
  {
    move=1;
  }
 smartcar();

}
 
void carforward() {
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {

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
//  Working esp8266 with ultrasonic sensor



/*
#include <ESP8266WiFi.h>

//int ledPin = 12; // choose pin for the LED D6
int inputPin = 04; // choose input pin (for Infrared sensor) D2
int val = 0; // variable for reading the pin status 
//Motor PINs
const int trigPin = 14;  // D5 -> GPIO14
const int echoPin = 12;  // D6 -> GPIO12

#define IN1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN4  0           // L298N in4 motors Left            GPIO0(D3)

 
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int move;

 
 
void setup() {

  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);  
}
 

 

 
void smartcar() {
  if (move == 1) {
    carforward();
    Serial.println("carforward");
  } else if (move == 2) {
    carbackward();
    Serial.println("carbackward");
  } else if (move == 3) {
    carturnleft();
    Serial.println("carfleft");
  } else if (move == 4) {
    carturnright();
    Serial.println("carright");
  } else if (move==5) {
    carStop();
    Serial.println("carstop");
  }

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout added
  int distance = duration * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.println(distance);

  if(distance<10)
  {
    move =5;

  }
  else if(distance<50)
  {
    move=1;
  }
   else if(distance<100)
  {
    move=2;
  }
   else if(distance<150)
  {
    move=3;
  }
   else if(distance<200)
  {
    move=4;
  }
   val = digitalRead(inputPin); // read input value 
   if (val == HIGH)
   { // check if the input is HIGH
      digitalWrite(ledPin, LOW); // turn LED OFF  
     Serial.println("Object Detected!");
   } 
   else 
   { 
      digitalWrite(ledPin, HIGH); // turn LED ON 
       Serial.println("No OBJECT"); 
   }
 smartcar();

}
 
void carforward() {
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carbackward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnleft() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnright() {

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

*/

/*
 * Interface InfraRed Sensor Using NodeMCU
 * By TheCircuit
 * Red :     5V
 * Brown: Sensor output
 * Black : Ground
*/





