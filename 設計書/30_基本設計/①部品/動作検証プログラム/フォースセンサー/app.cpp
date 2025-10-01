#include "app.h" // <1>
#include <stdio.h>

#include "Tracer.h" // <2>
#include "ForceSensor.h" // <3>
#include "Clock.h"

Tracer tracer;  // <4>
Clock clock_spike;    // <5>

using namespace spikeapi;

void tracer_task(intptr_t exinf) {
    tracer.run();
    ext_tsk();
}

void main_task(intptr_t unused) { // <1>
  const uint32_t duration = 100*1000; // <2>
  ForceSensor forceSensor(EPort::PORT_D);

  while(1){
    printf("Press the force sensor to start...\n");
    while (!forceSensor.isTouched()) {
      clock_spike.sleep(duration);   // <2>
    }
    
    while (forceSensor.isTouched()) {
      clock_spike.sleep(duration);
    }
    
    printf("Started!\n");
    
    while (!forceSensor.isTouched()) { // <1>
      clock_spike.sleep(duration);   // <2>
    }
    
    while (forceSensor.isTouched()) {
      clock_spike.sleep(duration);
    }

    printf("Stopped!\n");

  }
  ext_tsk(); // <5>
}

