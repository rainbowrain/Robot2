#include "coordinateArray.h"
#include "Arduino.h" 
#include "sensor.h"
#include "Robot_Movement.h"
#include "line_count.h"
#include "turn.h"
#define SAFEDISTANCE 7  //in cm 

void setup()

{
   Serial.begin (9600);
   pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(HPin1, OUTPUT);   //for left motor
  pinMode(HPin2, OUTPUT);
  pinMode(HPin3, OUTPUT);   //for right motor
  pinMode(HPin4, OUTPUT);
  pinMode(ePin2, OUTPUT);  //left 
  
  pinMode(ePin1, OUTPUT);  //right
   
   
}
void loop()
{
  long distance = distanceDetect( trigPin, echoPin);
  Serial.println(distance);
  /*  long originalDistance;
    long distanceAligned;
    hopperAlignment(originalDistance, distanceAligned);
    STOP(HPin1, HPin2, HPin3, HPin4);
    delay (500);
    */
  
}


