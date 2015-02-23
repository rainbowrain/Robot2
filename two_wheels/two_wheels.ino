/*
* Brushed_H_Bridge_simple2 sketch
* commands from serial port control motor direction
* + or - set the direction of rotation of the car (+ for CCW, - for CW), any other key stops the motors
*/
const int in1Pin = 4; // H-Bridge for first motor
const int in2Pin = 2;
const int in3Pin = 6; // H-Bridge pins for second motor
const int in4Pin = 7;
const int enPin1 = 3;
const int enPin2 = 5; 

void setup()
{
Serial.begin(9600);
pinMode(in1Pin, OUTPUT);
pinMode(in2Pin, OUTPUT);
pinMode(in3Pin, OUTPUT);
pinMode(in4Pin, OUTPUT);
Serial.println("+ - sets direction of motors, any other key stops motors");
}
void loop()
{
if ( Serial.available()) {
char ch = Serial.read();
if (ch == '+')
{
Serial.println("CCW");
// first motor
digitalWrite(in1Pin,LOW);
digitalWrite(in2Pin,HIGH);
//second motor
digitalWrite(in3Pin,HIGH);
digitalWrite(in4Pin,LOW);
}
else if (ch == '-')
{
Serial.println("CW");
digitalWrite(in1Pin,HIGH);
digitalWrite(in2Pin,LOW);

digitalWrite(in3Pin,LOW);
digitalWrite(in4Pin,HIGH);
}
else
{
Serial.print("Stop motors");
digitalWrite(in1Pin,LOW);
digitalWrite(in2Pin,LOW);
digitalWrite(in3Pin,LOW);
digitalWrite(in4Pin,LOW);
}
}
}
