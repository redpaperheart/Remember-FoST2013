#include <Servo.h> 

int revs = 0;
int thresh = 60;

// servo
Servo servo;  // create servo object to control a servo 
int pos = 0;    // variable to store the servo position 

// input smoothing
const int numReadings = 5;
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int lastAverage = 0;

void setup(){
  servo.attach(10);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;     
}

void loop(){
  // read pot and map that to servo speed
  float in = analogRead(A4);
  float out = map(in, 0, 1024, 0, 180);
  servo.write(out);
  // read optical encoder to determine revolutions
  readAndSmooth(A5);

  if(lastAverage < thresh && average > thresh){
    if(out > 90){
      revs ++;
      Serial.print("revolution forward: " );
    }
    else{
       revs --;
      Serial.print("revolution back: " );
    }
    Serial.println(revs);
  } 
  
  delay(5);
}

void readAndSmooth(int pin){
  total= total - readings[index];         
  readings[index] = analogRead(pin); 
  total= total + readings[index];       
  index = (index + 1)%numReadings;                    
  lastAverage = average;
  average = total / numReadings;  
//Serial.println(average);  
}

