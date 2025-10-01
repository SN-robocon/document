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
}

// 停止処理
void Tracer::terminate() {
  printf("Stopped.\n");
}

// 超音波センサー処理
void Tracer::run() {

  clock_spike.sleep(1000000);

  int32_t distance = ultrasonicsensor.getDistance();

  printf("距離: %d mm\n", distance);
  
  bool flag = ultrasonicsensor.isPresence();
  
  printf("flag = %d\n", flag);

  if (flag) {
    printf("物体を検出しました！\n");
  }else{
    printf("物体を検出できませんでした！\n");
  }
}
