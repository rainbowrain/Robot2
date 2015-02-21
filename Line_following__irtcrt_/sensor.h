/*
*Sensors.h
*Contains: 
*  - IR sensor
*  - Distance sensor
*/

#include "Arduino.h"
const unsigned int sensorPin1 = A1;    // pin that the sensor is attached to
const unsigned int sensorPin2 = A0;    // pin that the sensor is attached to
unsigned int irTCRTSensor (unsigned int sensorMax, unsigned int sensorPin, unsigned int sensorMin);

/*
const unsigned int IRLEDPIN1 = 9;
const unsigned int IRRECEIVERPIN1 = 8;  //left 
const unsigned int IRLEDPIN2 = ;
const unsigned int IRRECEIVERPIN2 = 10; //right 
const unsigned int FREQUENCY = 37900;
unsigned int irDetect(unsigned int irLedPin, unsigned int irReceiverPin, unsigned int frequency);
*/

/*
const unsigned int TRIGPIN = 10;
const unsigned int ECHOPIN = 11; 
long distanceDetect(unsigned int trigPin, unsigned int echoPin);
*/

