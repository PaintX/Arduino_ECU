/*
 * advance.h
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef ADVANCE_H_
#define ADVANCE_H_

#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
#else
   #include <WProgram.h>
#endif

#include "TunerStudio.h"

#define AD_LOAD_COUNT 16
#define AD_RPM_COUNT 16


extern TunerStudio::persistent_config_s        flashState;

float getAdvance(float rpm, float engineLoad);
void prepareTimingMap(void);

#endif /* ADVANCE_H_ */
