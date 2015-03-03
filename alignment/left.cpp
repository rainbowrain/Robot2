// test turn left (just turning left and then stop)

#include "Arduino.h"
#include "turn.h"
#include "sensor.h"
#include "Robot_Movement.h"
#include "line_count.h"

/*
step 1: Stop and check right sensor
a) if zero, good!
b) if 1, skip step 2
step 2: rotate until reach 1st blackline
step 3: poll sensor to make sure that it is a one (keep/start rotating)
step 4: if it is, counter ++
step 5: rotate until reach the white
step 6: make sure there is plenty of white
step 7: make sure that it is blackline, then start normal line following
step 8: current to past, future to current, next value to future
*/

/*The thing should STOP and then this function should be called, counter should be declared and set to 0*/


void turnLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int sensorMax, unsigned int sensorMin,unsigned int counterMax, unsigned int counterMin)
{

  unsigned int counter = 0;	
  unsigned int initial = 0;
  unsigned int irLeft = irTCRTSensor(sensorMax, sensorPin1, sensorMin);
  rotateLeft(HPin1, HPin2, HPin3, HPin4);
  while (counter < 1)			//should only see one black line
  {
    if (irLeft < 8 && initial == 0)   //sees black initially
    {
      Serial.println ("black initially");
      unsigned int irLeft = irTCRTSensor(sensorMax, sensorPin1, sensorMin);
    }
    else  // sees white - and initial becomes one
    {
      counter = lineCount(sensorMax, sensorMin, counterMax, counterMin, 0, sensorPin1);	//using the left IR sensor
      initial = 1;   
    }
  }
  STOP(HPin1,HPin2, HPin3, HPin4);
  delay(1);
  Serial.println("complete turn left");
}
