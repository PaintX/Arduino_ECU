#ifndef _VARIABLES_H_
#define _VARIABLES_H_

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


extern TunerStudio::persistent_config_s        flashState;



#endif
