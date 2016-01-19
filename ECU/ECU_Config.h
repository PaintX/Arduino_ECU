#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#if defined(ARDUINO)
   #include <Arduino.h>
   #include <LiquidCrystal.h>
   #include "TunerStudio.h"
#else
    #include <stdint.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <conio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "Console.h"
    #include <ctime>// include this header
#endif

#include "Trigger_Input.h"

#if defined(ARDUINO)
    #define   SERIAL_PORT           Serial
    #define   SERIAL_DEBUG          Serial1
    #define   DEGREE_FOR_CALC       45.0

    #define     MILLIS()              millis()
#else

    #define   SERIAL_DEBUG          Cons
    #define   SERIAL_PORT           Cons

    #define     MILLIS()            (clock()/double(CLOCKS_PER_SEC)*1000)
    #define     MICROS()            clock()
#endif


#endif
