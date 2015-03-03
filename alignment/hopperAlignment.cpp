// hopper alignment.cpp
#include "Arduino.h"
#include "sensor.h"
#include "coordinateArray.h"
#include "Robot_Movement.h"
#include "line_count.h"
#include "turn.h"
/*	Version 1: March 2, 2015  by Wan-Ying (Jenny) Yue	*/

/*
*	This module, assumes that the robot is on one of the 6 specified points
*	that is adjacent to the hoppers. 
*	This module uses the ultrasonic distance sensor to locate the hopper
*/

const unsigned int range = 25;
const unsigned int stopDistance = 10;
void hopperAlignment(long originalDistance, long distanceAligned)
{
	long distance;
	long distance1Max = 0;
	long distance2Max = 0;
	long distance3Max = 0;
	//record current sensor reading; assume that the sensor is place at the height of which 
	//it can only see the hopper and not the walls
	//the middle pillar is always the furthest away from the stopping point.
	originalDistance = distanceDetect(trigPin, echoPin);
	rotateRight(HPin1, HPin2, HPin3, HPin4);
	while ( distance1Max == 0 | distance2Max == 0 | distance3Max == 0)
	{
		distance = distanceDetect(trigPin, echoPin);
		if (distance1Max == 0 && distance < 10)
		{
			while( distance < 10)
			{
				//get ultrasonic sensor readings 
				distance = distanceDetect(trigPin, echoPin);
				if (distance > distance1Max && distance < range) 
				{
					distance1Max = distance;
				}
			}
			Serial.print("Distance to hopper leg 1: ");
			Serial.println(distance1Max);
		}

		if (distance2Max == 0 && distance < 25)
		{
			while( distance < 25)
			{
				//get ultrasonic sensor readings 
				distance = distanceDetect(trigPin, echoPin);
				if (distance > distance1Max && distance < range) 
				{
					distance2Max = distance;
				}
			}
			Serial.print("Distance to the middle: ");
			Serial.println(distance2Max);	
		}
		
		if (distance3Max == 0 && distance < 22)
		{
			while( distance < 22)
			{
				//get ultrasonic sensor readings 
				distance = distanceDetect(trigPin, echoPin);
				if (distance > distance1Max && distance < range) 
				{
					distance3Max = distance;
				}
			}
			Serial.print("Distance to hopper leg 2: ");
			Serial.println(distance3Max);
		}
	}
	//second turn
	Serial.println("Done scanning");
	STOP(HPin1, HPin2, HPin3, HPin4);
	delay(5000);

	while (distance != distance2Max)
	{
		distance = distanceDetect(trigPin, echoPin);
		rotateLeft(HPin1, HPin2, HPin3, HPin4);
	}
	
	STOP(HPin1, HPin2, HPin3, HPin4);
	Serial.println("Done alignment");
	distanceAligned = distance;
	delay(5000);
	
	while (distance != stopDistance)
	{
		moveForward (HPin1, HPin2, HPin3, HPin4);
		distance = distanceDetect(trigPin, echoPin);
	}
	STOP(HPin1, HPin2, HPin3, HPin4);
	Serial.println("Done!");
}

