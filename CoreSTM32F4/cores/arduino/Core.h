/*
  Arduino.h - Main include file for the Arduino SDK
  Copyright (c) 2005-2013 Arduino Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Core_h
#define Core_h

#include "ecv.h"		// macros for Escher C/C++ Verifier design-by-contract annotations
#undef array
#undef yield			// eCv definition clashes with function 'yield' in wiring.c (can use _ecv_yield instead within annotations)
#undef value			// needed because we include <optional> in some projects
#undef result

//#include "compiler.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "binary.h"
#include "itoa.h"
#include "PinNames.h"
#include "wiring_constants.h"
#include "interrupt_stm32.h"
#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

//#include "asf.h"

void yield(void) noexcept;
void CoreSysTick(void) noexcept;

typedef PinName Pin;
static const Pin NoPin = NC;
typedef uint8_t DmaChannel;
typedef uint16_t PwmFrequency;		// type used to represent a PWM frequency. 0 sometimes means "default".
typedef uint32_t NvicPriority;

#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
extern const char * const sysStackLimit;
// SSP/SPI Channels - yes I know the names do not match the numbers...
enum SSPChannel : uint8_t
{
    //Hardware SPI
    SSP1 = 0,
    SSP2,
    SSP3,
    //Software SPI
    SWSPI0,
    SWSPI1,
    SWSPI2,
    // Hardware SDIO
    SSPSDIO = 0xef,
    // Not defined
    SSPNONE = 0xff
};
constexpr size_t NumSPIDevices = (uint32_t)SWSPI2+1;
constexpr size_t NumSoftwareSPIDevices = 3;

// Definitions for PWM channels
enum EPWMChannel : int8_t
{
  NOT_ON_PWM=-1,
  PWM_CH0=0,
  PWM_CH1,
  PWM_CH2,
  PWM_CH3,
  PWM_CH4,
  PWM_CH5,
  PWM_CH6,
  PWM_CH7
};

// Definitions for TC channels
enum ETCChannel : int8_t
{
  NOT_ON_TIMER=-1,
  TC0_CHA0=0,
  TC0_CHB0,
  TC0_CHA1,
  TC0_CHB1,
  TC0_CHA2,
  TC0_CHB2,
  TC1_CHA3,
  TC1_CHB3,
  TC1_CHA4,
  TC1_CHB4,
  TC1_CHA5,
  TC1_CHB5,
#if SAM3XA || SAM4E || SAME70
  TC2_CHA6,
  TC2_CHB6,
  TC2_CHA7,
  TC2_CHB7,
  TC2_CHA8,
  TC2_CHB8,
#endif
#if SAME70
  TC3_CHA9,
  TC3_CHB9,
  TC3_CHA10,
  TC3_CHB10,
  TC3_CHA11,
  TC3_CHB11
#endif
};

typedef uint32_t AnalogChannelNumber;
constexpr AnalogChannelNumber NO_ADC = (AnalogChannelNumber)0xffffffff;
// Pin Attributes to be OR-ed
constexpr uint8_t PIN_ATTR_NONE = 0;
constexpr uint8_t PIN_ATTR_COMBO = 1 << 0;
constexpr uint8_t PIN_ATTR_ANALOG = 1 << 1;
constexpr uint8_t PIN_ATTR_DIGITAL = 1 << 2;
constexpr uint8_t PIN_ATTR_PWM = 1 << 3;
constexpr uint8_t PIN_ATTR_TIMER = 1 << 4;
constexpr uint8_t PIN_ATTR_DAC = 1 << 5;

// Types used for the tables below
typedef GPIO_TypeDef Pio;
struct PinDescription
{
	Pio* pPort;
	uint32_t ulPin;
	uint32_t ulPinConfiguration;
	uint8_t ulPinAttribute;
	AnalogChannelNumber ulADCChannelNumber; // ADC or DAC channel number in the SAM device
	EPWMChannel ulPWMChannel;
	ETCChannel ulTCChannel;
};

/* Pins table to be instantiated into variant.cpp */
extern const PinDescription g_APinDescription[];

#include "WCharacter.h"
#include "HardwareSerial.h"
#include "WInterrupts.h"
// Optimised version of memcpy for use when the source and destination are known to be 32-bit aligned and a whole number of 32-bit words is to be copied
void memcpyu32(uint32_t *dst, const uint32_t *src, size_t numWords) noexcept;

// memcpy for int32_t arrays
inline void memcpyi32(int32_t *dst, const int32_t *src, size_t numWords) noexcept
{
	static_assert(sizeof(int32_t) == sizeof(uint32_t));
	static_assert(alignof(int32_t) == alignof(uint32_t));
	memcpyu32(reinterpret_cast<uint32_t*>(dst), reinterpret_cast<const uint32_t*>(src), numWords);
}

// memcpy for float arrays
inline void memcpyf(float *dst, const float *src, size_t numFloats) noexcept
{
	static_assert(sizeof(float) == sizeof(uint32_t));
	static_assert(alignof(float) == alignof(uint32_t));
	memcpyu32(reinterpret_cast<uint32_t*>(dst), reinterpret_cast<const uint32_t*>(src), numFloats);
}

#endif // __cplusplus

// Include board variant
#include "variant.h"
#define SAM4E	0
#define SAM4S	0
#define SAM3XA	0
#define SAME70	0
#define SAME5x  0
#define SAMC21  0

// Address of main RAM bank
#define IRAM_ADDR 0x20000000

#include "wiring.h"
#include "wiring_digital.h"
#include "watchdog.h"
#include "WMath.h"
#include "Reset.h"

#ifdef __cplusplus
#include "AnalogIn.h"
#include "AnalogOut.h"
#include "ConfigurableUART.h"
#include "USBSerial.h"
#endif

#endif // Arduino_h
