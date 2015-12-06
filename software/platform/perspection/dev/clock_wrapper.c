#include "clock_wrapper.h"
#include "sys/clock.h"

void clock_wrapper_delay_msec(int msec){
  int i;
  for(i = 0; i < msec; i++){
    clock_delay_usec(1000);
  }
}
