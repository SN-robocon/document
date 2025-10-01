#include "Motor.h"       // <1>
#include "ColorSensor.h" // <2>
#include <fstream>
#include "IMU.h"
#include "UltrasonicSensor.h"
#include "Clock.h"

using namespace spikeapi;

// ステート管理用のenum
enum class TracerState {
  FIRST_ROTATE,
  STRAIGHT_MOVE,
  SECOND_ROTATE,
  BLACKLINE_SEARCH,
  STOP
};

class Tracer {  
public:
  Tracer();
  void run();      
  void init();
  void terminate();

private:
  Clock clock_spike;    // <5>
  Motor leftWheel;
  Motor rightWheel;
  ColorSensor colorSensor;                  //カラーセンサ
  const int8_t mThreshold = 20;  
  IMU imu;                                  //ジャイロセンサ
  UltrasonicSensor ultrasonicsensor;        //超音波センサ

#ifndef MAKE_RASPIKE
  const int8_t pwm = 30;
#else
  const int8_t pwm = 50;
#endif

  // 状態管理用のメンバ変数
  TracerState currentState;
  int pwm_l;
  int pwm_r;

  float calc_prop_value();  // methodを追加
  float get_rotation_angle();
  void line_obstacle();
};
