/*
*Sensors.h
*Contains: 
*  - IR sensor
*  - Distance sensor
*/

#include "Arduino.h"

const unsigned int IRLEDPIN1 = 6;
const unsigned int IRRECEIVERPIN1 = 7;
const unsigned int IRLEDPIN2 = 8;
const unsigned int IRRECEIVERPIN2 = 9;
const unsigned int FREQUENCY = 37900;

const unsigned int TRIGPIN = 10;
const unsigned int ECHOPIN = 11; 

unsigned int irDetect(unsigned int irLedPin, unsigned int irReceiverPin, unsigned int frequency);
long distanceDetect(unsigned int trigPin, unsigned int echoPin);


