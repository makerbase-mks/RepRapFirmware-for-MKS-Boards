

#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stdutils.h"
#include "gpio.h"
#include "systick.h"
#include "timer.h"
#include "delay.h"
#include "Reset.h"

#include "interrupt_lpc.h"


#include "ecv.h"        // included to compile rrf
#undef yield            // eCv definition clashes with function 'yield' in wiring.c (can use _ecv_yield instead within annotations)


extern void loop() noexcept;
extern void setup() noexcept;
extern void init( void ) noexcept;

#ifdef __cplusplus
extern "C"
{
#endif
    void CoreSysTick(void) noexcept;
#ifdef __cplusplus
}// end exten "C"
#endif

typedef gpioPins_et Pin;
static const Pin NoPin = P_NC; //which =0xff

#include "exti.h"
#include "wiring_digital.h"
#include "wirish_time.h"
#include "wdt.h"


#ifdef __cplusplus
extern const char * const sysStackLimit;

// Pin Attributes to be OR-ed
constexpr uint8_t PIN_ATTR_NONE = 0;
constexpr uint8_t PIN_ATTR_COMBO = 1 << 0;
constexpr uint8_t PIN_ATTR_ANALOG = 1 << 1;
constexpr uint8_t PIN_ATTR_DIGITAL = 1 << 2;
constexpr uint8_t PIN_ATTR_PWM = 1 << 3;
constexpr uint8_t PIN_ATTR_TIMER = 1 << 4;
constexpr uint8_t PIN_ATTR_DAC = 1 << 5;

constexpr uint8_t NumADCChannels = 8;

enum AnalogChannelNumber : int8_t
{
    NO_ADC=-1,
    ADC0=0,
    ADC1,
    ADC2,
    ADC3,
    ADC4,
    ADC5,
    ADC6,
    ADC7
};

#include "pwm_176x.h"

struct PinDescription
{
    uint8_t pPort;
    uint8_t ulPinAttribute;
    AnalogChannelNumber ulADCChannelNumber; // ADC or DAC channel number
    EPWMChannel ulPWMChannel;
};

/* Pins table to be instantiated into variant.cpp */
constexpr uint32_t MaxPinNumber = 160;// 5*32
extern const PinDescription g_APinDescription[MaxPinNumber];


enum SSPChannel : uint8_t
{
    //Hardware SPI
    SSP0 = 0,
    SSP1,
    
    //Software SPI
    SWSPI0,

    // Not defined
    SSPNONE = 0xff
};


#include "WCharacter.h"
#include "Stream.h"
#include "WMath.h"
#include "AnalogIn.h"
#include "AnalogOut.h"
#include "HardwareSerial.h"
#include "ConfigurableUART.h"
#include "SerialUSB.h"

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


#include "variant.h"
#define SAM4E	0
#define SAM4S	0
#define SAM3XA	0
#define SAME70	0
#define SAME5x  0
#define SAMC21  0

#define IRAM_ADDR 0x10000000

typedef uint8_t DmaChannel;			///< A type that represents a DMA channel number
typedef uint8_t DmaPriority;		///< A type that represents a DMA priority
//typedef uint8_t Pin;				///< A type that represents an I/O pin on the microcontroller
typedef uint16_t PwmFrequency;		///< A type that represents a PWM frequency. 0 sometimes means "default".
typedef uint32_t NvicPriority;		///< A type that represents an interrupt priority
typedef uint8_t ExintNumber;		///< A type that represents an EXINT number
typedef uint8_t EventNumber;		///< A type that represents an event number

#ifndef __STATIC_INLINE
 #define __STATIC_INLINE  static inline
#endif


#endif /* __ARDUINO_H__ */

/*lint -restore */
