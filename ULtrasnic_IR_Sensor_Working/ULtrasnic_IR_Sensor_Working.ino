

/*#define IN_1  15          // L298N in1 motors Right         
GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

// **Ultrasonic Sensor 1 (Front)**
const int trigPin1 = 14;  // D5 -> GPIO14
const int echoPin1 = 12;  // D6 -> GPIO12

// **Ultrasonic Sensor 2 (Side)**
const int trigPin2 = 4;   // D2 -> GPIO4
const int echoPin2 = 5;   // D1 -> GPIO5

#include <ESP8266WiFi.h>


const int inputPin = 16; // D0 -> GPIO16 (IR Sensor)
String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;

void setup() {

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT); 
pinMode(inputPin, INPUT);
Serial.begin(115200);
  
   
}

void goAhead(){   
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    
  }

void goBack(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW); 
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

void goRight(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);   

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
     
  }

void goLeft(){
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH); 

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

void goAheadRight(){     
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);    
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
    
   }

void goAheadLeft(){      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);    

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      
  }

void goBackRight(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
     
  }

void goBackLeft(){ 
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);  
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      
  }

void stopRobot(){   
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);  

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      
 }

void loop() {

 digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH, 30000); // Timeout added
  int distance1 = duration1 * 0.034 / 2;
  
  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  // **Measure distance from Sensor 2**
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH, 30000); // Timeout added
  int distance2 = duration2 * 0.034 / 2;
  
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  delay(1000); // Delay for readability

 


 int sensorValue = digitalRead(inputPin); 
if (sensorValue == LOW) 
  {  // Object detected
    //Serial.println("  Object Detected"); 
    stopRobot();

    if(distance2>distance1 )
    {
      goAheadRight(); 

    }

    else 
    {
      goAheadLeft();   

    }


        
   }
else if (sensorValue==HIGH)
{  //Serial.println("NO Object Detected");
    
  goAhead();
  
}
      
     
}  */

#define IN_1  15          // L298N in1 motors Right           GPIO15(D8)
#define IN_2  13          // L298N in2 motors Right           GPIO13(D7)
#define IN_3  2           // L298N in3 motors Left            GPIO2(D4)
#define IN_4  0           // L298N in4 motors Left            GPIO0(D3)

// **Ultrasonic Sensor 1 (Front)**
const int trigPin1 = 14;  // D5 -> GPIO14
const int echoPin1 = 12;  // D6 -> GPIO12

// **Ultrasonic Sens++++++++++++++++++++++++++or 2 (Side)**
const int trigPin2 = 4;   // D2 -> GPIO4
const int echoPin2 = 5;   // D1 -> GPIO5

#include <ESP8266WiFi.h>

const int inputPin = 16; // D0 -> GPIO16 (IR Sensor)
String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;
const int MAX_DISTANCE = 400; // Set a maximum distance in cm

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 
  pinMode(inputPin, INPUT);
  Serial.begin(115200);
}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH, 30000); // Timeout added
  if (duration == 0) {
    return MAX_DISTANCE; // Return max distance if no echo is received
  }
  return duration * 0.034 / 2; // Convert time to distance
}

void goAhead() {   
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
}

void goBack() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW); 
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
}

void goRight() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);   
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH); 
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
}

void goAheadRight() {     
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);    
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
}

void goAheadLeft() {      
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);    
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
}

void stopRobot() {   
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);  
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}

void loop() {
  int distance1 = getDistance(trigPin1, echoPin1);
  int distance2 = getDistance(trigPin2, echoPin2);

  Serial.print("Distance 1: ");
  Serial.print(distance1);
  Serial.println(" cm");

  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");

  int sensorValue = digitalRead(inputPin);
       if (sensorValue == LOW) 
       {  // Object detected
       
         stopRobot();
          if (distance2 > distance1)
        {
              Serial.print("Distance 1 is less than Distance 2");
              Serial.print(distance2>distance1);
               goAheadRight();
        } 
    
       else
        {
          //Serial.print("Distance 2 is less than Distance 1");
          Serial.print(distance1>distance2);
          goAheadLeft();
        }
  } 
  
  else { // No object detected
    goAhead();
    Serial.print("Go head");
  }
  
  delay(500); // Reduce delay for better response time
}














 



