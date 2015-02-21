  #include "Arduino.h"


  const unsigned int WHITE_VALUE = 8;
  const unsigned int BLACK_VALUE = 3;
  const unsigned int LINENUMBER = 1000;
  
  void rotate(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4);
  
  void turnLeft(unsigned int HPin1, unsigned int HPin2, unsigned int HPin3, unsigned int HPin4, unsigned int pastCoordinate, unsigned int currentCoordinate, unsigned int futureCoordinate, unsigned int sensorMax, unsigned int sensorMin, unsigned int sensorPin1, unsigned int sensorPin3,  unsigned int counter, /*pointer to the list of coordinate(map)*/  unsigned int n);
  
  unsigned int irTCRTSensor (unsigned int sensorMax, unsigned int sensorPin, unsigned int sensorMin);
