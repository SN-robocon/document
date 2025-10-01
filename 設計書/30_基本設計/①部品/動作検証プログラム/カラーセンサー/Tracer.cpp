#include "Tracer.h"
#include <stdio.h>
#include <algorithm> 

Tracer::Tracer():
  colorSensor(EPort::PORT_E)
  { 
}

void Tracer::run() {

spikeapi::ColorSensor::HSV hsv_color;
spikeapi::ColorSensor::HSV hsv;
spikeapi::ColorSensor::RGB rgb;
int reflection;

int red,green,blue;
double hue,saturation,value;

  //1.色取得 HSV値(近似されたHSV値)
  colorSensor.getColor(hsv_color);
  //printf("HSV(近似)\n");
  //printf("H:%d ,S:%d ,V:%d\n",hsv_color.h,hsv_color.s,hsv_color.v);
  printf("\n");

  //2.色取得 HSV値(近似なし)
  colorSensor.getHSV(hsv);
  printf("---HSV(近似なし)---\n");
  printf("H:%d ,S:%d ,V:%d\n",hsv.h,hsv.s,hsv.v);
  printf("\n");

  //3.色取得 RGB値
  colorSensor.getRGB(rgb);
  printf("---RGB---\n");
  printf("R:%d ,G:%d ,B:%d\n",rgb.r,rgb.g,rgb.b);
  printf("\n");
  red = rgb.r;
  green = rgb.g;
  blue = rgb.b;

  double max_rgb = std::max((std::max(red,green)),blue);
  double min_rgb = std::min((std::min(red,green)),blue);
  value = max_rgb/256*100;

  if(max_rgb==min_rgb){
      hue = 0;
      saturation = 0;
  }else{
      if(max_rgb == red){
          hue = 60.0*(green-blue)/(max_rgb-min_rgb) + 0;
      }else if(max_rgb == green) {
          hue = 60.0*(blue-red)/(max_rgb-min_rgb) + 120.0;
      }else if(max_rgb == blue){
          hue = 60.0*(red-green)/(max_rgb-min_rgb) + 240.0;
      }

      if(hue > 360.0) {
          hue = hue - 360.0;
      }else if(hue < 0){
          hue = hue + 360.0;
      }
      
      saturation = (max_rgb-min_rgb)/max_rgb*100.0;
  }
  printf("RGB→HSV\n");
  printf("H:%f ,S:%f ,V:%f\n",hue,saturation,value);

  double diff_h = abs(hue - hsv.h);
  double diff_s = abs(saturation - hsv.s);
  double diff_v = abs(value - hsv.v);
  printf("差分\n");
  printf("diff_h:%d ,diff_s:%d ,diff_v:%d\n",diff_h,diff_s,diff_v);
  printf("\n");


    //4.光の反射測定
  reflection = colorSensor.getReflection();
  //printf("反射光:%d\n",reflection);



}


