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

float getAdvance(float rpm, float engineLoad)
{
/*	if (isCrankingR(rpm))
		return engineConfiguration->ignitionOffset;*/

	return getBaseAdvance(rpm, engineLoad) + flashState.engineConfiguration.ignitionOffset;
}
