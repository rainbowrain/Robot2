/*
*  Robot_Movement.h
* Library header file for Robot_Movement functions
*/
  #include "Arduino.h"
  /*left wheel pins*/
  const unsigned int HPin1 = 2; 
  const unsigned int HPin2 = 3; 
  /*right wheel pins*/
  const unsigned int HPin3 = 4; 
  const unsigned int HPin4 = 5; 
  
  /*Speed control pins*/
  const unsigned int ePin1 = 9; 
  const unsigned int ePin2 = 10; 

 const unsigned int TURNING_SPEED_SLOWER_WHEEL = 0;
 // const unsigned int TURNING_SPEED_FASTER_WHEEL = ;
 // const unsigned int ROTATIONAL_SPEED = ;
  
  void moveForward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void moveBackward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void STOP (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void rotateLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void rotateRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void pivotLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2);
  void pivotRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2);
  
  void hopperAlignment(long originalDistance, long distanceAligned);
void gameboardAlignment(unsigned int pastCoordinate,unsigned int currentCoordinate, unsigned int sensor1Max, unsigned int sensor2Max, unsigned int sensor1Min, unsigned int sensor2Min, unsigned int counterMax, unsigned int counterMin);
