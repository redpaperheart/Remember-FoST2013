
void outputToServo(float out){
  servo.slowmove(map(out, 0, 100, 0, 180), servoSpeed);
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


