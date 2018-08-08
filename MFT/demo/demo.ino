#define TIME 150
#include <M5Stack.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte servopin[8]={8,1,2,3,4,5,6,7};
byte pos[8][8]={
  {135,90,130,90,20,20,20,20},
  {90,135,90,135,10,10,10,10},
  {90,135,90,135,60,60,60,60},
  {90,135,90,135,60,60,60,60},
  
  {155,50,100,135,30,60,20,60},
  {135,50,110,135,30,20,20,30},
  {90,120,170,70,60,20,60,20},
  {90,120,170,70,30,20,20,30}
};

void setup(){
  M5.begin();
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  pwm.begin();
  pwm.setPWMFreq(60);
  delay(500);
  //Serial2.print("a");
  if(Serial.available()>0){
    Serial.print("start");
  }
}

void loop(){
   //Serial.print("start");
  if(M5.BtnA.wasPressed()){
     //Serial.print("start");
    func1();
  }else if(M5.BtnB.wasPressed()){
    func2();
  }else if(M5.BtnC.wasPressed()){
    func3();
  }
   M5.update();
}

void leg(byte n){
  for(int i=0;i<8;i++){
    servo_write(servopin[i],pos[n][i]);
  }
}

void func1(){
  Serial.print("func1");
  leg(0);
}

void func2(){
  Serial.print("func2");
  leg(1);
  delay(500);
  leg(2);
  delay(500);
  leg(1);
  delay(500);
  leg(2);
  delay(500);
  leg(1);
  delay(500);
  leg(0);
  delay(500);
  Serial2.write("a");
  delay(1000);
  Serial2.write("b");
  delay(1000);
  Serial2.write("s");
}

void func3(){
  Serial.print("func3");
  for(int i=0;i<6;i++){
    leg(4);
    delay(TIME);
    leg(5);
    delay(TIME);
    leg(6);
    delay(TIME);
    leg(7);
    delay(TIME);
  }
    leg(1);
  
}

void servo_write(int n, int ang){ //動かすサーボと角度を引数に持つ
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）へ変換
  pwm.setPWM(n, 0, ang);
}

