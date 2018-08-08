#include <M5Stack.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 600 // this is the 'maximum' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int angle_print=0;

void setup() {
  M5.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("start!");
  delay(500);
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates

}

void loop() {
  if(M5.BtnA.wasPressed()){
    standard();
    
  }else if(M5.BtnB.wasPressed()){
   naname();
   delay(1000);
   nanames();
   delay(1000);
      naname();
   delay(1000);
   nanames();
   delay(1000);
      naname();
   delay(1000);
   standard();
  }else if(M5.BtnC.wasPressed()){
        servo_write(0,135);
    servo_write(1,90);
    servo_write(2,135);
    servo_write(3,90); 
  }
  servo_write(0,angle_print);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("%d",angle_print);
  M5.update();
  // put your main code here, to run repeatedly:

}

void standard(){
     servo_write(8,135);
    servo_write(1,90);
    servo_write(2,130);
    servo_write(3,90); 
    servo_write(4,20);
    servo_write(5,20);
    servo_write(6,20);
    servo_write(7,20);  
}

void naname(){
     servo_write(8,90);
    servo_write(1,135);
    servo_write(2,90);
    servo_write(3,135); 
    servo_write(4,8);
    servo_write(5,8);
    servo_write(6,8);
    servo_write(7,8);  
}

void nanames(){
    servo_write(8,90);
    servo_write(1,135);
    servo_write(2,90);
    servo_write(3,135); 
    servo_write(4,60);
    servo_write(5,60);
    servo_write(6,60);
    servo_write(7,60);  
}
void servo_write(int n, int ang){ //動かすサーボと角度を引数に持つ
  ang = map(ang, 0, 180, SERVOMIN, SERVOMAX); //角度（0～180）をPWMのパルス幅（150～600）へ変換
  pwm.setPWM(n, 0, ang);
}
