#include "coordinateArray.h"
#include "Arduino.h" 
#include "sensor.h"
#include "Robot_Movement.h"
#include "line_count.h"
#include "turn.h"
  /*
		Program checks for the robot should going straight, turn left, or turn right
		by reading the past, current and future coordinate in the array.
		- straight if:
			- past +/- 1 = current +/- 1 = future 
			- past +/- 10 = current +/- 10 = future 
		- turn "left" relatively to the front of the robot
			- past +/- 1  = present +/- 10 = future (future - past = +/- 11)
			- past +/- 10 = present -/+ 1 = future 	(future - past = +/- 9)
		- turn "right"
			- past +/- 10  = present +/- 1 = future (future - past = +/- 11)
			- past +/- 1 = present -/+ 10 = future 	(future - past = +/- 9)

  */
  
void checkForAction(unsigned int pastCoordinate, unsigned int currentCoordinate, unsigned int futureCoordinate, unsigned int sensor1Max, unsigned int sensor2Max, unsigned int sensor1Min, unsigned int sensor2Min, unsigned int counterMax, unsigned int counterMin)
{	// go through the array for the coordinates - eventually going to have a program that will produce the array (path) given the start and the end coordinate
    STOP(HPin1,HPin2,HPin3,HPin4);
    int differencePC = currentCoordinate - pastCoordinate;
    Serial.print("current - past: ");
    Serial.println(differencePC);
    
    int differenceCF = futureCoordinate - currentCoordinate;
    Serial.print("future - current: ");
    Serial.println(differenceCF);
    
    int differencePF = futureCoordinate - pastCoordinate;
    Serial.print("future - past: ");
    Serial.println(differencePF);

     if (differencePF == 20 | differencePF == -20 | differencePF == 2 | differencePF == -2)
     {
       Serial.println("forward");
     }
     
     else if ((differencePC == 1 && differenceCF == 10 )| (differencePC == -1 && differenceCF == -10))
     {
       Serial.println("Left");
      turnLeft(HPin1, HPin2,HPin3, HPin4, sensor1Max, sensor1Min, counterMax,counterMin); 
     }
     
     else if ((differencePC == 10 && differenceCF == 1 )| (differencePC == -10 && differenceCF == -1))
     {
       Serial.println("Right");
       turnRight(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
     }
     
     else if ((differencePC == 1 && differenceCF == -10) | (differencePC == -1 && differenceCF == 10))
     {
       Serial.println("Right");
       turnRight(HPin1, HPin2,HPin3, HPin4, sensor2Max, sensor2Min, counterMax,counterMin); 
     }

    else if ((differencePC == 10 && differenceCF == -1) | (differencePC == -10 && differenceCF == 1))
    {
      Serial.println("Left");
      turnLeft(HPin1, HPin2,HPin3, HPin4, sensor1Max, sensor1Min, counterMax,counterMin); 
    }
    
    else
    {
      Serial.println("Error!"); 
    }
     
     Serial.println("Complete! Next");
}
   
