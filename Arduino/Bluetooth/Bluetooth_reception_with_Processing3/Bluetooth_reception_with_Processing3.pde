import processing.serial.*; 
 
Serial myPort;    // The serial port
String inString;  // Input string from serial port
int lf = 10;      // ASCII linefeed 
 
void setup() 
{ 
  size(600,400); 
  printArray(Serial.list()); 
  myPort = new Serial(this, "COM8", 115200); 
  myPort.bufferUntil(lf); 
} 
 
void draw() 
{ 
  background(0); 
  text("Received: " + inString, 10,50); 
} 
 
void serialEvent(Serial p) 
{ 
  inString = p.readString(); 
} 
