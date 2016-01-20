/**
 * @file	advance_map.c
 *
 * @date Mar 27, 2013
 * @author Andrey Belomutskiy, (c) 2012-2014
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */
#include "advance_map.h"
#include "interpolation.h"

float getBaseAdvance(float rpm, float engineLoad)
{
  float * ptr = flashState.engineConfiguration.ignitionTable[0];
	return interpolate3d(engineLoad , flashState.engineConfiguration.ignitionLoadBins , IGN_LOAD_COUNT , rpm,flashState.engineConfiguration.ignitionRpmBins , IGN_RPM_COUNT ,  ptr);
}

float IGN_GetAdvance(float rpm, float engineLoad)
{
/*	if (isCrankingR(rpm))
		return engineConfiguration->ignitionOffset;*/

	return getBaseAdvance(rpm, engineLoad) + flashState.engineConfiguration.ignitionOffset;
}


float IGN_GetOneDegreeUs(float  rpm)
{
    return (((1000.0 * 60.0) / 360.0) / rpm);
}


float IGN_GetSparkDwellMs(float rpm)
{
    /*if (isCrankingR(rpm))
    {
    // technically this could be implemented via interpolate2d
    //FLOAT32 angle = engineConfiguration->crankingChargeAngle;
    //return getOneDegreeTimeMs(rpm) * angle;
    }*/

    if (rpm > flashState.engineConfiguration.rpmHardLimit)
    {
        // technically this could be implemented via interpolate2d by setting everything above rpmHardLimit to zero
       // CONS_PutS("skipping spark due to rpm=%d", rpm);
        return 0.0;
    }

    return interpolate2d(rpm, flashState.engineConfiguration.sparkDwellBins, flashState.engineConfiguration.sparkDwell, DWELL_CURVE_SIZE);
}
