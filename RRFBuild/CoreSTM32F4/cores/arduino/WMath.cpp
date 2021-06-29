/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <Core.h>
#include <cstdlib>
#include <cstdint>

#include "WMath.h"

#if SAM3XA || SAME70
// SAM3X and SAME70 have a true random number generator
# include "trng/trng.h"
#endif

extern "C" uint32_t random32()
{
#if SAM3XA || SAME70
	while (!(TRNG->TRNG_ISR & TRNG_ISR_DATRDY)) {}
	return (uint32_t)TRNG->TRNG_ODATA;
#else
	static bool isInitialised = false;

	if (!isInitialised)
	{
		srand(SysTick->VAL);
		isInitialised = true;
	}

	return rand();
#endif
}

extern int32_t random(int32_t howsmall, int32_t howbig)
{
	if (howsmall >= howbig)
	{
		return howsmall;
	}

	return random(howbig - howsmall) + howsmall;
}

// End
