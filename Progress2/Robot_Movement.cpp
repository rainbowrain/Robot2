/* Robot_Movement.cpp
* functions to move the robot
*/
#include "Arduino.h" 
#include "Robot_Movement.h"

void moveForward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{  analogWrite(ePin2, 255);  //right wheel
  analogWrite(ePin1, 255);  //right wheel
  digitalWrite(HPin1,LOW);
  digitalWrite(HPin2,HIGH);  
  digitalWrite(HPin3,LOW);
  digitalWrite(HPin4,HIGH);
}
void moveBackward (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{
  analogWrite(ePin2, 255);  //right wheel
  analogWrite(ePin1, 255);  //right wheel
  digitalWrite(HPin1,HIGH);
  digitalWrite(HPin2,LOW);
  digitalWrite(HPin3,HIGH);
  digitalWrite(HPin4,LOW);
  
}
void STOP (unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{
  digitalWrite(HPin1,LOW);
  digitalWrite(HPin2,LOW);  
  digitalWrite(HPin3,LOW);
  digitalWrite(HPin4,LOW);  
}
void rotateLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{
	analogWrite(ePin1, 255);
	analogWrite(ePin2, 255);
	digitalWrite(HPin2, LOW);
	digitalWrite(HPin1, HIGH);
	digitalWrite(HPin4, HIGH);
	digitalWrite(HPin3, LOW);
}
void rotateRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4)
{
	analogWrite(ePin1, 255);
	analogWrite(ePin2, 255);
	digitalWrite(HPin1, LOW);
	digitalWrite(HPin2, HIGH);
	digitalWrite(HPin3, HIGH);
	digitalWrite(HPin4, LOW);
}

void pivotLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2)
{
  analogWrite(ePin1, TURNING_SPEED_SLOWER_WHEEL);  //left wheel
  analogWrite(ePin2, 255);  //right wheel
  digitalWrite(HPin2,HIGH); 
  digitalWrite(HPin1,LOW);
  digitalWrite(HPin4,HIGH);
  digitalWrite(HPin3,LOW);
}
void pivotRight(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int ePin1, unsigned int ePin2)
{
  analogWrite(ePin2, TURNING_SPEED_SLOWER_WHEEL);  //right wheel
  analogWrite(ePin1, 255);  //left wheel
  digitalWrite(HPin2,HIGH); 
  digitalWrite(HPin1,LOW);
  digitalWrite(HPin4,HIGH);
  digitalWrite(HPin3,LOW);
}
