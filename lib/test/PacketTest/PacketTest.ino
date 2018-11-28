#include <Servo.h>
#include "Packet.h"

Servo servo1;
Servo servo2;

Packet packet1;
Packet packet2;
uint8_t len;
uint8_t* buf;

void setup() {
  Serial.begin(115200);
  packet1.num = 8;
  packet1.permit = 1;
  packet1.motor = -1;
  packet1.power = 29;
  packet1.angle1 = 20;
  packet1.angle2 = 40;
  buf = packet1.createPacket(&len);
  for(int i = 0; i < len; i++) {
    String s = String(buf[i], HEX);
    if(s.length() == 1) {
      Serial.print("0");
    }
    Serial.print(s);
  }
  Serial.println();
  for(int i = 0; i < len; i++) {
    packet2.put(buf[i]);
  }
  Serial.println("------------------------------");
  packetPrint(&packet2);
}

void loop() {
}

void packetPrint(Packet* packet) {
  Serial.print("isReady:");
  Serial.println(packet->isReady());
  Serial.print("number:");
  Serial.println(packet->getNumber());
  Serial.print("permit:");
  Serial.println(packet->isPermit());
  Serial.print("motor state:");
  Serial.println(packet->getMotorStatus());
  Serial.print("motor power:");
  Serial.println(packet->getMotorPower());
  Serial.print("angle1:");
  Serial.println(packet->getAngle1());
  Serial.print("angle2:");
  Serial.println(packet->getAngle2());
}

