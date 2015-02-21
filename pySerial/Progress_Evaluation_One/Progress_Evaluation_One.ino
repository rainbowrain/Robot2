/***********************INTRODUCTION*********************************
* This module combines the functions of the IR sensors with the     *
* supersonic distance sensor. The goal is to use IR sensor to avoid *
* the hoppers and the walls and the distance sensor indicate        *
* how far away the obstacles are. The goal is for later utilizing   *
* the same sensors for navigation and critical failure situations   *
*/


/********************VERSIONS AND UPDATES***************************
* Initial code: February 7, 2015
*/

/********************SPECIFICATIONS*******************************
* Using 2 IRs and 1 distance sensor to control motor (wheel) spin
*   - IR can detect up to 10 cm (from the breadboard)
*   - Distance sensor can detect over a large range
* Given left IR sensor detects an object:
*   - left wheel moves faster than right wheel
* Given right IR sensor detects an object:
*   - left wheel moves slower than right wheel
* Given that both right and left IR sensor detects an object:
*   NOTE: it maybe really wide and the robot can squeeze through
*         so it maybe okay to keep going
*   - check distance sensor
* Given that the distance sensor is <= 7cm
*   - stop
*   - Go backwards until the sensor reads 7cm
*   - Rotate 180?
*   - check IR sensors (until at least one of them reads '1')
* Else keep going straight
*/

#include "Arduino.h" 
#include "Sensor.h"
#include "Robot_Movement.h"

#define SAFEDISTANCE 7  //in cm 
 
void setup()
{
  Serial.begin(9600);
  pinMode(IRLEDPIN1 , OUTPUT); 
  pinMode(IRRECEIVERPIN1 , INPUT); 
  pinMode(IRRECEIVERPIN2 , INPUT); 
  //for left motor
  pinMode(HPin1, OUTPUT);
  pinMode(HPin2, OUTPUT);
  //for right motor
  pinMode(HPin3, OUTPUT);
  pinMode(HPin4, OUTPUT);
  
  pinMode(ePin2, OUTPUT);  //left 
  pinMode(ePin1, OUTPUT);  //right
  /*
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
  */
}

void loop() // Main loop auto-repeats
{
  tone(IRLEDPIN1, FREQUENCY);
  delay(1);
  unsigned int irLeft = digitalRead(IRRECEIVERPIN2);  //left 
  delay(1);
  unsigned int irRight = digitalRead(IRRECEIVERPIN1);  //right
  
  if (irRight == 0 && irLeft ==0)
  //Right sensor sees and left sensor sees white
  {
    Serial.println("Right 0 AND left 0 : go straight but object may be ahead");
    moveForward (HPin1, HPin2, HPin3, HPin4);
  }
  else if (irLeft ==1 && irRight == 1)
  //left and right sensor sees blackline
  {
    Serial.println("Left 1 AND right 1: IR sees nothing");
    moveForward (HPin1, HPin2, HPin3, HPin4);
  }
  else if (irLeft == 1)
  //left sensor sees blackline 
  {
    Serial.println("Left blackline - left skewed");
    pivotRight(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2);
  }
  else
  //Right sensor sees blackline 
  {
    Serial.println("Right blackline - right skewed");
    pivotLeft(HPin1, HPin2, HPin3, HPin4, ePin1, ePin2);
  }
  delay (500);
  
  //Check if the distance to the wall is okay
 // long distance = distanceDetect(TRIGPIN,ECHOPIN);
  
  // backup until safe distance
  // NOTE: this is based on the assumpution that it is not going to back up straight
 /* while (distance < SAFEDISTANCE)
  {
      moveBackward(HPin1, HPin2, HPin3, HPin4);
      distance = distanceDetect(TRIGPIN,ECHOPIN);
  }
  */
}

