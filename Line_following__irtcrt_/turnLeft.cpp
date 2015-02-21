  #include "Arduino.h"
  #include "turn.h"
  #include "sensor.h"

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


void turnLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int pastCoordinate, unsigned int currentCoordinate, unsigned int futureCoordinate, unsigned int sensorMax, unsigned int sensorMin, unsigned int sensorPin1, unsigned int sensorPin3,  unsigned int counter, /*pointer to the list of coordinate(map)*/  unsigned int n)

{
	unsigned int counter2;
        unsigned int LeftValue;
        unsigned int irTracker;
        counter2 =0;
	while (counter < 2)
	{
		rotate( HPin1, HPin2, HPin3,HPin4);	//right wheel forward and left wheel backwards
		LeftValue = irTCRTSensor (sensorMax, sensorPin1, sensorMin);
		if (LeftValue >	WHITE_VALUE)
		{
			Serial.println("White!");
		}
		else if (LeftValue < BLACK_VALUE)
		{
			Serial.println("I maybe seeing the black line");
			while (LeftValue < BLACK_VALUE)
			{
				irTracker = irTCRTSensor (sensorMax, sensorPin3, sensorMin);
				counter2 += 1;
			}
			Serial.print("number of times it sees the black line: ");
			Serial.println (counter2);
			
			if (counter2 > LINENUMBER)
			{
				counter++;
				Serial.print("number of Black lines passed:");
				Serial.println(counter);
				
			}
			else
			{
				Serial.println("That was not a black line");
			}
		}
		else 
		{
			Serial.println("ERROR! (does not detect)");
		}
	
	}
	pastCoordinate = currentCoordinate;
	currentCoordinate = futureCoordinate;
	//futureCoordinate = /*list [n + 1]*/;
}
void rotate(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{
  /**/
  digitalWrite(HPin1,LOW);
  digitalWrite(HPin2,HIGH);  
  
  digitalWrite(HPin3,HIGH);
  digitalWrite(HPin4,LOW);
}
