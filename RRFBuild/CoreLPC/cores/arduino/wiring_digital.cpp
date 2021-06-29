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

#include "Core.h"

//Input Pin Settings
#define LPC_INPUT_PULLUP              0      //Pin has an on-chip pull-up resistor enabled (default on reset)
#define LPC_INPUT_REPEATER            1      //Repeater mode - Repeater mode enables the pull-up resistor if the pin is at a logic high and enables the
                                             //pull-down resistor if the pin is at a logic low. This causes the pin to retain its last known
                                             //state if it is configured as an input and is not driven externally.
#define LPC_INPUT_NOPULLUP_NOPULLDOWN 2      //Pin has neither pull-up nor pull-down resistor enabled.
#define LPC_INPUT_PULLDOWN            3      //Pin has an on-chip pull-down resistor enabled.
     
//opendrain modes
#define LPC_NOT_OPEN_DRAIN_MODE       4
#define LPC_OPEN_DRAIN_MODE           5
     

     
//SD: Added function to handle pin modes, based on mbed
extern "C" inline void GPIO_PinInputMode(gpioPins_et enm_pinNumber, uint8_t var_pinFunction_u8) noexcept
{
    uint8_t port_number;
    uint8_t pin_number = enm_pinNumber;

    port_number =  (enm_pinNumber>>5);  //Divide the pin number by 32 go get the PORT number
    pin_number  =   pin_number & 0x1f;  //lower 5-bits contains the bit number of a 32bit port

    switch (var_pinFunction_u8){
        case LPC_INPUT_PULLUP:
            // Set the two bits for this pin as 00
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] &= ~(3<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] &= ~(3<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] &= ~(3<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] &= ~(3<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] &= ~(3<<((pin_number-16)*2)); }

             break;
        case LPC_INPUT_REPEATER:
            // Set the two bits for this pin as 01
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[0] &= ~(2<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[1] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[2] &= ~(2<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[3] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[4] &= ~(2<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[7] &= ~(2<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (1<<( pin_number*2)); LPC_IOCON->PINMODE[9] &= ~(2<<((pin_number-16)*2)); }
             break;
        case LPC_INPUT_NOPULLUP_NOPULLDOWN:
            // Set the two bits for this pin as 10
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[0] &= ~(1<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[1] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[2] &= ~(1<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[3] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[4] &= ~(1<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[7] &= ~(1<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (2<<( pin_number*2)); LPC_IOCON->PINMODE[9] &= ~(1<<((pin_number-16)*2)); }
             break;
        case LPC_INPUT_PULLDOWN:
            // Set the two bits for this pin as 11
            if( port_number == 0 && pin_number < 16  ){ LPC_IOCON->PINMODE[0] |= (3<<( pin_number    *2)); }
            if( port_number == 0 && pin_number >= 16 ){ LPC_IOCON->PINMODE[1] |= (3<<((pin_number-16)*2)); }
            if( port_number == 1 && pin_number < 16  ){ LPC_IOCON->PINMODE[2] |= (3<<( pin_number    *2)); }
            if( port_number == 1 && pin_number >= 16 ){ LPC_IOCON->PINMODE[3] |= (3<<((pin_number-16)*2)); }
            if( port_number == 2 && pin_number < 16  ){ LPC_IOCON->PINMODE[4] |= (3<<( pin_number    *2)); }
            if( port_number == 3 && pin_number >= 16 ){ LPC_IOCON->PINMODE[7] |= (3<<((pin_number-16)*2)); }
            if( port_number == 4 && pin_number >= 16 ){ LPC_IOCON->PINMODE[9] |= (3<<((pin_number-16)*2)); }

             break;
        case LPC_OPEN_DRAIN_MODE:
            if( port_number == 0 ){ LPC_IOCON->PINMODE_OD[0] |= (1<<pin_number); }
            if( port_number == 1 ){ LPC_IOCON->PINMODE_OD[1] |= (1<<pin_number); }
            if( port_number == 2 ){ LPC_IOCON->PINMODE_OD[2] |= (1<<pin_number); }
            if( port_number == 3 ){ LPC_IOCON->PINMODE_OD[3] |= (1<<pin_number); }
            if( port_number == 4 ){ LPC_IOCON->PINMODE_OD[4] |= (1<<pin_number); }
            //pull_none(); // no pull up by default

             break;
        default:
             return; // invalid mode
        }
 }

     
     //From UserManual:
    /* The PINMODE registers control the input mode of all ports. This includes the use of the
     on-chip pull-up/pull-down resistor feature and a special open drain operating mode. The
     on-chip pull-up/pull-down resistor can be selected for every port pin regardless of the
     function on this pin with the exception of the I2C pins for the I2C0 interface and the USB
     pins (see Section 8.5.10). Three bits are used to control the mode of a port pin, two in a
     PINMODE register, and an additional one in a PINMODE_OD register. Bits are reserved
     for unused pins as in the PINSEL registers.

     PINMODE0 to PINMODE9
     00 Pin has an on-chip pull-up resistor enabled. 00
     01 Repeater mode - Repeater mode enables the pull-up resistor if the pin is at a logic high and enables the
                        pull-down resistor if the pin is at a logic low. This causes the pin to retain its last known
                        state if it is configured as an input and is not driven externally.
     10 Pin has neither pull-up nor pull-down resistor enabled.
     11 Pin has an on-chip pull-down resistor enabled.
     
*/
    
                            
     //SD: adapted for LPC
 extern "C" void pinModeDuet(Pin pin, enum PinMode ulMode, uint32_t debounceCutoff) noexcept
 {
     if(pin == NoPin) return;
     
     //const PinDescription& pinDesc = g_APinDescription[pin];

     switch (ulMode)
     {
         case INPUT:
             GPIO_PinFunction(pin,0); //configure pin as GPIO
             GPIO_PinDirection(pin, LPC_INPUT);
             GPIO_PinInputMode(pin, LPC_INPUT_NOPULLUP_NOPULLDOWN); //no pull up or down
             break;

         case INPUT_PULLUP:
             GPIO_PinFunction(pin,0); //configure pin as GPIO
             GPIO_PinDirection(pin, LPC_INPUT);
             GPIO_PinInputMode(pin, LPC_INPUT_PULLUP); //enable Pullup
             break;
             
         case INPUT_PULLDOWN:
             GPIO_PinFunction(pin,0); //configure pin as GPIO
             GPIO_PinDirection(pin, LPC_INPUT);
             GPIO_PinInputMode(pin, LPC_INPUT_PULLDOWN); //enable Pulldown
             break;
             
         case OUTPUT_LOW:
             GPIO_PinFunction(pin,0); //configure pin as GPIO
             GPIO_PinDirection(pin, LPC_OUTPUT);
             GPIO_PinWrite(pin, 0);
             break;
             
         case OUTPUT_HIGH:
             GPIO_PinFunction(pin,0); //configure pin as GPIO
             GPIO_PinDirection(pin, LPC_OUTPUT);
             GPIO_PinWrite(pin, 1);
             break;
             
         case OUTPUT_PWM_LOW:
             ConfigurePinForPWM(pin, false);
             break;
             
         case OUTPUT_PWM_HIGH:
            ConfigurePinForPWM(pin, true);
             break;

         case OUTPUT_SERVO_LOW:
             ConfigurePinForServo(pin, false);
             break;
             
         case OUTPUT_SERVO_HIGH:
             ConfigurePinForServo(pin, true);
             break;

         case AIN:
             //analog in
             GPIO_PinInputMode(pin, LPC_INPUT_NOPULLUP_NOPULLDOWN); //no pull up or down
             break;
             
         case SPECIAL:
             break;
             
         default:
             break;
     }
 }

     
     
extern "C" void digitalWrite( Pin pin, bool dwVal ) noexcept
{
    if(pin != NoPin) GPIO_PinWrite(pin,dwVal);
}

extern "C" bool digitalRead( Pin pin ) noexcept
{
    if(pin != NoPin) return GPIO_PinRead(pin);
    else return 0;
}

extern "C" void setPullup(Pin pin, bool en) noexcept
{
    
    pinModeDuet(pin, INPUT_PULLUP, 0);
    
}

