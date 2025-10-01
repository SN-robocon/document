#include "Motor.h"       // <1>

#include "IMU.h"

using namespace spikeapi;


class Tracer {  
public:
  Tracer();
  void run();      
  void terminate();
  void speed();
private:
  Motor leftWheel;
  Motor rightWheel;
  IMU imu;                                  //ジャイロセンサ

#ifndef MAKE_RASPIKE
  const int8_t pwm = 30;
#else
  const int8_t pwm = 50;
#endif

  // 状態管理用のメンバ変数


};
