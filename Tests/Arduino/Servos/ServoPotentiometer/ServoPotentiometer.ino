#include <Servo.h> 

Servo myservo;
int potPin = A0;
int servoPin = 10;

void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  //myServo.attach(10, 0, 180);
  //myServo.slowmove (0, 150);
  Serial.begin(9600);
} 


void loop() 
{ 
  float in = analogRead(potPin);
  float out = map(in, 0, 1023, 0, 180);
  Serial.print(in);
  Serial.print(" -> ");
  Serial.println(out);

  myservo.write(out);
  delay(20);
} 

