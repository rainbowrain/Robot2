  #include "Arduino.h"
  #include "RobotMovement.h"

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
void turnLeft()
{
	while (counter < 2)
	{
		rotateLeft();	//right wheel forward and left wheel backwards
		LeftValue = irTCRTSensor (sensorMax, sensorPin, sensorMin);
		if (LeftValue >	WHITE_VALUE)
		{
			Serial.println("White!");
		}
		else if (LeftValue < BLACK_VALUE)
		{
			Serial.println("I maybe seeing the black line");
			while (LeftValue < BLACK_VALUE)
			{
				irTracker= irDetect(IR_LED_PIN_3, IR_RECEIVER_PIN_3,FREQUENCY);
				counter2 += 1;
			}
			Serial.print("number of times it sees the black line: ");
			Serial.println (counter2);
			
			if (counter2 > /*value to be defined*/);
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
}