import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 
import cc.arduino.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class BT825 extends PApplet {

 

Arduino arduino;

PFont f;
Serial myPort;    // The serial port
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 

float initAgx;
float initAgy;
float initAgz;

float lastAgx;
float lastAgy;
float lastAgz;

int lastTime;

public void setup() 
{ 
   
  f=loadFont("TimesNewRomanPS-BoldMT-48.vlw");  
  
  initSerial();
  initMPU();
  initArduinoUno();
 
  lastAgx=0;
  lastAgy=0;
  lastAgz=0;
  lastTime=millis();
} 
 
public void draw() 
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
 
  if(agz<-180) agz+=360.0f;
  
  textAlign(CENTER);
  text("X: " + String.format("%.2f", agx) + " Y: " + String.format("%.2f", agy) + " Z: "+ String.format("%.2f", agz), width/2, 50); 
  
  drawCube(agx, agy, agz);
  
  
  arduino.servoWrite(8, constrain((int)((agz)*1.3f)+90, 0, 180));
  arduino.servoWrite(9, constrain((int)((agy)*5)+90, 0, 180));
  arduino.servoWrite(10, constrain((int)((agx)*7)+90, 0, 180));
} 
 
public void serialEvent(Serial p) 
{ 
  inString = p.readString(); 
} 

public void initSerial()
{
  printArray(Serial.list()); 
  myPort = new Serial(this, "COM8", 115200); 
  myPort.bufferUntil(lf); 
}

public void initMPU()
{
  text("" + inString, 0,0); 
  float[] list=PApplet.parseFloat(split(inString, " "));
  initAgx=list[1];
  initAgy=list[2];
  initAgz=list[3];
}

public void initArduinoUno()
{
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(8, Arduino.SERVO);
  arduino.pinMode(9, Arduino.SERVO);
  arduino.pinMode(10, Arduino.SERVO);
  
  arduino.servoWrite(8, 90);
  arduino.servoWrite(9, 90);
  arduino.servoWrite(10, 90);
}

public void initdraw()
{
  background(0); 
  textFont(f, 36);
  fill(255);
}

public float[] getMPU()
{
  float[] list=PApplet.parseFloat(split(inString, " "));
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

public void buildBoxShape() 
{
  //box(60, 10, 40);
  
  noStroke();
  beginShape(QUADS);

  //Z+ 
  fill(0xff00ff00);
  vertex(-30, -5, 20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  //Z-
  fill(0xff0000ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, 5, -20);
  vertex(-30, 5, -20);

  //X-
  fill(0xffff0000);
  vertex(-30, -5, -20);
  vertex(-30, -5, 20);
  vertex(-30, 5, 20);
  vertex(-30, 5, -20);

  //X+
  fill(0xffffff00);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(30, 5, 20);
  vertex(30, 5, -20);

  //Y-
  fill(0xffff00ff);
  vertex(-30, -5, -20);
  vertex(30, -5, -20);
  vertex(30, -5, 20);
  vertex(-30, -5, 20);

  //Y+
  fill(0xff00ffff);
  vertex(-30, 5, -20);
  vertex(30, 5, -20);
  vertex(30, 5, 20);
  vertex(-30, 5, 20);

  endShape();
}

public void drawCube(float agx, float agy, float agz) 
{  
  pushMatrix();
  translate(width/2, height/2, 0);
  scale(4, 4, 4);

  rotateX((agy)/180.0f*PI);
  rotateY((agz)/180.0f*PI);
  rotateZ((agx)/180.0f*PI);

  buildBoxShape();

  popMatrix();
}
  public void settings() {  size(800, 600, P3D); }
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "BT825" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
