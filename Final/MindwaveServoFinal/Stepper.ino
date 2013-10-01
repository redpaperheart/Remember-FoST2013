
void outputWithStepper(float out){
  stepper.moveTo(map(out, 0, 100, 0, stepperCicle));
  stepper.run();
}
