
void outputWithServo(float out){
  servo.slowmove(map(out, 0, 100, 0, 180), 100);
}
