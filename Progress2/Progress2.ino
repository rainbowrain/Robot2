// go through the array for the coordinates - eventually going to have a program that will produce the array (path) given the start and the end coordinate

/*for example, the array [13, 14, 15, 16, 26, 27, 37, 47, 57, 67];
 we actually want to go from 14 to 67, 13 is a filler. 
 The code that makes the array fills in the "13" assuming that you are in the correct orientation
 and wishes to go straight to the next coordinate, in this case, is 15. It stops at 67, when current pathway is 67
 */
 
#include "coordinateArray.h"
#include "Arduino.h" 
#include "sensor.h"
#include "Robot_Movement.h"
#include "line_count.h"
#include "turn.h"
#define SAFEDISTANCE 7  //in cm 

/*************************Sensor Readings for calibration*******************/
unsigned int sensor1Value = 0;         // the sensor value
unsigned int sensor1Min = 1023;        // minimum sensor value
unsigned int sensor1Max = 0;           // maximum sensor value

unsigned int sensor2Value = 0;         // the sensor value
unsigned int sensor2Min = 1023;        // minimum sensor value
unsigned int sensor2Max = 0;           // maximum sensor value

unsigned int sensor3Value = 0;         // the sensor value
unsigned int sensor3Min = 1023;        // minimum sensor value
unsigned int sensor3Max = 0;           // maximum sensor value
/***************************************************************************/

/***********************linecount*************************/
  unsigned int counter = 0;		// to keep track
  unsigned int counterMax = 0;	
  unsigned int counterMin = 1000000;
/**********************************************************/
void setup()
{
  Serial.begin(9600);
 /************************PINS********************************/
  pinMode(HPin1, OUTPUT);   //for left motor
  pinMode(HPin2, OUTPUT);
  pinMode(HPin3, OUTPUT);   //for right motor
  pinMode(HPin4, OUTPUT);
  pinMode(ePin2, OUTPUT);  //left 
  pinMode(ePin1, OUTPUT);  //right
 /* pinMode(TRIGPIN, OUTPUT);  //distance sensor
  pinMode(ECHOPIN, INPUT);
  
 /*************************************************************/ 
  /*******************Sensor Calibration**********************/
  while (millis() < 2500)
  {
    moveForward(HPin1, HPin2, HPin3, HPin4);  // robot will move forward while adjusting the sensors
    sensor1Value = analogRead(sensorPin1);  
    // record the maximum sensor value
    if (sensor1Value > sensor1Max)
    {
      sensor1Max = sensor1Value;
    }
    // record the minimum sensor value
    if (sensor1Value < sensor1Min) 
    {
      sensor1Min = sensor1Value;
    }
    
    sensor2Value = analogRead(sensorPin2);
    if (sensor2Value > sensor2Max)    //2nd sensor (right sensor)
    {
      sensor2Max = sensor2Value;
    }
    if (sensor2Value < sensor2Min) 
    {
      sensor2Min = sensor2Value;
    }
    
    sensor3Value = analogRead(sensorPin3);
    if (sensor3Value > sensor3Max)    //counter sensor
    {
      sensor3Max = sensor3Value;
    }
    if (sensor3Value < sensor3Min) 
    {
      sensor3Min = sensor3Value;
    }
  }
  /****************************linecounting calibration*********************************/
  unsigned int initial = 0; 
  moveBackward(HPin1, HPin2, HPin3, HPin4);
  while (millis() < 5000)
  {
    unsigned int sensorValue = analogRead(sensorPin3);    //sensor pin at the middle of the board 
    sensorValue = map(sensorValue, sensor3Min, sensor3Max, 0, 10);
    sensorValue = constrain(sensorValue, 0, 10);
		
		//needs such that the robot is on the board
    if (initial == 0)
    {
      if (sensorValue > 8) // sees white
      {
	  Serial.println("Ready to start calibration");
	  initial = 1;
      }
      else if (sensorValue < 8)// sees black
      {
	Serial.println("See black; please place the robot at a white spot");
      }
      else
      {
	Serial.println("please place the robot at a white spot");
      }
    }		
    else
    {
      if (sensorValue < 9)	//possible blackline
      {
	  Serial.println("coming across a blackline?");
          while (sensorValue < 9 && millis() < 5000)		//pull the counters
	  {
            Serial.print ("Sensor: ");
            Serial.println (sensorValue);
            counter++;
            unsigned int sensorValue = analogRead(sensorPin3);    //sensor pin at the middle of the board 
            sensorValue = map(sensorValue, sensor3Min, sensor3Max, 0, 10);
            sensorValue = constrain(sensorValue, 0, 10);
           }
	// record the maximum counter value
	  if (counter > counterMax)
	  {
	    counterMax = counter;
            counter = 0;
          }
          // record the minimum counter value
          if (counter < counterMin) 
          {
	    counterMin = counter;
            counter = 0;
          }
       }
    }
  }
  STOP(HPin1, HPin2, HPin3, HPin4);
  Serial.print("maximum: ");
  Serial.println (counterMax);
  Serial.print("minimum: ");
  Serial.println (counterMin);
  Serial.print("Sensor1Max: ");
  Serial.println (sensor1Max);
  Serial.print("Sensor2Max: ");
  Serial.println (sensor2Max);
  Serial.print("Sensor3Max: ");
  Serial.println (sensor3Max);
  Serial.print("Sensor1Min: ");
  Serial.println (sensor1Min);
  Serial.print("Sensor2Min: ");
  Serial.println (sensor2Min);
  Serial.print("Sensor3Min: ");
  Serial.println (sensor3Min);
/**********************************************************************************/
}

void loop()
{
  if ( Serial.available()) 
  {
    char ch = Serial.read();
    if (ch == '+')
    {  
      unsigned int currentPosition;
      unsigned int pastPosition;
      unsigned int futurePosition; 
      unsigned int i;
      //unsigned int  pathway [] = {13, 14, 15, 16, 26, 27, 37, 47, 57, 67, '\0'};
      //unsigned int  pathway [] = {81, 82, 72, 73, 83, 82, '\0'};
      unsigned int  pathway [] = {62, 61, 71, 72, 73, 83, '\0'};
      for (i = 1; pathway[i + 1]!= '\0'; i++)
      {
        currentPosition = pathway [i];
        pastPosition = pathway[i - 1];
        futurePosition = pathway [i + 1] ;
        unsigned int initial= 0;
        unsigned int line = 0;   
        Serial.print("before line following: ");
        Serial.println(line);
        while(line == 0)
        {
          unsigned int irLeft = irTCRTSensor (sensor1Max, sensorPin1, sensor1Min);  //left 
          unsigned int irRight = irTCRTSensor (sensor2Max, sensorPin2, sensor2Min);  //right
          if (irRight > 8 && irLeft > 8)
          //Right sensor sees and left sensor sees white
          {
            Serial.println("Right 0 AND left 0 : go straight but object may be ahead");
            moveForward(HPin1, HPin2, HPin3, HPin4);
          }
          else if (irLeft < 9 && irRight < 9)   //left and right sensor sees blackline
          {
            Serial.println("Left 1 AND right 1: IR sees nothing");
            moveForward(HPin1, HPin2, HPin3, HPin4);
          }
          else if (irLeft < 9 && irRight > 8)   //left sensor sees blackline 
          {
            Serial.println("Left blackline - left skewed");  
            pivotLeft(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2);
          }
          else if (irRight < 9 && irLeft > 8)    //Right sensor sees blackline 
          {
            Serial.println("Right blackline - right skewed");
            pivotRight(HPin1, HPin2, HPin3, HPin4, ePin1, ePin2);
          }
          else //sees other values
          {
            Serial.println ("please check the sensors, adjust the height");
          }
          
          initial++;
          line = lineCount(sensor3Max, sensor3Min, counterMax, counterMin, 0, sensorPin3);
          Serial.print ("Number of 'lines' passed: ");
          Serial.println(line);
          if (initial < 5)
          {
            line = 0;
          }
        }  //end of while loop
        Serial.println ("Current Position: ");
        Serial.println(currentPosition);
        STOP(HPin1, HPin2, HPin3, HPin4);
        delay(5);
        checkForAction(pastPosition, currentPosition, futurePosition, sensor1Max, sensor2Max, sensor1Min, sensor2Min, counterMax, counterMin);	//to see if you wanna turn or continue
        if (pathway [i + 2] == '\0')
        {
          line = 0;
          while(line == 0)
          {
            unsigned int irLeft = irTCRTSensor (sensor1Max, sensorPin1, sensor1Min);  //left 
            unsigned int irRight = irTCRTSensor (sensor2Max, sensorPin2, sensor2Min);  //right
            if (irRight > 8 && irLeft > 8)
            //Right sensor sees and left sensor sees white
            {
              Serial.println("Right 0 AND left 0 : go straight but object may be ahead");
              moveForward(HPin1, HPin2, HPin3, HPin4);
            }
            else if (irLeft < 9 && irRight < 9)
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
            
            initial++;
            line = lineCount(sensor3Max, sensor3Min, counterMax, counterMin, 0, sensorPin3);
            Serial.print ("Number of 'lines' passed: ");
            Serial.println(line);
            if (initial < 5)
            {
              line = 0;
            }
          }    
        }
    }
      Serial.println("end of for loop");
      pastPosition = currentPosition;
      currentPosition = futurePosition;
      Serial.print("Path is completed! Current Position is: ");
      Serial.print(currentPosition);
      STOP(HPin1,HPin2,HPin3,HPin4);
      delay(100000);
    }
  }
}


	
