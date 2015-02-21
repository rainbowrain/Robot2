/* Robot_Naviagation.cpp
* functions to move the robot
*/
#include "Arduino.h" 
#include "Sensor.h"

unsigned int irDetect(unsigned int irLedPin, unsigned int irReceiverPin, unsigned int frequency)
{
  tone(irLedPin, frequency); 
  delay(1); // Wait 2 ms
  unsigned int ir = digitalRead(irReceiverPin); 
  delay(1); // Down time before recheck
  noTone(irLedPin);
  return ir;
}
