  #include "Arduino.h"
  #include "RobotNavigation.h"
  
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
  
  
   void checkForAction(unsigned int pastCoordinate, unsigned int currentCoordinate, unsigned int futureCoordinate)
   {
     int differencePC = currentCoordinate - pastCoordinate;
     Serial.println("current - past");
     
     int differenceCF = futureCoordinate - currentCoordinate;
     Serial.println("future - current");
     
     int differencePF = futureCoordinate - pastCoordinate;
     Serial.println("future - past");
     
     if (differencePF == 20 | differencePF == -20 | differencePF == 2 | differencePF == -2)
     {
       Serial.println("forward");
       moveforward();
     }
     else if (differencePC == 1 & differenceCF == 10 | differencePC == -1 & differenceCF = -10)
     {
       turnLeft();
       Serial.println("Left");
     }
     else if (differencePC == 10 & differenceCF == 1 | differencePC == -10 & differenceCF = -1)
     {
       Serial.println("Right");
       turnRight();
     }
     else if (differencePC == 1 & differenceCF == -10 | differencePC == -1 & differenceCF = 10)
     {
       Serial.println("Right");
       turnRight();
     }

	 else if (differencePC == 10 & differenceCF == -1 | differencePC == 10 & differenceCF = -1)
	 {
		 Serial.println("Left");
		 turnLeft(); 
	 }
     else
     {
        Serial.println("Error!"); 
     }
     
   }
   
