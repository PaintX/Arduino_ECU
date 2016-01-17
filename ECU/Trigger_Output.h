#ifndef _TRIGGER_OUTPUT_H_
#define _TRIGGER_OUTPUT_H_

#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
#else
   #include <WProgram.h>
#endif

void setPwmFrequency(int pin, int divisor) ;

#endif

