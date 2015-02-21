/***********************INTRODUCTION*********************************
* This module combines the functions of the IR sensors with the     *
* supersonic distance sensor. The goal is to use IR sensor to avoid *
* the hoppers and the walls and the distance sensor indicate        *
* how far away the obstacles are. The goal is for later utilizing   *
* the same sensors for navigation and critical failure situations   *
*/


/********************VERSIONS AND UPDATES***************************
* Initial code: February 7, 2015
* Updated February 14, 2015 - change digital into analog LED
* included calibration of sensor in code
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
#include "sensor.h"
#include "Robot_Movement.h"

#define SAFEDISTANCE 7  //in cm 

/*************************Sensor Readings*******************/
unsigned int sensorValue = 0;         // the sensor value
unsigned int sensorMin = 1023;        // minimum sensor value
unsigned int sensorMax = 0;           // maximum sensor value
/**********************************************************/

void setup()
{
  Serial.begin(9600);
 /************************PINS********************************/
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
 /*************************************************************/ 
  /*******************Sensor Calibration**********************/
  while (millis() < 5000)
  {
    sensorValue = analogRead(sensorPin1);
    // record the maximum sensor value
    if (sensorValue > sensorMax)
    {
      sensorMax = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorMin) 
    {
      sensorMin = sensorValue;
    }
    Serial.println(millis());  //knowing when it starts 
  }
   /*************************************************************/
}

void loop() // Main loop auto-repeats
{ 
  unsigned int irLeft = irTCRTSensor (sensorMax, sensorPin1, sensorMin);  //left 
  unsigned int irRight = irTCRTSensor (sensorMax, sensorPin2, sensorMin);  //right
  Serial.print("irLeft: ");
  Serial.println(irLeft);
  
  Serial.print("irRight: ");
  Serial.println(irRight);
  /*Note: below 3 is black, above 8 is white*/
  
 
  if (irRight > 8 && irLeft >8)
  //Right sensor sees and left sensor sees white
  {
    Serial.println("Right 0 AND left 0 : go straight but object may be ahead");
    moveForward (HPin1, HPin2, HPin3, HPin4);
  }
  else if (irLeft < 3 && irRight < 3)
  //left and right sensor sees blackline
  {
    Serial.println("Left 1 AND right 1: IR sees nothing");
    moveForward (HPin1, HPin2, HPin3, HPin4);
  }
  else if (irLeft < 3 && irRight > 8)
  //left sensor sees blackline 
  {
    Serial.println("Left blackline - left skewed");
    pivotRight(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2);
  }
  else if (irRight < 3 && irLeft > 8)
  //Right sensor sees blackline 
  {
    Serial.println("Right blackline - right skewed");
    pivotLeft(HPin1, HPin2, HPin3, HPin4, ePin1, ePin2);
  }
  else //sees other values
  {
    Serial.println ("please check the sensors, adjust the height");
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

