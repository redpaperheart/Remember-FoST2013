#include <VarSpeedServo.h>
#include <AccelStepper.h>

// servo
VarSpeedServo servo; 
int servoPin = 10;

// stepper
int stepperPinDir = 8;
int stepperPintStep = 9;
int stepperCicle = 1000; // 3 revolutions at 1.8 degree steps
AccelStepper stepper(1, stepperPintStep, stepperPinDir); 

// mindwave
#define BAUDRATE 57600  // for bluetooth and serial debug
#define DEBUGOUTPUT 1 
boolean bDebug = true;

// parsing + checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {
  0};
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
boolean useMeditation = false;
float damping = 0.025;
unsigned long dampFreq = 17; //about 60fps
unsigned long lastDamp = 0;
int activationThresh = 60;
unsigned long timeOverThresh = 0;
unsigned long timeUnderThresh = 0;
unsigned long timeGrown = 0;
unsigned long lastMillis;
int state = 0; // state machibne - 0:waiting to grow, 1:grown, 2: waiting to die 
String states[] = {
  "0- waiting to grow", "1- growing", "2- waiting to die"};
float output = 0;

//---------------------------------------------------------------------------------

void setup() 
{ 
  Serial.begin(BAUDRATE);

  servo.attach(servoPin, 0, 180);
  stepper.setMaxSpeed(3000);
  stepper.setSpeed(3000);
  stepper.setAcceleration(1000);
} 

void loop() 
{ 
  parseMindwave();
  processNewData();
  calculateOutput();

  if(bDebug && bigPacket){
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
  //outputWithServo(output);
  outputWithStepper(output);
} 

//---------------------------------------------------------------------------------

void calculateOutput(){
  // decide if we use meditation or attention
  int val = useMeditation? (int)lastMeditation : (int)lastAttention;

  // count time spent in every state
  int deltaTime = millis() - lastMillis;
  lastMillis = millis();

  if (val > activationThresh) {
    timeOverThresh += deltaTime;
    timeUnderThresh = 0;
  }
  else {
    timeUnderThresh += deltaTime;
    timeOverThresh = 0;
  }

  // installation logic
  float targetOutput = 0;
  if(lastPoorQuality < 26){
    if (state == 0) { // waiting to grow
      targetOutput = map(val, 0, 100, 0, 50);
      if (timeOverThresh > 5000) {
        changeState(1);
      }
    }
    else if (state == 1) { // grown
      targetOutput = 100;
      timeGrown += deltaTime;
      if (timeGrown > 10000) {
        changeState(2);
      }
    }
    else if (state == 2) { // waiting to die
      targetOutput = map(val, 0, 100, 90, 100);
      if (timeUnderThresh > 5000) {
        changeState(0);
      }
    }
  }
  else{
    targetOutput = 0.0;
    lastAttention = 0.0;
    lastMeditation = 0.0;
  }

  // damp current output
  if(millis() - lastDamp > dampFreq){
    output = (1-damping) * output + damping * targetOutput; 
    lastDamp = millis();
  }
  //output = targetOutput;
}

void countTime(int val){

}

void processNewData(){
  if(bigPacket){ // we have new data
    lastPoorQuality = poorQuality;
    lastAttention = attention;
    lastMeditation = meditation;
  }
}

void changeState(int s) {
  state = s;
  timeGrown = 0;
  timeOverThresh = 0;
  timeUnderThresh = 0;
}













