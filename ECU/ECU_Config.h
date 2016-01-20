#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#if defined(ARDUINO)
  #include <EEPROM.h>
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
    #include <windows.h>	//This is for the console code
    #include "Console.h"
    #include <ctime>// include this header
    #include "xml.h"
#endif

#include "Trigger_Input.h"
#include "TunerStudio.h"

#if defined(ARDUINO)

    #define   LCD_ROW               16
    #define   LCD_LINE              2
    #define   LCD                   lcd

    #define   SERIAL_PORT           Serial
    #define   SERIAL_DEBUG          Serial1
    #define   DEGREE_FOR_CALC       45.0

    #define     MILLIS()            millis()
    #define     MICROS()            micros()
#else

    #define   LCD_ROW               16
    #define   LCD_LINE              2

    #define   SERIAL_DEBUG          Cons
    #define   SERIAL_PORT           Cons

    #define     MILLIS()            (clock()/double(CLOCKS_PER_SEC)*1000)
    #define     MICROS()            clock()


    #define     LCD                 Cons

    #define     EEPROM              xmlfile
#endif


#endif
