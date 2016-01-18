#ifndef _ECU_CONFIG_H_
#define _ECU_CONFIG_H_

#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
   #include "TunerStudio.h"
#else
    #include <stdint.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
 //  #include <WProgram.h>
#endif


#define   SERIAL_PORT       Serial
#define   SERIAL_DEBUG       Serial1

#define   DEGREE_FOR_CALC   45.0

#endif
