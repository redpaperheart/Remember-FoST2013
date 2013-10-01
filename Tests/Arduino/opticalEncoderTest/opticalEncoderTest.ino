// wiring based on this tutorial
// http://bildr.org/2011/03/various-proximity-sensors-arduino/

int revs = 0;
int thresh = 500;

// input smoothing
const int numReadings = 5;
int readings[numReadings];      // the readings from the analog input
int index = 0;                  // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average
int lastAverage = 0;

void setup(){
  Serial.begin(9600);
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;     
}

void loop(){
  readAndSmooth(A5);
  
  if(lastAverage < thresh && average > thresh){
    revs ++;
    Serial.print("new revolution: " );
    Serial.println(revs);
  }
  
  delay(15);
}

void readAndSmooth(int pin){
  total= total - readings[index];         
  readings[index] = analogRead(pin); 
  total= total + readings[index];       
  index = (index + 1)%numReadings;                    
  lastAverage = average;
  average = total / numReadings;         
}

