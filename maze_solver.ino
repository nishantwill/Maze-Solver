// for arduino 1

#include <LiquidCrystal.h>
LiquidCrystal lcd(13,A0,A1,A2,A3,A4);
// C++ code
// Arduino1 pins used for the motors
#define in1 7
#define in2 2
#define in3 4
#define in4 5
#define enA 3
#define enB 6
// Arduino pins used for the switches
#define S1 8 // Most Significant
#define S2 9
#define S3 10 // Least Significant
// State of each switch (0 or 1)
int s1state;
int s2state;
int s3state;
// Initial Potentiometer val
int potVal=255;
int speed;
void setup()
{
Serial.begin(9600);
lcd.begin(16,2);
// pins for switches are inputs
pinMode(S1, INPUT);
pinMode(S2, INPUT);
pinMode(S3, INPUT);
pinMode(A5, INPUT); // Analog pin5 is configured as input
// Set all the motor control pins to outputs
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(enA, OUTPUT);
pinMode(enB, OUTPUT);
}
// moves forward
void forward()
{
potVal = analogRead(A5); // Reads the analog value from the Ariduino-2.
potVal = map(potVal,0,1023,0,255); // Maps the potentiometer readings from [0,1023] to [0,255].
speed = (16530/255)*potVal;
analogWrite(enA, potVal);
analogWrite(enB, potVal);
// Move forward
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}
// moves backward
void backward()
{
potVal = analogRead(A5); // Reads the analog value from Potentiometer.
potVal = map(potVal,0,1023,0,255); // Maps the potentiometer readings from [0,1023] to [0,255].
speed = (16530/255)*potVal; // calculates the speed
analogWrite(enA, potVal); // Generates PWM for motor A
 analogWrite(enB, potVal); // Generates PWM for motor B
// Rotates the wheels opposite
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}
// turns right
void right()
{
potVal = analogRead(A5); // Reads the analog value from Potentiometer.
potVal = map(potVal,0,1023,0,255); // Maps the potentiometer readings from [0,1023] to [0,255].
speed = (16530/255)*potVal; // calculates the speed
analogWrite(enA, potVal); // Generates PWM for motor A
// Move right
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}
// turns left
void left()
{
potVal = analogRead(A5); // Reads the analog value from Potentiometer.
potVal = map(potVal,0,1023,0,255); // Maps the potentiometer readings from [0,1023] to [0,255].
speed = (16530/255)*potVal; // calculates the speed
analogWrite(enB, potVal); // Generates PWM for motor B
// Move left
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
}
void loop()
{
delay(100);
// Reads the Switches' state
s1state = digitalRead(S1);
s2state = digitalRead(S2);
s3state = digitalRead(S3);
if (s1state == 0 && s2state == 0 && s3state == 0)
{
lcd.setCursor(0,0);
lcd.print("speed(RPM):0 ");
lcd.setCursor(0,1);
lcd.print("STOP ");
analogWrite(enA, 0);
analogWrite(enB, 0);
// Turn off the motor
digitalWrite(in1, LOW);
digitalWrite(in2, LOW);
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
}
else if (s1state == 0 && s2state == 0 && s3state == 1)
{
forward();
lcd.setCursor(0,0);
lcd.print("speed(RPM):");
lcd.setCursor(11,0);
lcd.print(" ");
lcd.setCursor(11,0);
lcd.print(speed);
lcd.setCursor(0,1);
lcd.print("Forward ");
}
else if (s1state == 0 && s2state == 1 && s3state == 0)
{
backward();
lcd.setCursor(0,0);
lcd.print("speed(RPM):");
lcd.setCursor(11,0);
lcd.print(" ");
lcd.setCursor(11,0);
lcd.print(speed);
lcd.setCursor(0,1);
lcd.print("Backward");
}
else if (s1state == 0 && s2state == 1 && s3state == 1)
{
lcd.setCursor(0,0);
lcd.print("speed(RPM):");
lcd.setCursor(11,0);
lcd.print(" ");
lcd.setCursor(11,0);
lcd.print(speed);
lcd.setCursor(0,1);
lcd.print("Right ");
right();
}
else if (s1state == 1 && s2state == 0 && s3state == 0)
{
lcd.setCursor(0,0);
lcd.print("speed(RPM):");
lcd.setCursor(11,0);
lcd.print(" ");
lcd.setCursor(11,0);
lcd.print(speed);
lcd.setCursor(0,1);
lcd.print("Left ");
left();
}
}