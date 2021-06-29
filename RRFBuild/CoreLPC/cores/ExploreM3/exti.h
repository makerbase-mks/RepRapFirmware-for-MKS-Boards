
/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   extintr.h
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the function prototypes and configuration of LPC1768 External Interrupts.
                 

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 

Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/


#ifndef _EXT_INTERRUPTS_H_
#define _EXT_INTERRUPTS_H_


#ifdef __cplusplus

#include "Core.h"
#include "chip.h"
#include "stdutils.h"
#include "stdlib.h"


enum InterruptMode {
    INTERRUPT_MODE_NONE = 0,
    INTERRUPT_MODE_LOW,
    INTERRUPT_MODE_HIGH,
    INTERRUPT_MODE_CHANGE,
    INTERRUPT_MODE_FALLING,
    INTERRUPT_MODE_RISING
};

union CallbackParameter
{
    void *vp;
    uint32_t u32;
    int32_t i32;
    
    CallbackParameter(void *pp) noexcept : vp(pp) { }
    CallbackParameter(uint32_t pp) noexcept : u32(pp) { }
    CallbackParameter(int32_t pp) noexcept : i32(pp) { }
    CallbackParameter() noexcept : u32(0) { }
};

typedef void (*StandardCallbackFunction)(CallbackParameter) noexcept;

bool attachInterrupt(Pin pin, StandardCallbackFunction callback, enum InterruptMode mode, CallbackParameter param) noexcept;
void detachInterrupt(Pin pin) noexcept;

constexpr size_t MaxExtIntEntries = 3;

#endif //__cplusplus


#endif
