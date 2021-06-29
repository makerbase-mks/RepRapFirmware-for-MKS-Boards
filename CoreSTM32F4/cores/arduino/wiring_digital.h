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

#ifndef _WIRING_DIGITAL_
#define _WIRING_DIGITAL_
#include <pins_arduino.h>
#include <digital_io.h>

#ifdef __cplusplus
extern "C" {
#endif
// Pin mode enumeration. Would ideally be a C++ scoped enum, but we need to use it from C library functions.
enum PinMode
{
	PIN_MODE_NOT_CONFIGURED = -1,	// used in Platform class to record that the mode for a pin has not been set yet
	INPUT = 0,						// pin is a digital input
	INPUT_PULLUP,					// pin is a digital input with pullup enabled
	INPUT_PULLDOWN,					// pin is a digital input with pulldown enabled
	OUTPUT_LOW,						// pin is an output with initial state LOW
	OUTPUT_HIGH,					// pin is an output with initial state HIGH
	AIN,							// pin is an analog input, digital input buffer is disabled if possible
	SPECIAL,						// pin is used for the special function defined for it in the variant.cpp file
	OUTPUT_PWM_LOW,					// PWM output mode, initially low
	OUTPUT_PWM_HIGH,				// PWM output mode, initially high
	OUTPUT_LOW_OPEN_DRAIN,			// used in SX1509B expansion driver to put the pin in open drain output mode
	OUTPUT_HIGH_OPEN_DRAIN,			// used in SX1509B expansion driver to put the pin in open drain output mode
	OUTPUT_PWM_OPEN_DRAIN			// used in SX1509B expansion driver to put the pin in PWM output mode
};

/**
 * \brief Configures the specified pin to behave either as an input or an output. See the description of digital pins for details.
 *
 * \param ulPin The number of the pin whose mode you wish to set
 * \param ulMode Either INPUT or OUTPUT
 * \param debounceCutoff Debounce cutoff frequency (only one can be set per PIO)
 */
extern void pinModeDuet(Pin pin, enum PinMode dwMode, uint32_t debounceCutoff) noexcept;

static inline void pinMode(Pin pin, enum PinMode dwMode) noexcept
{
	pinModeDuet(pin, dwMode, 0);
}

/**
 * \brief Write a HIGH or a LOW value to a digital pin.
 *
 * If the pin has been configured as an OUTPUT with pinMode(), its voltage will be set to the
 * corresponding value: 3.3V for HIGH, 0V (ground) for LOW.
 *
 * \param dwPin the pin number
 * \param dwVal HIGH or LOW
 */
extern void digitalWrite(Pin dwPin, uint32_t dwVal) ;

/**
 * \brief Reads the value from a specified digital pin, either HIGH or LOW.
 *
 * \param ulPin The number of the digital pin you want to read (int)
 *
 * \return HIGH or LOW
 */
extern int digitalRead(Pin ulPin) ;

/**
 * \brief Toggle the value from a specified digital pin.
 *
 * \param ulPin The number of the digital pin you want to toggle (int)
 */
extern void digitalToggle(Pin ulPin) ;

extern void setPullup(Pin pin, bool en) ;

// Set a pin high with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] inline void fastDigitalWriteHigh(const Pin pin) noexcept
#else
inline void fastDigitalWriteHigh(const Pin pin) noexcept
#endif
{
	WRITE_REG(GPIOPort[STM_PORT(pin)]->BSRR, STM_GPIO_PIN(pin));
}

// Set a pin low with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] inline void fastDigitalWriteLow(const Pin pin) noexcept
#else
inline void fastDigitalWriteLow(const Pin pin) noexcept
#endif
{
	WRITE_REG(GPIOPort[STM_PORT(pin)]->BSRR, STM_GPIO_PIN(pin) << 16);
}

// Read a pin with no error checking
#ifdef __cplusplus
[[gnu::always_inline, gnu::optimize("O3")]] inline int fastDigitalRead(const Pin pin) noexcept
#else
inline int fastDigitalRead(const Pin pin) noexcept
#endif
{
	return (READ_BIT(GPIOPort[STM_PORT(pin)]->IDR, STM_GPIO_PIN(pin)) ? HIGH : LOW);
}



#ifdef __cplusplus
}
#endif

#endif /* _WIRING_DIGITAL_ */
