/*
 * AnalogInput.h
 *
 *  Created on: 2 Apr 2016
 *      Author: David
 */

#ifndef ANALOGIN_H_
#define ANALOGIN_H_

#ifdef __cplusplus

#include "Core.h"

extern uint32_t ADCNotReadyCnt;
extern uint32_t ADCInitCnt;
extern uint32_t ADCErrorThreshold;

// Module initialisation
void AnalogInInit() noexcept;

// Enable or disable a channel. Use AnalogCheckReady to make sure the ADC is ready before calling this.
void AnalogInEnableChannel(AnalogChannelNumber channel, bool enable) noexcept;

// Read the most recent 12-bit result from a channel
uint16_t AnalogInReadChannel(AnalogChannelNumber channel) noexcept;
static inline void AnalogInFinaliseConversion() noexcept { }

 static constexpr unsigned int AdcBits = 12;

// Start converting the enabled channels, to include the specified ones. Disabled channels are ignored.
void AnalogInStartConversion(uint32_t channels = 0xFFFFFFFF) noexcept;

// Convert a pin number to an AnalogIn channel
extern AnalogChannelNumber PinToAdcChannel(uint32_t pin) noexcept;

void ConfigureADCPreFilter(bool enable) noexcept;
#endif

#endif /* CORES_ARDUINO_ANALOGIN_H_ */
