
void outputToServo(float out){
  servo.write(map(out, 0, 100, 180, 0));
}

void calculateOutput(){
  // set bad quality if dont get packets
  if(millis() - lastReceivedPacket > 5000){
    lastPoorQuality = 255;
  }

  // decide if we use meditation or attention
  int val = useMeditation? (int)lastMeditation : (int)lastAttention;

  // decide if we use mindReader or manual slider depending on signal quality
  float targetOutput = 0;
  if(lastPoorQuality < 27){
    targetOutput = map(val, 10, 80, 0, 100);
  }
  else{
    lastAttention = 0.0;
    lastMeditation = 0.0;
    targetOutput = map(potVal, 0, 1023, 0, 100);
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

  // clamp it
  if(output > 100) output = 100;
  else if (output < 0) output = 0;
}


void processNewData(){
  if(bigPacket){ // we have new data
    lastPoorQuality = poorQuality;
    lastAttention = attention;
    lastMeditation = meditation;
  }
}







