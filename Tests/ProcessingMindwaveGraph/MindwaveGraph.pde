import processing.serial.*;

Serial myPort;  // Create object from Serial class

// input
float att = 0;
float graphAtt = 0;
float med = 0;
float graphMed = 0;
float attmed = 0;
float graphAttmed = 0.0;

// logic
boolean useMeditation = false;
float attThresh = 65;
int timeOverThresh = 0;
int timeUnderThresh = 0;
int timeGrown = 0;
int lastMillis;
float output = 0;
int state = 0; // state machibne - 0:waiting to grow, 1:grown, 2: waiting to die 
String[] states = {
  "0- waiting to grow", "1- growing", "2- waiting to die"
};

// drawing
PGraphics graphs;
float cursor = 0;
float damping = 0.025;
float barHeight;
float meterWidth;

void setup() 
{
  size(1200, 600);
  background(225);
  frameRate(45);
  barHeight = height/4;
  meterWidth = 200;
  graphs = createGraphics(int(width - meterWidth*1.5), height);
  graphs.beginDraw();
  graphs.background(250);
  graphs.endDraw();

  println(Serial.list());
  String portName = "/dev/tty.usbmodem1441";//Serial.list()[0];
  myPort = new Serial(this, portName, 57600);
  myPort.bufferUntil(10); // Linefeed in ASCII
}

void update()
{
  int deltaTime = millis() - lastMillis;
  lastMillis = millis();

  // smooth data
  graphAtt = (1-damping) * graphAtt + damping * att;
  graphMed = (1-damping) * graphMed + damping * med;
  graphAttmed = (1-damping) * graphAttmed + damping * attmed;
  
  // logic - time
  // decide if we use meditation or attention
  float val = useMeditation? med : att;
    
  if (val > attThresh) {
    timeOverThresh += deltaTime;
    timeUnderThresh = 0;
  }
  else {
    timeUnderThresh += deltaTime;
    timeOverThresh = 0;
  }

  // logic - decisions
  float targetOutput = 0;
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
  output = (1-damping) * output + damping * targetOutput; 
}
void draw()
{
  update();

  background(250);
  drawGraphs(graphs);
  image(graphs, 0, 0);

  // draw labels
  fill(128);
  text("attention", 20, 30);
  text("meditation", 20, barHeight + 30);
  text("sum", 20, barHeight*2 + 30);
  text("difference", 20, barHeight*3 + 30);
  
  String secsOverThresh = nf(timeOverThresh/1000.0, 0, 1) + " secs over " + (useMeditation? "meditation" : "attention") + " thresh";
  String secsUnderThresh = nf(timeUnderThresh/1000.0, 0, 1) + " secs under " + (useMeditation? "meditation" : "attention") +  " thresh";
  text(secsOverThresh, width - meterWidth * 1.25, 20);
  text(secsUnderThresh, width - meterWidth * 1.25, 40);
  text("state: " + states[state], width - meterWidth * 1.25, height - 30);
  
  // draw meter
  float meterHeight = map(output, 0, 100, 0, height - 100);
  noStroke();
  fill(200);
  rect(width - meterWidth*1.25, 50, meterWidth, height - 100);
  fill(150);
  rect(width - meterWidth*1.25, height - 50, meterWidth, -meterHeight);

  float threshHeight = map(attThresh, 0, 100, 0, barHeight);
  stroke(150);
  if(useMeditation)  line(0, barHeight*2 - threshHeight, width - meterWidth*1.5, barHeight*2 - threshHeight);
  else               line(0, barHeight - threshHeight, width - meterWidth*1.5, barHeight - threshHeight);
}

void drawGraphs(PGraphics g) {  
  g.beginDraw();

  if (frameCount % 20 == 0) {
    g.fill(250, 8);
    g.noStroke();
    g.rect(0, 0, width, height);
  }

  cursor = (cursor + 0.5) % (width - meterWidth*1.5);
  drawBar(g, cursor, barHeight, graphAtt * barHeight /100, color(255, 0, 255));
  drawBar(g, cursor, barHeight*2, graphMed * barHeight /100, color(0, 255, 255));
  drawBar(g, cursor, barHeight*3, graphAttmed * barHeight /200, color(0, 255, 102));
  drawBar(g, cursor, barHeight*4 - 5, abs(graphAtt - graphMed) * barHeight /100, color(255, 102, 0));

  g.endDraw();
}

void changeState(int s) {
  state = s;
  timeGrown = 0;
  timeOverThresh = 0;
  timeUnderThresh = 0;
}

void drawBar(PGraphics g, float x, float y, float h, color c) {
  g.stroke(c);
  g.fill(c);
  g.line(x, y, x, y-h);
  g.fill(128);
  g.noStroke();
  g.ellipse(x, y-h, 1, 1);
}


void serialEvent(Serial port) {
  // normal message has the structure:
  // PoorQuality: 200 Attention: 0 Meditation: 0 Time since last packet: 0.497

  String msg = port.readStringUntil('\n'); 
  //msg = msg.replaceAll(" ", "");
  String[] list = split(msg, ' ');
  att = parseInt(list[3]);
  med = parseInt(list[5]);
  attmed = att + med;
  print(msg);
}

void keyPressed() {
  if(key == ' ') useMeditation = !useMeditation;
}
