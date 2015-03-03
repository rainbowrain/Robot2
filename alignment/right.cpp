// test turn left (just turning left and then stop)

#include "Arduino.h"
#include "turn.h"
#include "sensor.h"
#include "Robot_Movement.h"
#include "line_count.h"

/*The thing should STOP and then this function should be called, counter should be declared and set to 0*/


void turnRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int sensorMax, unsigned int sensorMin,unsigned int counterMax, unsigned int counterMin)
{
  unsigned int initial = 0;
  unsigned int counter = 0;	
  unsigned int irRight = irTCRTSensor(sensorMax, sensorPin2, sensorMin);  //right sensor
  rotateRight(HPin1, HPin2, HPin3, HPin4);
  while (counter < 1)			//should only see one black line
  {
     if (irRight < 8 && initial == 0)   //sees black initially
     {
        unsigned int irRight = irTCRTSensor(sensorMax, sensorPin2, sensorMin);
        Serial.println ("black initially");
    }
    else  // sees white - and initial becomes one
    {
       counter = lineCount( sensorMax, sensorMin, counterMax, counterMin, 0, sensorPin2);	//using the right IR sensor
        initial = 1;   
    }
  }
    STOP(HPin1,HPin2, HPin3, HPin4);
  delay(1);
  Serial.println("complete turning right");
}
