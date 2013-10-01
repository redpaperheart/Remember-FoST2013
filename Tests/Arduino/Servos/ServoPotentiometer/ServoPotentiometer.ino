#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 
boolean dir = false;

void setup() 
{ 
  myservo.attach(10);  // attaches the servo on pin 9 to the servo object 
  //myServo.attach(10, 0, 180);
  //myServo.slowmove (0, 150);
  Serial.begin(9600);
} 


void loop() 
{ 
  float in = analogRead(A5);
  float out = map(in, 0, 1024, 0, 180);
  Serial.println(in);
  Serial.println(out);

  myservo.write(out);
  delay(20);
  
  /*
  for(pos = 0; pos < 180; pos += 1)  // goes from 0 degrees to 180 degrees 
   {                                  // in steps of 1 degree 
   myservo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(15);                       // waits 15ms for the servo to reach the position 
   } 
   delay(2000);
   for(pos = 180; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
   {                                
   myservo.write(pos);              // tell servo to go to position in variable 'pos' 
   delay(15);                       // waits 15ms for the servo to reach the position 
   } */



  /*if(dir == false){
   myservo.write(180);
   delay(1000);
   dir = true;
   }
   else{
   myservo.write(0);
   delay(1000);
   dir = false;
   }
   */
} 

