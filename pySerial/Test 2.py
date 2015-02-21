'''Arduino read data from pySerial

This is useful for when you want to check if your program does what it should
when given input from python - debugging w/o circuit input


Audunio code:
int incomingByte = 0;
 
void setup(){
// Open serial connection.
Serial.begin(9600);
 
}
 
void loop(){
if (Serial.available() > 0) {
 // read the incoming byte:
 incomingByte = Serial.read();
 
 // say what you got:
 Serial.print("I got: "); // ASCII printable characters
 Serial.println(incomingByte, DEC);
}
 
}
'''

import serial
import time
ser = serial.Serial('COM3', 9600, timeout=0)
var = raw_input("Enter something: ")
ser.write(var)
while 1:
    try:
        print ser.readline()
        time.sleep(1)
    except ser.SerialTimeoutException:
        print('Data could not be read')
