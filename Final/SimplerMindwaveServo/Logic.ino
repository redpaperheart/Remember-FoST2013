
void outputToServo(float out){
  //servo.slowmove(map(out, 0, 100, 0, 180), servoSpeed);
  servo.write(map(out, 0, 100, 180, 0));
}

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
    targetOutput = map(val, 20, 100, 0, 100);
  }
  else{
    targetOutput = 0.0;
    lastAttention = 0.0;
    lastMeditation = 0.0;
    targetOutput = potVal;
  }

  // damp current output
  if(bDamp){
    if(millis() - lastDamp > dampFreq){
      output = (1-damping) * output + damping * targetOutput; 
      lastDamp = millis();
    }
  }
  else{
    output = targetOutput;
  }
}


void processNewData(){
  if(bigPacket){ // we have new data
    lastPoorQuality = poorQuality;
    lastAttention = attention;
    lastMeditation = meditation;
  }
}



