/**
 * @file    interpolation.h
 *
 * @date Oct 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2013
 */

#ifndef INTERPOLATION_3D_H_
#define INTERPOLATION_3D_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "ECU_Config.h"

int   findIndex(float array[], int size, float value);
float interpolate(float x1, float y1, float x2, float y2, float x);
float interpolate2d(float value, float bin[], float values[], int size);
float interpolate3d(float x, float xBin[], int xBinSize, float y, float yBin[], int yBinSize, float* map);


void setTableValue(float bins[], float values[], int size, float key, float value);


#endif /* INTERPOLATION_3D_H_ */
