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
  
  