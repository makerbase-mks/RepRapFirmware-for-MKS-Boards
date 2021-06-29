/*
  Copyright (c) 2011 Arduino.  All right reserved.
  Copyright (c) 2013 by Paul Stoffregen <paul@pjrc.com> (delayMicroseconds)

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

#ifndef _WIRING_TIME_H_
#define _WIRING_TIME_H_

#include "clock.h"
#include "dwt.h"

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief Returns the number of milliseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 50 days.
 *
 * \return Number of milliseconds since the program started (uint32_t)
 */
extern uint32_t millis(void) ;
uint64_t millis64(void);
/**
 * \brief Returns the number of microseconds since the Arduino board began running the current program.
 *
 * This number will overflow (go back to zero), after approximately 70 minutes. On 16 MHz Arduino boards
 * (e.g. Duemilanove and Nano), this function has a resolution of four microseconds (i.e. the value returned is
 * always a multiple of four). On 8 MHz Arduino boards (e.g. the LilyPad), this function has a resolution
 * of eight microseconds.
 *
 * \note There are 1,000 microseconds in a millisecond and 1,000,000 microseconds in a second.
 */
extern uint32_t micros(void) ;

/**
 * \brief Pauses the program for the amount of time (in miliseconds) specified as parameter.
 * (There are 1000 milliseconds in a second.)
 *
 * \param ms the number of milliseconds to pause (uint32_t)
 */
extern void coreDelay(uint32_t ms) ;
extern void delay(uint32_t ms) noexcept;


#if defined(DWT_BASE) && !defined(DWT_DELAY_DISABLED)
	// Delay in cycles
  static inline uint32_t DelayCycles(const uint32_t start, const uint32_t cycles) noexcept __attribute__((always_inline, unused));
  #ifdef __cplusplus
  	[[gnu::always_inline, gnu::optimize("03")]]
  #endif
  static inline uint32_t DelayCycles(const uint32_t start, const uint32_t cycles) noexcept
	{
    while ((DWT->CYCCNT) - start < cycles) ; 
    return (DWT->CYCCNT); 
	}

  static inline uint32_t GetCurrentCycles() noexcept
  {
    return (DWT->CYCCNT);
  }
#else

  #ifdef __cplusplus
  	[[gnu::always_inline, gnu::optimize("03")]]
  #endif
 static inline void __delay_4cycles(uint32_t cy) noexcept { // +1 cycle
	__asm__ __volatile__(
		"  .syntax unified\n\t" // is to prevent CM0,CM1 non-unified syntax
		"1:\n\t"
		"  subs %[cnt],#1\n\t" // 1
		"  mov r0, r0\n\t"            // 1
		"  bne 1b\n\t"         // 1 + (1? reload)
		: [cnt]"+r"(cy)   // output: +r means input+output
		:                 // input:
		: "cc"            // clobbers:
	);
	}

	// Delay in cycles
  #ifdef __cplusplus
  	[[gnu::always_inline, gnu::optimize("03")]]
  #endif
  static inline uint32_t DelayCycles(const uint32_t start, const uint32_t cycles) noexcept 
	{
		if (cycles >> 2) __delay_4cycles(cycles >> 2);
		return 0;
	}

  static inline uint32 GetCurrentCycles() noexcept
  {
    return 0;
  }

#endif


/**
 * \brief Pauses the program for the amount of time (in microseconds) specified as parameter.
 *
 * \param us the number of microseconds to pause (uint32_t)
 */
static inline void delayMicroseconds(uint32_t) __attribute__((always_inline, unused));
static inline void delayMicroseconds(uint32_t us)
{
#if defined(DWT_BASE) && !defined(DWT_DELAY_DISABLED)
  int32_t start  = (DWT->CYCCNT);
  int32_t cycles = us * (SystemCoreClock / 1000000);

  while ((int32_t)(DWT->CYCCNT) - start < cycles);
#else
  __IO uint32_t currentTicks = SysTick->VAL;
  /* Number of ticks per millisecond */
  const uint32_t tickPerMs = SysTick->LOAD + 1;
  /* Number of ticks to count */
  const uint32_t nbTicks = ((us - ((us > 0) ? 1 : 0)) * tickPerMs) / 1000;
  /* Number of elapsed ticks */
  uint32_t elapsedTicks = 0;
  __IO uint32_t oldTicks = currentTicks;
  do {
    currentTicks = SysTick->VAL;
    elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
                    oldTicks - currentTicks;
    oldTicks = currentTicks;
  } while (nbTicks > elapsedTicks);
#endif
}


static inline uint32_t NanosecondsToCycles(uint32_t ns) noexcept
{
  return (ns * (uint64_t)SystemCoreClock)/1000000000u;
}


#ifdef __cplusplus
}
#endif

#endif /* _WIRING_TIME_H_ */
