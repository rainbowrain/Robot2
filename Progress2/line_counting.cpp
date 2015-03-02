// test line counting using IRCT 5000
#include "Arduino.h"
#include "Robot_Movement.h"
#include "sensor.h"


/*
fuction counts the number of lines and the value is stored in lineCounter
this uses two sensors - the left and right.
Assumption: it will detect the black line and not miss it
Note: a program running the line following will be in setup and will set the max and min counter
*/

/*The thing should STOP and then this function should be called, counter should be declared and set to 0*/
unsigned int lineCount(unsigned int sensorMax, unsigned int sensorMin, unsigned int counterMax, unsigned int counterMin,unsigned int initialLineCount, unsigned int sensorPin)
{
	unsigned int lineCounter = initialLineCount;	//number of lines that was passed already
	unsigned sensorValue = irTCRTSensor(sensorMax, sensorPin, sensorMin);		// seeing the black line?
	unsigned int counter = 0;		// checkpoint for if it is a black line or is it nonsense?
	if (sensorValue < 9)	//possible blackline
	{
		//Serial.println("comming across a blackline?");

		while (sensorValue < 9)		//pull the sensors
		{
			sensorValue = irTCRTSensor(sensorMax, sensorPin, sensorMin);
			counter++;
		}

		//Serial.print("not infinite loop! number of times it sees the black line: ");

		if (counter > (2 / 3 * counterMax) && counter < (2 * counterMax));	// if the counter tells me that it is reasonsable:
		{
			lineCounter++;
			return (lineCounter);						// this will become the next initialLineCount as declared in the main loop
		}
        }
	else
	{
		delay(1);
		return (lineCounter);				
	}
}

