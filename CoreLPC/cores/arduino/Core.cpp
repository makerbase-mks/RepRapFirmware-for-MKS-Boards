/*
 * Core.cpp
 *
 *  Created on: 8 Dec 2020
 *      Author: David
 */

#include "Core.h"

// Optimised version of memcpy for when we know that the source and destination are 32-bit aligned and a whole number of 32-bit words are to be copied
void __attribute__ ((__optimize__ ("-fno-tree-loop-distribute-patterns"))) memcpyu32(uint32_t *dst, const uint32_t *src, size_t numWords) noexcept
{
	while (numWords >= 4)
	{
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
		*dst++ = *src++;
		numWords -= 4;
	}

	if ((numWords & 2) != 0)
	{
		*dst++ = *src++;
		*dst++ = *src++;
	}

	if ((numWords & 1) != 0)
	{
		*dst++ = *src++;
	}
}

// End