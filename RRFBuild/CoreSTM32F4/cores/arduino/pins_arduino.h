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
#ifndef _PINS_ARDUINO_H_
#define _PINS_ARDUINO_H_
#include <stdlib.h> /* Required for static_assert */
// Include board variant
#include "variant.h"
#include "PinNames.h"


// Avoid PortName issue
_Static_assert(LastPort <= 0x0F, "PortName must be less than 16");



#ifdef __cplusplus
extern "C" {
#endif
#define NOT_AN_INTERRUPT            NC // -1

// Convert a digital pin number Dxx to a PinName PX_n
// Note: Analog pin is also a digital pin.
#define digitalPinToPinName(p)      ((PinName)(p))
// Convert a PinName PX_n to a digital pin number
//uint32_t pinNametoDigitalPin(PinName p);
#define analogInputToPinName(p)     ((PinName)(p))
// All pins could manage EXTI
#define digitalPinToInterrupt(p)    (digitalPinIsValid(p) ? p : NOT_AN_INTERRUPT)

#define digitalPinHasI2C(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SDA) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_I2C_SCL))
#define digitalPinHasPWM(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_PWM))
#define digitalPinHasSerial(p)      (pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_RX) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_UART_TX))
#define digitalPinHasSPI(p)         (pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MOSI) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_MISO) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SCLK) ||\
                                     pin_in_pinmap(digitalPinToPinName(p), PinMap_SPI_SSEL))


#define digitalPinToPort(p)         (get_GPIO_Port(STM_PORT(digitalPinToPinName(p))))
#define digitalPinToBitMask(p)      (STM_GPIO_PIN(digitalPinToPinName(p)))

#define analogInPinToBit(p)         (STM_GPIO_PIN(digitalPinToPinName(p)))
#define portOutputRegister(P)       (&(P->ODR))
#define portInputRegister(P)        (&(P->IDR))

#define portSetRegister(P)          (&(P->BSRR))
#if defined(STM32F2xx) || defined(STM32F4xx) || defined(STM32F7xx)
// For those series reset are in the high part so << 16U needed
#define portClearRegister(P)        (&(P->BSRR))
#else
#define portClearRegister(P)        (&(P->BRR))
#endif


#if defined(STM32F1xx)
// Config registers split in 2 registers:
// CRL: pin 0..7
// CRH: pin 8..15
// Return only CRL
#define portModeRegister(P)         (&(P->CRL))
#else
#define portModeRegister(P)         (&(P->MODER))
#endif
#define portConfigRegister(P)       (portModeRegister(P))


#define digitalPinIsValid(p)        (digitalPinToPinName(p) != NC)

#ifdef __cplusplus
}
#endif

// Default Definitions, could be redefined in variant.h
#ifndef ADC_RESOLUTION
#define ADC_RESOLUTION              12
#endif
#ifndef DACC_RESOLUTION
#define DACC_RESOLUTION             12
#endif
#ifndef PWM_RESOLUTION
#define PWM_RESOLUTION              12
#endif
#ifndef PWM_FREQUENCY
#define PWM_FREQUENCY               1000
#endif
#ifndef PWM_MAX_DUTY_CYCLE
#define PWM_MAX_DUTY_CYCLE          4095
#endif

#endif /*_PINS_ARDUINO_H_*/
