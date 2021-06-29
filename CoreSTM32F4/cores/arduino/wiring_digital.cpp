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

#include "Arduino.h"
#include "PinConfigured.h"
#include "HybridPWM.h"

#ifdef __cplusplus
extern "C" {
#endif


extern uint32_t g_anOutputPinConfigured[MAX_NB_PORT];
void pinModeDuet(Pin pin, enum PinMode ulMode, uint32_t debounceCutoff) noexcept
{
    if(pin == NoPin) return;
    switch (ulMode)
    {
        case INPUT:
            pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
            break;

        case INPUT_PULLUP:
            pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0));
            break;
            
        case INPUT_PULLDOWN:
            pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLDOWN, 0));
            break;
            
        case OUTPUT_LOW:
            pin_function(pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
            digitalWriteFast(pin, 0);
            break;
            
        case OUTPUT_HIGH:
            pin_function(pin, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
            digitalWriteFast(pin, 1);
            break;
            
        case OUTPUT_PWM_LOW:
            HybridPWMPin::allocate(pin, 0.0f);
            break;
            
        case OUTPUT_PWM_HIGH:
            HybridPWMPin::allocate(pin, 1.0f);
            break;

        case AIN:
            //analog in
            pin_function(pin, STM_PIN_DATA(STM_MODE_ANALOG, GPIO_NOPULL, 0));
            break;

        case OUTPUT_LOW_OPEN_DRAIN:
            pin_function(pin, STM_PIN_DATA(STM_MODE_OUTPUT_OD, GPIO_NOPULL, 0));
            digitalWriteFast(pin, 0);
            break;
            
        case OUTPUT_HIGH_OPEN_DRAIN:
            pin_function(pin, STM_PIN_DATA(STM_MODE_OUTPUT_OD, GPIO_NOPULL, 0));
            digitalWriteFast(pin, 1);
            break;
                        
        default:
            break;
    }
}

void digitalWrite(Pin ulPin, uint32_t ulVal)
{
  if (ulPin == NC) return;
  digitalWriteFast(digitalPinToPinName(ulPin), ulVal);
}

int digitalRead(Pin ulPin)
{
  if (ulPin == NC) return 0;
  return digitalReadFast(digitalPinToPinName(ulPin));
}

void digitalToggle(Pin ulPin)
{
  if (ulPin == NC) return;
  digitalToggleFast(digitalPinToPinName(ulPin));
}

void setPullup(Pin pin, bool en)
{
  if (pin == NC) return;
  if (en)
    pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, 0));
  else
    pin_function(pin, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
}
#ifdef __cplusplus
}
#endif
