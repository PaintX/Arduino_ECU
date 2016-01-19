/**
 * @file    interpolation.c
 * @brief	Linear interpolation algorithms
 *
 * @date Oct 17, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 */
#include <math.h>
#include "interpolation.h"

//#define DEBUG_INTERPOLATION


#define INTERPOLATION_A(x1, y1, x2, y2) ((y1 - y2) / (x1 - x2))

bool needInterpolationLogging = true;

/** @brief	Linear interpolation by two points
 *
 * @param	x1 key of the first point
 * @param	y1 value of the first point
 * @param	x2 key of the second point
 * @param	y2 value of the second point
 * @param	X key to be interpolated
 *
 * @note	For example, "interpolate(engineConfiguration.tpsMin, 0, engineConfiguration.tpsMax, 100, adc);"
 */
float interpolate(float x1, float y1, float x2, float y2, float x) {
	// a*x1 + b = y1
	// a*x2 + b = y2
//	chDbgCheck(x1 != x2, "no way we can interpolate");
	float a = INTERPOLATION_A(x1, y1, x2, y2);
	float b = y1 - a * x1;
	float result = a * x + b;
#if	DEBUG_FUEL
	printf("x1=%f y1=%f x2=%f y2=%f\r\n", x1, y1, x2, y2);
	printf("a=%f b=%f result=%f\r\n", a, b, result);
#endif
	return result;
}

/** @brief	Binary search
 * @returns	the highest index within sorted array such that array[i] is greater than or equal to the parameter
 * @note If the parameter is smaller than the first element of the array, -1 is returned.
 */
int findIndex(float * array, int size, float value)
{
#ifdef 	DEBUG_INTERPOLATION
	if (isnan(value))
		SERIAL_DEBUG.println("NaN in findIndex");
#endif
	if (value < array[0])
		return -1;
	int middle;

	int left = 0;
	int right = size;

	while (1)
	{
#ifdef 	DEBUG_INTERPOLATION
		if (size-- == 0)
			SERIAL_DEBUG.println("Unexpected state in binary search.");
#endif
		middle = (left + right) / 2;

//		print("left=%d middle=%d right=%d: %f\r\n", left, middle, right, array[middle]);

		if (middle == left)
			break;

		if (value < array[middle])
		{
			right = middle;
		}
		else if (value > array[middle])
		{
			left = middle;
		}
		else
		{
			break;
		}
	}
	return middle;
}

/**
 * @brief	One-dimensional table lookup with linear interpolation
 */
float interpolate2d(float value, float bin[], float values[], int size) {
	int index = findIndex(bin, size, value);

	if (index == -1)
		return values[0];
	if (index == size - 1)
		return values[size - 1];

	return interpolate(bin[index], values[index], bin[index + 1], values[index + 1], value);
}

/**
 * @brief	Two-dimensional table lookup with linear interpolation
 */
float interpolate3d(float x, float * xBin, int xBinSize, float y, float yBin[], int yBinSize, float* map)
{
   uint8_t tabStr[16];
	if (isnan(x))
   {
#ifdef 	DEBUG_INTERPOLATION
    SERIAL_DEBUG.print(x);
		SERIAL_DEBUG.println(": x is NaN in interpolate3d");
#endif
		return NAN;
	}
	if (isnan(y))
   {
#ifdef 	DEBUG_INTERPOLATION
    SERIAL_DEBUG.print(y);
		SERIAL_DEBUG.println(": y is NaN in interpolate3d");
#endif
		return NAN;
	}

	int xIndex = findIndex(xBin, xBinSize, x);
#ifdef	DEBUG_INTERPOLATION
		SERIAL_DEBUG.print("X index=");
		SERIAL_DEBUG.println(xIndex);
#endif
	int yIndex = findIndex(yBin, yBinSize, y);
#ifdef  DEBUG_INTERPOLATION
    SERIAL_DEBUG.print("Y index=");
    SERIAL_DEBUG.println(yIndex);
    SERIAL_DEBUG.println();
#endif
	if (xIndex < 0 && yIndex < 0)
   {
#ifdef	DEBUG_INTERPOLATION
      SERIAL_DEBUG.print("X and Y are smaller than smallest cell in table: ");
      SERIAL_DEBUG.print(xIndex);
      SERIAL_DEBUG.print(" ");
      SERIAL_DEBUG.println(yIndex);
#endif
		//return map2[0][0];
	}

	if (xIndex < 0)
   {
#ifdef	DEBUG_INTERPOLATION
    SERIAL_DEBUG.print("X is smaller than smallest cell in table: ");
    SERIAL_DEBUG.println(xIndex);
#endif
		// no interpolation should be fine here.
		//return map2[0][yIndex];
	}

	if (yIndex < 0)
   {
#ifdef	DEBUG_INTERPOLATION
    SERIAL_DEBUG.print("Y is smaller than smallest cell in table: ");
    SERIAL_DEBUG.println(yIndex);
#endif
		// no interpolation should be fine here.
		//return map2[xIndex][0];
	}

	if (xIndex == xBinSize - 1 && yIndex == yBinSize - 1)
   {
#ifdef	DEBUG_INTERPOLATION
      SERIAL_DEBUG.print("X and Y are larger than largest cell in table: ");
      SERIAL_DEBUG.print(xIndex);
      SERIAL_DEBUG.print(" ");
      SERIAL_DEBUG.println(yIndex);

 //  	CONS_Debug("X and Y are larger than largest cell in table: %d %d\r\n", xIndex, yIndex);
#endif
		//return map2[xBinSize - 1][yBinSize - 1];
	}

	if (xIndex == xBinSize - 1)
   {
#ifdef	DEBUG_INTERPOLATION
      SERIAL_DEBUG.print("TODO BETTER LOGGING x overflow ");
      SERIAL_DEBUG.println(xIndex);
//	   CONS_Debug("TODO BETTER LOGGING x overflow %d\r\n", yIndex);
#endif
		// todo: implement better handling - y interpolation
		//return map2[xBinSize - 1][yIndex];
	}

	if (yIndex == yBinSize - 1)
   {
#ifdef	DEBUG_INTERPOLATION
      SERIAL_DEBUG.print("Y is larger than largest cell in table: ");
      SERIAL_DEBUG.println(yIndex);
//		CONS_Debug("Y is larger than largest cell in table: %d\r\n", yIndex);
#endif
		// todo: implement better handling - x interpolation
		//return map2[xIndex][yBinSize - 1];
	}

	/*
	 * first we find the interpolated value for this RPM
	 */
	int rpmMaxIndex = xIndex + 1;

	float xMin = xBin[xIndex];
	float xMax = xBin[xIndex + 1];

	//sprintf(tabStr,"%.3f",map[((UINT32)xIndex * (UINT32)xBinSize) + (UINT32)yIndex]);
 //  float rpmMinKeyMinValue = atof(tabStr);
  float rpmMinKeyMinValue = map[((uint32_t)xIndex * (uint32_t)xBinSize) + (uint32_t)yIndex];

  // sprintf(tabStr,"%.3f",map[((UINT32)(xIndex+1) * (UINT32)xBinSize) + (UINT32)yIndex]);
//	float rpmMaxKeyMinValue = atof(tabStr);
  float rpmMaxKeyMinValue = map[((uint32_t)(xIndex+1) * (uint32_t)xBinSize) + (uint32_t)yIndex];


   float keyMinValue = interpolate(xMin, rpmMinKeyMinValue, xMax, rpmMaxKeyMinValue, x);

#ifdef	DEBUG_INTERPOLATION
	{
    SERIAL_DEBUG.println();
    SERIAL_DEBUG.print("X=");SERIAL_DEBUG.println(x,3);
    SERIAL_DEBUG.print("Xindex = ");SERIAL_DEBUG.println(xIndex);
    SERIAL_DEBUG.print("Yindex = ");SERIAL_DEBUG.println(yIndex);
    SERIAL_DEBUG.print("range ");SERIAL_DEBUG.print(xMin,3);SERIAL_DEBUG.print(" to ");SERIAL_DEBUG.println(xMax,3);
    SERIAL_DEBUG.print("X interpolation range ");SERIAL_DEBUG.print(rpmMinKeyMinValue,3); SERIAL_DEBUG.print(" to "); SERIAL_DEBUG.print(rpmMaxKeyMinValue,3);SERIAL_DEBUG.print(" result ");SERIAL_DEBUG.print(keyMinValue,3);
	}
#endif

	int keyMaxIndex = yIndex + 1;
	float keyMin = yBin[yIndex];
	float keyMax = yBin[keyMaxIndex];

	//sprintf(tabStr,"%.3f",map[((UINT32)xIndex * (UINT32)yBinSize) + (UINT32)keyMaxIndex]);
	//float rpmMinKeyMaxValue = atof(tabStr);
	float rpmMinKeyMaxValue = map[((uint32_t)xIndex * (uint32_t)yBinSize) + (uint32_t)keyMaxIndex];


	//sprintf(tabStr,"%.3f",map[((UINT32)rpmMaxIndex * (UINT32)yBinSize) + (UINT32)keyMaxIndex]);
	//float rpmMaxKeyMaxValue = atof(tabStr);
  float rpmMaxKeyMaxValue = map[((uint32_t)rpmMaxIndex * (uint32_t)yBinSize) + (uint32_t)keyMaxIndex];

	float keyMaxValue = interpolate(xMin, rpmMinKeyMaxValue, xMax, rpmMaxKeyMaxValue, x);

#ifdef	DEBUG_INTERPOLATION
	{
    SERIAL_DEBUG.println();
    SERIAL_DEBUG.print("Y=");SERIAL_DEBUG.println(y,3);
    SERIAL_DEBUG.print("range ");SERIAL_DEBUG.print(keyMin,3);SERIAL_DEBUG.print(" to ");SERIAL_DEBUG.println(keyMax,3);
    SERIAL_DEBUG.print("Y interpolation range ");SERIAL_DEBUG.print(rpmMinKeyMaxValue,3); SERIAL_DEBUG.print(" to "); SERIAL_DEBUG.print(rpmMaxKeyMaxValue,3);SERIAL_DEBUG.print(" result ");SERIAL_DEBUG.print(keyMaxValue,3);
    SERIAL_DEBUG.println();
	}
#endif

  float result = interpolate(keyMin, keyMinValue, keyMax, keyMaxValue, y);
  return result;
}

void setTableValue(float bins[], float values[], int size, float key, float value) {
	int index = findIndex(bins, size, key);
	if (index == -1)
		index = 0;
	values[index] = value;
}

