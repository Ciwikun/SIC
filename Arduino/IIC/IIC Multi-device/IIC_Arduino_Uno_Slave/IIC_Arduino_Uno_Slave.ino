#include <Wire.h>
int x;
void setup() 
{
  Wire.begin(10);                //加入 i2c 总线，设置从机地址为 #10
  Wire.onReceive(receiveEvent); //注册接收到主机字符的事件
  Wire.onRequest(requestEvent); //注册主机通知从机上传数据的事件
  Serial.begin(9600);          
}

void loop() 
{
  delay(100);
}

void receiveEvent(int howMany)
{
  while(Wire.available()>1)
  {
    char c = Wire.read();
    Serial.print(c);  
  }
  x = Wire.read();
  Serial.println(x);
}

void requestEvent()
{
    //把接收主机发送的数据包中的最后一个字节再上传给主机
    Wire.write(x); // 响应主机的通知，向主机发送一个字节数据
}
