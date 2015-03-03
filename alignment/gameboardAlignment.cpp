//using distance sensor to align the robot to the game board ready to make play
#include "Arduino.h"
#include "sensor.h"
#include "coordinateArray.h"
#include "Robot_Movement.h"
#include "line_count.h"
#include "turn.h"


void gameboardAlignment(unsigned int pastCoordinate,unsigned int currentCoordinate, unsigned int sensor1Max, unsigned int sensor2Max, unsigned int sensor1Min, unsigned int sensor2Min, unsigned int counterMax, unsigned int counterMin)
{
	int check = pastCoordinate - currentCoordinate; 
	if (check == 1)
	{
		turnRight(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
	}
	else if (check == -1)
	{
		turnLeft(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
	}
	else if (check == -10)
	{
		turnLeft(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
		turnLeft(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
	}
	else
	{
		Serial.println("check code!");
	}
	
	long distance = distanceDetect(trigPin, echoPin);
	while (distance > 5);
	{
		distance = distanceDetect(trigPin, echoPin);
		// line follow slowly
          unsigned int irLeft = irTCRTSensor (sensor1Max, sensorPin1, sensor1Min);  //left 
          unsigned int irRight = irTCRTSensor (sensor2Max, sensorPin2, sensor2Min);  //right
          if (irRight > 8 && irLeft > 8)
          //Right sensor sees and left sensor sees white
          {
            Serial.println("Right 0 AND left 0 : go straight but object may be ahead");
            moveForward(HPin1, HPin2, HPin3, HPin4);
          }
          else if (irLeft < 9 && irRight < 8)
          //left and right sensor sees blackline
          {
            Serial.println("Left 1 AND right 1: IR sees nothing");
            moveForward(HPin1, HPin2, HPin3, HPin4);
          }
          else if (irLeft < 9 && irRight > 8)
          //left sensor sees blackline 
          {
            Serial.println("Left blackline - left skewed");  
            pivotLeft(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2);
          }
          else if (irRight < 9 && irLeft > 8)
          //Right sensor sees blackline 
          {
            Serial.println("Right blackline - right skewed");
            pivotRight(HPin1, HPin2, HPin3, HPin4, ePin1, ePin2);
          }
          else //sees other values
          {
            Serial.println ("please check the sensors, adjust the height");
          }
	}
	STOP(HPin1, HPin2, HPin3, HPin4);
	Serial.println("Done!");
}
