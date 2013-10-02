//#include <VarSpeedServo.h>
#include <Servo.h>

// control
int potPin = A0;
int switchPin = 2;
int ledPin = 12;
int potVal = 0;

// servo
Servo servo; 
int servoPin = 10;
int servoSpeed = 200;

// mindwave
#define BAUDRATE 57600  // for bluetooth and serial debug
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
long lastReceivedPacket = 0;
boolean bigPacket = false;

// mindwave output
byte poorQuality = 250;
byte attention = 0;
byte meditation = 0;
byte lastPoorQuality = 250;
byte lastAttention = 0;
byte lastMeditation = 0;

// installation logic
boolean bDamp = false;
boolean bDebug = true;
boolean useMeditation = false;
int activationThresh = 60;
float damping = 0.025;
unsigned long dampFreq = 17; //about 60fps
unsigned long lastDamp = 0;
unsigned long timeOverThresh = 0;
unsigned long timeUnderThresh = 0;
unsigned long timeGrown = 0;
unsigned long lastMillis;
float output = 0;

//---------------------------------------------------------------------------------

void setup() 
{ 
  Serial.begin(BAUDRATE);
  //servo.attach(servoPin, 0, 180);
  servo.attach(servoPin);
} 

void loop() 
{ 
  readControl();
  parseMindwave();
  processNewData();
  calculateOutput();

  if(bDebug && bigPacket){
    physicalDebug();
    debugInput();
    debugLogic();
  }
  outputToServo(output);
} 

void readControl(){
  // we can map to the potentiometer to different parameters
  //activationThresh = map(analogRead(potPin), 0, 1023, 0, 100);
  //servoSpeed = map(analogRead(potPin), 0, 1023, 0, 255);
  potVal = analogRead(potPin);
  useMeditation = digitalRead(switchPin);
}

void physicalDebug(){
  if(poorQuality == 0) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

void debugInput(){
  Serial.print("PoorQuality: ");
  Serial.print(poorQuality, DEC);
  Serial.print(" Attention: ");
  Serial.print(attention, DEC);
  Serial.print(" Meditation: ");
  Serial.print(meditation, DEC);
  Serial.print(" Time since last packet: ");
  Serial.print((millis() - lastReceivedPacket)/1000.0, 3);
  lastReceivedPacket = millis();
  Serial.print("\n");
}

void debugLogic(){
  Serial.print("state: ");
  Serial.print(state);
  Serial.print(" timeUnderThresh: ");
  Serial.print(timeUnderThresh);
  Serial.print(" timeOverThresh: ");
  Serial.print(timeOverThresh);
  Serial.print(" timeGrown: ");
  Serial.print(timeGrown);
  Serial.print(" output: ");
  Serial.println(output);
  Serial.println(" ");
}

//---------------------------------------------------------------------------------















