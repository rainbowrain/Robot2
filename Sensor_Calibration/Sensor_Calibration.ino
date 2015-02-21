/*calibrations for analog IR sensors*/
//Feb 14, 2015

/********************intstucutions****************************/
/*
Note that the ir calibrated is connected to analog pin A1
it is assumed that the difference between sensors is negligible

The serial will out put numbers 1 to 5000 - indicating that there is 5s for the
ir to be exposed to different colours and distances

then, it will show the orignial reading and then the calibrated reading
note that the calibrated reading is from 0 to 10 (using map function)

*/

const unsigned int sensorPin = A1;    // pin that the sensor is attached to
const unsigned int ledPin = 9;        // pin that the LED is attached to

// variables:
unsigned int sensorValue = 0;         // the sensor value
unsigned int sensorMin = 1023;        // minimum sensor value
unsigned int sensorMax = 0;           // maximum sensor value


void setup() 
{
 // digitalWrite(SIGNALPIN, HIGH);
 // calibrate during the first five seconds 
  Serial.begin(9600);
  while (millis() < 5000)
  {
    sensorValue = analogRead(sensorPin);

    // record the maximum sensor value
    if (sensorValue > sensorMax)
    {
      sensorMax = sensorValue;
    }

    // record the minimum sensor value
    if (sensorValue < sensorMin) 
    {
      sensorMin = sensorValue;
    }
    Serial.println(millis());
  }

 // signal the end of the calibration period
  
 // digitalWrite(SIGNALPIN, LOW);
}

void loop()
{
  // read the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.print("Pre-Calibration reading: ");
  Serial.println(sensorValue);

  // apply the calibration to the sensor reading
  sensorValue = map(sensorValue, sensorMin, sensorMax, 0, 10);
  sensorValue = constrain(sensorValue, 0, 10);
  Serial.print("After calibration: ");
  Serial.println(sensorValue);

  // fade the LED using the calibrated value:
  analogWrite(ledPin, sensorValue);//
  delay(1000);
}
