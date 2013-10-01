int distance = 0;  // Record the number of steps we've taken
int motorCicle = 1600 * 4; //10000; //5 revolutions
int in = 0;
int out = 0;

void setup() {                
  pinMode(8, OUTPUT);     
  pinMode(9, OUTPUT);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);

  Serial.begin(9600);
}

void loop() {
  
  if(distance == out){
    in = analogRead(A5);
    if(in < 400){
      out = distance - 20;
    }
    else if(in > 600){
      out = distance + 20;
    }
    Serial.print("in: ");
    Serial.print(in);
    Serial.print(" out: ");
    Serial.println(out);
  }
  else if(distance < out){
    stepForward();
  }
  else if(distance > out){
    stepBack();
  }
  else{
    hold();
  }
  

  /*
  if(distance == out){
    in = analogRead(A5);
    out = map(in, 0, 1024, 0, motorCicle);
    Serial.print("in: ");
    Serial.print(in);
    Serial.print(" out: ");
    Serial.println(out);
  }
  else if(distance < out){
    stepForward();
  }
  else if(distance > out){
    stepBack();
  }
  else{
    hold();
  }
  */
}

void setDirection(boolean forward){
  if(forward){
    digitalWrite(8, HIGH);
  }
  else{
    digitalWrite(8, LOW);
  }
}

void stepForward(){
  setDirection(true);
  step();
  distance ++;
}

void stepBack(){
  setDirection(false);
  step();
  distance --;
}

void step(){
  digitalWrite(9, HIGH);
  delayMicroseconds(200);          
  digitalWrite(9, LOW); 
  delayMicroseconds(200);
}
void hold(){
}



