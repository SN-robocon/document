#include "Tracer.h"
#include <stdio.h>
#include <iostream>
#include <ctime> 

  static int pwm_l = -60;
  static int pwm_r = 60;

Tracer::Tracer():
  leftWheel(EPort::PORT_B,Motor::EDirection::COUNTERCLOCKWISE,true), 
  rightWheel(EPort::PORT_A,Motor::EDirection::CLOCKWISE,true)
  { 
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


  leftWheel.setPower(pwm_l);
  rightWheel.setPower(pwm_r);

  // ジャイロセンサーから角速度を取得
  spikeapi::IMU::AngularVelocity angVel;
  imu.getAngularVelocity(angVel);
  printf("Z:%f \n",angVel.z);
	//printf("左:%d 右:%d\n",pwm_l,pwm_r);

}

void Tracer::speed() {
  printf("SPEED UP.\n\n");
  pwm_l = -70;
  pwm_r = 70;


}