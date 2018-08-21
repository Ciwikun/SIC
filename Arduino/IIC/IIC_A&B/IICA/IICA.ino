#include <Wire.h>

byte x = 0; //传递信号

void setup() {
  Wire.begin();
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(8); //发送数据到设备号为8的从机
  Wire.write("Hello World: "); //发送字符串
  Wire.write(x);             // 发送变量x中的一个字节  
  Wire.endTransmission();    // 停止发送
  x++;
  delay(500);
  Serial.println(x);
  Wire.requestFrom(4, 1);    //通知4号从机上传1个字节
  while(Wire.available()>0)  // 当主机接收到从机数据时
  { 
    byte c = Wire.read();  //接收一个字节赋值给c
    //判断c为1，则点亮LED，否则熄灭LED。
    if(c%3)
      digitalWrite(13, LOW);
    else
      digitalWrite(13, HIGH);
  }
  delay(500);
}
