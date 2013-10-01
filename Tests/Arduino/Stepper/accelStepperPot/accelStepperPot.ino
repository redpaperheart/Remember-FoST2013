//This is an example of how you would control 1 stepper

#include <AccelStepper.h>

int motorSpeed = 1000; //9600; //maximum steps per second (about 3rps / at 16 microsteps)
int motorAccel = 10000; //80000; //steps/second/second to accelerate
int motorCicle = 200; //10000; //5 revolutions

int motorDirPin = 8; //digital pin 2
int motorStepPin = 9; //digital pin 3

//set up the accelStepper intance
//the "1" tells it we are using a driver
AccelStepper stepper( AccelStepper::DRIVER, motorStepPin, motorDirPin); 

void setup(){
 stepper.setMaxSpeed(motorSpeed);
 stepper.setSpeed(motorSpeed);
 stepper.setAcceleration(motorAccel);
 
 stepper.moveTo(16000); //move 32000 steps (should be 10 rev)
  stepper.setSpeed(500);
  stepper.runSpeedToPosition();
 Serial.begin(9600);
}

void loop(){
  /*
  float in = analogRead(A5);
  float out = map(in, 0, 1024, 0, motorCicle);
  Serial.print("in: ");
  Serial.print(in);
  Serial.print(" out: ");
  Serial.println(out);
  */
  
  stepper.moveTo(out);
  tepper.setSpeed(200);
  stepper.runSpeedToPosition();
  delay(25);
  
 }
 
 //these must be called as often as possible to ensure smooth operation
 //any delay will cause jerky motion
 //stepper.run();
}
