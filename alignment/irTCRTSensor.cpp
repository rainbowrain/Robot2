// function that reads analog pins and calibrates them

  #include "Arduino.h"
  #include "sensor.h"
  
unsigned int irTCRTSensor (unsigned int sensorMax, unsigned int sensorPin, unsigned int sensorMin)
{
  unsigned int sensorValue = analogRead(sensorPin);
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 10);
  sensorValue = constrain(sensorValue, 0, 10);
  return (sensorValue);
}
