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

#endif

#include "ECU_Config.h"
#include "TunerStudio.h"


float IGN_GetAdvance(float rpm, float engineLoad);
float IGN_GetOneDegreeUs(float  rpm);
float IGN_GetSparkDwellMs(float rpm);

#endif /* ADVANCE_H_ */
