'''
Reading "hello world from serial"

void setup(){
// Open serial connection.
Serial.begin(9600);
 
}
 
void loop(){
Serial.print("Hello world");
delay(10); // ms
 
}
'''



import serial
import time
ser = serial.Serial('COM3', 9600, timeout=0)
 
while 1:
 try:
  print ser.readline()
  time.sleep(1)
 except ser.SerialTimeoutException:
  print('Data could not be read')
  time.sleep(1)
