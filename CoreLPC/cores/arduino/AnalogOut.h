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

#ifndef ANALOGOUT_H
#define ANALOGOUT_H

#include "Core.h"

// Initialise this module
void AnalogOutInit() noexcept;

/*
 * \brief Writes an analog value (PWM wave) to a pin.
 *
 * \param ulPin
 * \param ulValue, will be constrained to be within 0.0 to 1.0 within this function
 * \param freq (optional)
 */


constexpr uint8_t MaxNumberSoftwarePWMPins = 7;
constexpr uint16_t HardwarePWMFrequency = 50; //50Hz for Servos

void AnalogOut(Pin pin, float ulValue, uint16_t freq = 1000) noexcept;
bool IsPwmCapable(Pin pin) noexcept;
bool ConfigurePinForPWM(Pin pin, bool outputHigh) noexcept;
void ReleasePWMPin(Pin pin) noexcept;


bool IsServoCapable(Pin pin) noexcept;
bool ConfigurePinForServo(Pin pin, bool outputHigh) noexcept;
void ReleaseServoPin(Pin pin) noexcept;
bool AnalogWriteServo(float ulValue, uint16_t freq, Pin pin) noexcept;

bool AnalogWriteSoftwarePWM(float ulValue, uint16_t freq, Pin pin) noexcept;
bool CanDoSoftwarePWM(Pin pin) noexcept;
bool ConfigurePinForSoftwarePWM(Pin pin) noexcept;
void ReleaseSoftwarePWMPin(Pin pin) noexcept;

extern Pin UsedHardwarePWMChannel[NumPwmChannels];
class SoftwarePWM; //fwd decl
extern SoftwarePWM* softwarePWMEntries[MaxNumberSoftwarePWMPins];

#endif // ANALOGOUT_H
