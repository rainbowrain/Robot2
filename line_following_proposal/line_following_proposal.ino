/*
* added irTracker, to make the robot being about to naviage in a circuit Jan 30, 2015
* line following code using 3 IRS. Feb 9, 2015
*
*/
#include "sensor.h"
#include "Robot_Movement.h"


void setup()
{
  Serial.begin(9600);
  pinMode(IR_RECEIVER_PIN_1 , INPUT); 
  pinMode(IR_LED_PIN_1 , OUTPUT); 
  pinMode(IR_RECEIVER_PIN_2 , INPUT); 
  pinMode(IR_LED_PIN_2 , OUTPUT);   
  pinMode(IR_RECEIVER_PIN_3 , INPUT); 
  pinMode(IR_LED_PIN_3 , OUTPUT);   
}

void loop()
{
  //Getting the IR readings 
  unsigned int irLeft = irDetect(IR_LED_PIN_2, IR_RECEIVER_PIN_2,FREQUENCY); 
  delay(1);
  unsigned int irRight = irDetect(IR_LED_PIN_1, IR_RECEIVER_PIN_1,FREQUENCY); 
  delay(1);
  unsigned int irTracker;
  unsigned int counter = 0; // Counts the number of gridlines that it passes
  unsigned int counter2 = 0;
  
  // insert loop to poll the ir tracker
  while (irTracker == 1)
  {
    irTracker= irDetect(IR_LED_PIN_3, IR_RECEIVER_PIN_3,FREQUENCY);
    counter2 += 1;
  }
  Serial.println ("number of times it sees the black line");
  Serial.println (counter2);
  
  if (counter2 > /*value to be defined*/);
  {
    
    Serial.print("number of lines passed:");
    Serial.println(counter);
    
    // insert function that looks at path - returns an array of numbers (coordinates that needs to be conquered) 
    // if function doesn't work, hard code things in (look up table)
    
    
    if (counter <= maxCount) // maxCount is determined by the path 
                            //(numbers of points before a turn) determined by "breadth first algorithm"
    {
      if (pathleft)//pathleft is dictated by path; ( = 1) if a left turn should happen
      {
        turnLeft(HPin1, HPin2, HPin3, HPin4);
      }
      else
      {
        turnRight(HPin1, HPin2, HPin3, HPin4);
      }
      counter == 0;
    }
  }
  else
  {
    counter2 = 0;
  }
   

    
  
  if (irRight == 0 && irLeft == 0 | irRight == 1 && irLeft == 1)
  //Both sensors sees black of both sees White
  {
    Serial.println("Go straight");
    //Call moveForward function that sets the motor pins to HIGH and LOW
    moveForward (HPin1, HPin2, HPin3, HPin4);
  }
  else if (irRight == 1)
  //Right sensor sees black line only
  {
    Serial.println("Right-Skewed");
    //Call turnLeft function that slows the left motor via enable pin
    pivotLeft(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2);
  }
  else 
  //left sensor sees black line only
  {
    Serial.println("Left-Skewed");
    //Call turnRight function that slows the right motor via enable pin
    pivotRight(HPin1, HPin2, HPin3, HPin4,ePin1, ePin2); 
  }
}

