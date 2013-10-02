#include <Servo.h> 
//#include <VarSpeedServo.h>


Servo myservo;
//VarSpeedServo myservo; 

int potPin = A0;
int servoPin = 10;

void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  //myservo.attach(10, 0, 180);
  //myServo.slowmove (0, 150);
  Serial.begin(9600);
} 


void loop() 
{ 
  int in = analogRead(potPin);
  int out = map(in, 0, 1023, 0, 180);
  Serial.print(in);
  Serial.print(" -> ");
  Serial.println(out);

  myservo.write(out);
  //myservo.slowmove (out, 50);

  delay(20);
} 

