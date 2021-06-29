/*
  Copyright (c) 2014 Arduino.  All right reserved.

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

#include "watchdog.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_wwdg.h"

static WWDG_HandleTypeDef wdHandle;
void WatchdogEnable (uint32_t timeout)
{
    wdHandle.Instance = WWDG;
    wdHandle.Init.Prescaler = WWDG_PRESCALER_8;
    wdHandle.Init.Window = 0x7f;
    wdHandle.Init.Counter = 0x7f;
    wdHandle.Init.EWIMode = WWDG_EWI_ENABLE;
    __HAL_RCC_WWDG_CLK_ENABLE();
    HAL_WWDG_Init(&wdHandle);
    __HAL_WWDG_ENABLE_IT(&wdHandle, WWDG_IT_EWI);
    __HAL_WWDG_ENABLE(&wdHandle);
    NVIC_EnableIRQ(WWDG_IRQn);
}

void WatchdogDisable(void)
{
    __HAL_RCC_WWDG_CLK_DISABLE();
}

void WatchdogReset(void)
{
    HAL_WWDG_Refresh(&wdHandle);
}

// End
