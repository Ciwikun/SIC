/*
    The devices are based on MegaPi.
    Libraries include "MeOrion.h" and "MeOrion.h".
 
    MPU6050
    VCC -> 5V
    GND -> GND
    SCL -> SCL
    SDA -> SDA
    AD0 -> A9
    INT -> A10

    Servo 
    myservo1 BASE -> A6
    myservo2 MID -> A7
    myservo3 UP -> A8
*/
#include "MeOrion.h"
#include <Wire.h>

MeGyro gyro;

Servo myservo1;//BASE
Servo myservo2;//MID
Servo myservo3;//UP

int PIN_SERVO1 = A6;
int PIN_SERVO2 = A7;
int PIN_SERVO3 = A8;

void setup() {
    Serial.begin(115200);
    
    myservo1.attach(PIN_SERVO1);
    delay(200);
    myservo2.attach(PIN_SERVO2);
    delay(200);
    myservo3.attach(PIN_SERVO3);
    delay(200);
    
    gyro.setpin(A9, A10);
    gyro.begin();
}

void loop() {
    int agx = gyro.getAngleX();
    int agy = gyro.getAngleY();
    int agz = gyro.getAngleZ();
    
    gyro.update();
    Serial.read();
    Serial.print("X:");
    Serial.print(agx);
    Serial.print(" Y:");
    Serial.print(agy);
    Serial.print(" Z:");
    Serial.println(agz);
    
    myservo1.write(90-agz);
    delay(15);
    myservo2.write(90-agx);
    delay(15);
    myservo3.write(90+agy);
    delay(15);
    
}
