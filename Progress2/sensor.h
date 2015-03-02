/*
*Sensors.h
*Contains: 
*  - IR sensor
*  - Distance sensor
*/

#include "Arduino.h"
const unsigned int sensorPin1 = A1;    // left sensor
const unsigned int sensorPin2 = A0;    // right sensor
const unsigned int sensorPin3 = A2;    // counterpin 1  the one at the middle
const unsigned int sensorPin4 = A3;    // counterpin 2  the one at the edge

unsigned int irTCRTSensor (unsigned int sensorMax, unsigned int sensorPin, unsigned int sensorMin);

/*
const unsigned int IRLEDPIN1 = 9;
const unsigned int IRRECEIVERPIN1 = 8;  //left 
const unsigned int IRLEDPIN2 = ;
const unsigned int IRRECEIVERPIN2 = 10; //right 
const unsigned int FREQUENCY = 37900;
unsigned int irDetect(unsigned int irLedPin, unsigned int irReceiverPin, unsigned int frequency);
*/
const unsigned int TRIGPIN = 12;
const unsigned int ECHOPIN = 11; 
//long distanceDetect(unsigned int trigPin, unsigned int echoPin);

