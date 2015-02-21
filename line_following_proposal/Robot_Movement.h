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
  const unsigned int enPin1 = 12; 
  const unsigned int enPin2 = 13; 

  const unsigned int TURNING_SPEED_SLOWER_WHEEL = 200;
 // const unsigned int ROTATIONAL_SPEED = ;
 
  void moveForward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void moveBackward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void STOP (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void turnLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void turnRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void rotate(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  void pivotLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2);
  void pivotRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2);
