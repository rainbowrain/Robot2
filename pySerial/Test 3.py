''' Reading data from sensor and printing that to computer

int lightPin = 1;
float lightValue;
 
void setup(){
  pinMode(ledPin, OUTPUT);
}
 
void loop(){
  lightValue = analogRead(lightPin);
  Serial.println(lightValue);
  delay(1000);
  }

'''

import serial
import time
ser = serial.Serial('COM4', 9600, timeout=0)
while 1:
    try:
        print ser.readline()
        time.sleep(1)
    except ser.SerialTimeoutException:
        print('Data could not be read')
    time.sleep(1)

    
# you can use the data and graph it/save it as a file
