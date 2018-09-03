import processing.serial.*; 
import cc.arduino.*;
Arduino arduino;

PFont f;
Serial myPort;    // The serial port
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
PShape head;

float initAgx;
float initAgy;
float initAgz;

float lastAgx;
float lastAgy;
float lastAgz;

int lastTime;

void setup() 
{ 
  size(800, 600, P3D); 
  f=loadFont("TimesNewRomanPS-BoldMT-48.vlw");  
  head = loadShape("head/GoodBieber.obj");
  
  initSerial();
  initMPU();
  initArduinoUno();
 
  lastAgx=0;
  lastAgy=0;
  lastAgz=0;
  lastTime=millis();
} 
 
void draw() 
{ 
  initdraw();
  
  float[] list=getMPU();
  float agx=list[1];
  float agy=list[2];
  float agz=list[3];
  
  if(millis()-lastTime>6000)
  {
    //initMPU();  
    lastTime=millis();
  }
 
  if(agz<-180) agz+=360.0;
  
  textAlign(CENTER);
  text("X: " + String.format("%.2f", agx) + " Y: " + String.format("%.2f", agy) + " Z: "+ String.format("%.2f", agz), width/2, 50); 
  
  drawHead(agx, agy, agz);
  
  
  arduino.servoWrite(8, constrain((int)((agz)*1.3)+90, 0, 180));
  arduino.servoWrite(9, constrain((int)((agy)*5)+90, 0, 180));
  arduino.servoWrite(10, constrain((int)((agx)*7)+90, 0, 180));
} 
 
void serialEvent(Serial p) 
{ 
  inString = p.readString(); 
} 

void initSerial()
{
  printArray(Serial.list()); 
  myPort = new Serial(this, "COM8", 115200); 
  myPort.bufferUntil(lf); 
}

void initMPU()
{
  text("" + inString, 0,0); 
  float[] list=float(split(inString, " "));
  initAgx=list[1];
  initAgy=list[2];
  initAgz=list[3];
}

void initArduinoUno()
{
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(8, Arduino.SERVO);
  arduino.pinMode(9, Arduino.SERVO);
  arduino.pinMode(10, Arduino.SERVO);
  
  arduino.servoWrite(8, 90);
  arduino.servoWrite(9, 90);
  arduino.servoWrite(10, 90);
}

void initdraw()
{
  background(0); 
  textFont(f, 36);
  fill(255);
}

float[] getMPU()
{
  float[] list=float(split(inString, " "));
  float agx=list[1];
  float agy=list[2];
  float agz=list[3];
  
  agx-=initAgx;
  agy-=initAgy;
  agz-=initAgz;
  
  list[1]=agx;
  list[2]=agy;
  list[3]=agz;
  
  return list;
}

void buildBoxShape() 
{
  //box(60, 10, 40);
  
  noStroke();
  beginShape(QUADS);

  //Z+ 
  fill(#00ff00);
  vertex(-30, -5, 20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  //Z-
  fill(#0000ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, 5, -20);
  vertex(-30, 5, -20);

  //X-
  fill(#ff0000);
  vertex(-30, -5, -20);
  vertex(-30, -5, 20);
  vertex(-30, 5, 20);
  vertex(-30, 5, -20);

  //X+
  fill(#ffff00);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(30, 5, -20);

  //Y-
  fill(#ff00ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(-30, -5, 20);

  //Y+
  fill(#00ffff);
  vertex(-30, 5, -20);
  vertex(30, 5, -20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  endShape();
}

void drawCube(float agx, float agy, float agz) 
{  
  pushMatrix();
  translate(width/2, height/2, 0);
  scale(4, 4, 4);

  rotateX((agy)/180.0*PI);
  rotateY((agz)/180.0*PI);
  rotateZ((agx)/180.0*PI);

  buildBoxShape();

  popMatrix();
}

public void drawHead(float agx, float agy, float agz) {
  background(0);
  lights();
  
  translate(width/2, height/2+25, -200);
  rotateX((agy)/180.0*PI);
  rotateY((agz)/180.0*PI);
  rotateZ((agx)/180.0*PI);
  
  shape(head);
}
