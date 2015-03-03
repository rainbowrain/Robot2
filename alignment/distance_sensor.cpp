/* distance_sensor.cpp
* functions to sence the distance of an object infront of the robot
*/
#include "Arduino.h" 
#include "sensor.h"

long distanceDetect(unsigned int trigPin, unsigned int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration/2) / 29.1; 

  return distance;
}
