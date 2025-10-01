#include "Tracer.h"
#include <stdio.h>
#include <iostream>
#include <ctime> 

Tracer::Tracer():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true), 
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true),  
  colorSensor(EPort::PORT_E) ,
  ultrasonicsensor(EPort::PORT_F)
  { 
}

// 初期化処理
void Tracer::init() {
  printf("Tracer\n");
  leftWheel.resetCount();
}

// 停止処理
void Tracer::terminate() {
  printf("Stopped.\n");
  
  // モータ停止
  leftWheel.stop();  
  rightWheel.stop();
  
}

// 走行処理
void Tracer::run() {
  pwm_l = pwm;
  pwm_r = pwm;

  static float rotation_count = 0;      // モーターの回転角度を記憶
  int turn_limit = 2;                 // 直進する際のモーターの回転数

  rotation_count = abs(leftWheel.getCount());
  printf("角度：%f\n",rotation_count);
  if (rotation_count > 360 * turn_limit) {
    leftWheel.stop();
    rightWheel.stop();
    leftWheel.resetCount();
  } else {
    leftWheel.setPower(pwm_l);
    rightWheel.setPower(pwm_r);
    printf("左モータ速度：%d 右モータ速度：%d\n",pwm_l,pwm_r);
  }
}
