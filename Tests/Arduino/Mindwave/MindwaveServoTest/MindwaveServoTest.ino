#include <Servo.h> 

// servo
Servo servo; 
int servopin = 10;
int potpin = A5;  
int inputval;  
int outputval = 90;   
int targetOutput = 90;

// mindwave
#define BAUDRATE 57600  // for bluetooth and serial debug
#define DEBUGOUTPUT 1 

// parsing + checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {
  0};
long lastReceivedPacket = 0;
boolean bigPacket = false;

// mindwave output
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

void setup() 
{ 
  servo.attach(servopin);  // attaches the servo on pin 9 to the servo object
  Serial.begin(BAUDRATE);
} 

void loop() 
{ 
  //inputval = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  //outputval = map(inputval, 0, 1023, 0, 180);    // full rotation servo we dont specify the angle but the speed
  parseMindwave();
  //outputval = 0.95 * outputval + 0.05 * targetOutput;
  //servo.write(outputval);                  // sets the servo position according to the scaled value 

    // add poorquality threshold
  if(bigPacket){ // we have new data
    if(poorQuality < 50){
      //Serial.print("meditation: " );                       
      //Serial.print(meditation);
      //outputval = map(attention, 0, 100, 180, 0);    // full rotation servo we dont specify the angle but the speed
      if(attention > 65){
        outputval = 60;
        Serial.println(" -> UP!");
      }
      else if(attention < 35){
        outputval = 120;
        Serial.println(" -> DOWN ");
      }
      else{
        outputval = 90;
        Serial.println(" -> still ");
      }

      //Serial.print("Output: " );                       
      //Serial.println(outputval);
      servo.write(outputval);                  // sets the servo position according to the scaled value 
    }
    else servo.write(90);
  }


  //delay(15);  
} 


