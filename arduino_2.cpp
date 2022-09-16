//for arduino 2

int cm; // declaring a variable to store distance..
int t; // declaring a variable to store the duration of received pulse.
// Variable to store sensor values.
int FrontSensor;
int LeftSensor;
int RightSensor;
// Variable for Sensor's Pinn
int forwardTriggerPin = 7;
int forwardEchoPin = 6;
int RightTriggerPin = 3;
int RightEchoPin = 2;
int LeftTriggerPin = 5;
int LeftEchoPin = 4;
void setup()
{
Serial.begin(9600);
// setting up input/output PINS
pinMode(forwardTriggerPin , OUTPUT);
pinMode(forwardEchoPin, INPUT);
pinMode(RightTriggerPin, OUTPUT);
pinMode(RightEchoPin, INPUT);
pinMode(LeftTriggerPin, OUTPUT);
pinMode(LeftEchoPin, INPUT);
for(int i=11; i<=13; i++){
pinMode(i,OUTPUT);
}
}
// Function to calculate Distance of an object
int distance(int tx, int rx){
digitalWrite(tx,LOW);
delayMicroseconds(2);
digitalWrite(tx,HIGH);
delayMicroseconds(10);
digitalWrite(tx,LOW);
t = pulseIn(rx,HIGH);
//Serial.println(t);
cm = t*0.034/2;
//Serial.println(cm);
return cm;
}
// function to decide in which direction bot should move.
void direct()
{
if (FrontSensor > 300 && RightSensor > 300 && LeftSensor > 300)
{
forward();
}
else if (FrontSensor > 300 && RightSensor < 300 && LeftSensor < 300)
{
forward();
}
else if (FrontSensor < 300 && RightSensor < 300 && LeftSensor < 300) // obstacle infront of all 3sides
{
reverse();
delay(500);
if ((LeftSensor) > (RightSensor))
turn_left();
else
turn_right();
//then reverse
}
else if (FrontSensor < 300 && RightSensor < 300 && LeftSensor > 300) // obstacle on right and front sides
{
turn_left(); // turn left side
}
else if (FrontSensor < 300 && RightSensor > 300 && LeftSensor < 300) // obstacle on left and front sides
{
turn_right(); // turn right side
}
else if (FrontSensor < 300 && RightSensor > 300 && LeftSensor > 300) // obstacle on front sides
{
turn_left();
delay(500);
forward(); // then turn right //********************
}
else
{
forward();
}
}
// sends forward command in Binary.
void forward(){
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(13,HIGH);
}
// sends a reverse command in Binary.
void reverse(){
digitalWrite(11,LOW);
digitalWrite(12,HIGH);
digitalWrite(13,LOW);
}
// sends the right command in Binary.
void turn_right(){
digitalWrite(11,LOW);
digitalWrite(13,HIGH);
digitalWrite(12,HIGH);
}
// sends the left command in Binary.
void turn_left(){
digitalWrite(11,HIGH);
digitalWrite(12,LOW);
digitalWrite(13,LOW);
}
// sends stop command in Binary.
void stop(){
digitalWrite(11,LOW);
digitalWrite(12,LOW);
digitalWrite(13,LOW);
}
void loop(){
LeftSensor = distance(LeftTriggerPin , LeftEchoPin);
RightSensor = distance(RightTriggerPin , RightEchoPin);
FrontSensor = distance(forwardTriggerPin , forwardEchoPin);
Serial.print("Front : ");
Serial.println(FrontSensor);
Serial.print("Left : ");
Serial.println(LeftSensor);
Serial.print("Right : ");
Serial.println(RightSensor);
direct();
delay(10); // Wait for 10 milliseconds.
}
