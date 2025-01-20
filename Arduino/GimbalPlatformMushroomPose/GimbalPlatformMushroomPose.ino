#include <Servo.h>

// Create servo objects
Servo topServo;
Servo bottomServo;

// Pin numbers for the servos
#define topServoPin 9
#define bottomServoPin 10

// Rest time between servo movements in milliseconds
const int restTime= 1000;

void setup() {
  // Attach the servo objects to the respective pins
  topServo.attach(topServoPin);
  bottomServo.attach(bottomServoPin);
  
  // Initialize the servos to the center position (90 degrees)
  topServo.write(90);
  bottomServo.write(0);

  // Set up serial communication at 9600 baud rate
  Serial.begin(9600);
}

void loop() {

  for (int  topServoAngle=10; topServoAngle <= 360; topServoAngle+= 10){
    // Top Servo Control
    // First rotation start with yaw=10 degrees w.r.t vertical axis going though the middle of mushroom stem
    // Yaw is -90 to +90 and pitch is 0 to 360 
    topServo.write(topServoAngle);
    // Bottom Servo Control
    for (int  bottomServoAngle=0; bottomServoAngle <= 360; bottomServoAngle+= 10){
      // Debuigging purpose
      if (bottomServoAngle > 180){
        Serial.println("BottomServo: " + String(bottomServoAngle) + " & TopServo: " + String(-topServoAngle));
      }
      else{
        Serial.println("BottomServo: " + String(bottomServoAngle) + " & TopServo: " + String(topServoAngle));
      }

      // Logic to move the servos in a fashion required
      bottomServo.write(bottomServoAngle);
      delay(restTime); // time delay between two poses
    }
    if (topServoAngle==360){
      topServo.write(90);
      bottomServo.write(0);
      Serial.println("Going back to Default pose; Whole Gimbal cycle Completed!");
      //break;
    }
  }
  while(true){}
  
}
