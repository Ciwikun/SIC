#include <Wire.h>

byte x = 0; //传递信号
byte y = 0; //传递信号

void setup() {
  Wire.begin();
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(0x0A); 
  Wire.write("Hello World: "); //发送字符串
  Wire.write(x);             // 发送变量x中的一个字节  
  Wire.endTransmission();    // 停止发送

  Wire.beginTransmission(0x0B); 
  Wire.write("IIC: "); //发送字符串
  Wire.write(y);             // 发送变量x中的一个字节  
  Wire.endTransmission();    // 停止发送
  
  x++;
  y--;
  delay(500);
  Wire.requestFrom(0xA, 1);
  while(Wire.available()>0)  // 当主机接收到从机数据时
  { 
    Serial.print("0x0A: ");
    byte c = Wire.read();  //接收一个字节赋值给c
    Serial.println(c);
    //判断c为1，则点亮LED，否则熄灭LED。
    if(c%3)
      digitalWrite(13, LOW);
    else
      digitalWrite(13, HIGH);
  }

  Wire.requestFrom(0xB, 1);
  while(Wire.available()>0)  // 当主机接收到从机数据时
  { 
    Serial.print("0x0B: ");
    byte c = Wire.read();  //接收一个字节赋值给c
    Serial.println(c);
    //判断c为1，则点亮LED，否则熄灭LED。
    if(c%3)
      digitalWrite(13, LOW);
    else
      digitalWrite(13, HIGH);
  }
  
  delay(500);
}

