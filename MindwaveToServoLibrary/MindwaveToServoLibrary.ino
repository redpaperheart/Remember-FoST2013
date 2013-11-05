/*
 MindwaveToServoLibrary, same app but using the ArduinoMindwave library
 The library can be found at https://github.com/redpaperheart/ArduinoMindwave
 
 Created by Adrià Navarro at Red Paper Heart
 To contact, email hello@redpaperheart.com
 */
 
#include <Servo.h>
#include <Mindwave.h>

int potPin = A0;
int ledPin = 12;
int potVal = 0;
int servoPin = 10;
float output = 0;
Servo servo; 
Mindwave mindwave;

//---------------------------------------------------------------------------------

void setup() 
{ 
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  mindwave.setup();
  mindwave.setDebug(true);
} 

void loop() 
{ 
  mindwave.update();
  readControl();
  calculateOutput();
  outputToServo(output);
  debug();
} 

//---------------------------------------------------------------------------------

void readControl(){
  potVal = analogRead(potPin);
}

void outputToServo(float out){
  servo.write(map(out, 0, 100, 180, 0));
}

void calculateOutput(){
  byte attention = mindwave.getMeditation();

  // decide if we use mindReader or manual slider depending on signal quality
  if(mindwave.getPoorQuality() < 27){
    output = map(attention, 10, 80, 0, 100);
  }
  else{
    output = map(potVal, 0, 1023, 0, 100);
  }

  // clamp it
  if(output > 100) output = 100;
  else if (output < 0) output = 0;
}

void debug(){
  if(mindwave.hasNewData() && mindwave.isDebugging()){
    // physical debug
    if(mindwave.getPoorQuality() == 0) digitalWrite(ledPin, HIGH);
    else digitalWrite(ledPin, LOW);    

    // debug logic
    Serial.print("slider: ");
    Serial.print(potVal);
    Serial.print(" output: ");
    Serial.println(output);
    Serial.println(" ");
  }
}
