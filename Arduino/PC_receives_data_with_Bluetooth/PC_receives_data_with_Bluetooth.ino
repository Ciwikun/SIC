/*
   we use the Bluetooth module for mBot, MegaPi and MPU6050.
   The Bluetooth module for mBot using Serial3.
   PC uses APP named Bluetooth Serial terminal (from win 10 store).
   Tips: Only use Serial3 can we receive datas(Bluetooth module uesd Tx3 and Rx3).
   
   DATE 2018.8.22   
*/

#include "MeOrion.h"
#include <Wire.h>
#include <SoftwareSerial.h>

MeGyro gyro;

void setup() {
    Serial3.begin(115200);
    Serial3.println("Bluetooth Start!");
    gyro.begin();
}

void loop() {
    double agx = gyro.getAngleX();
    double agy = gyro.getAngleY();
    double agz = gyro.getAngleZ();
    
    gyro.update();
    Serial3.read();
    Serial3.print("X:");
    Serial3.print(agx);
    Serial3.print(" Y:");
    Serial3.print(agy);
    Serial3.print(" Z:");
    Serial3.println(agz);
    delay(100);
}
