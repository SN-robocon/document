#include "ColorSensor.h" // <2>

using namespace spikeapi;

class Tracer {  
public:
  Tracer();
  void run();      

private:
  ColorSensor colorSensor;                  //カラーセンサ

};
