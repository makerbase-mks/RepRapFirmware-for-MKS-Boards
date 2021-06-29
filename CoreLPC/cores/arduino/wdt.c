

//SD: Watchdog functions for LPC to work with RRF

#include "chip.h"
#include "wdt.h"
#include "stdutils.h"
#include "interrupt_lpc.h"


#ifdef __cplusplus
extern "C" {
#endif
/* LPC
 -Programmable 32-bit timer with internal pre-scaler.
 -Selectable time period from (TWDCLK x 256 x 4) to (TWDCLK x 2^32 x 4) in multiples of TWDCLK x 4.
 */

//Init the watchdog in mS
void WatchdogEnable(uint32_t s_counter) noexcept
{

    //From Manual
    //1. Set the Watchdog timer constant reload value in WDTC register.
    //2. Setup the Watchdog timer operating mode in WDMOD register.
    //3. Enable the Watchdog by writing 0xAA followed by 0x55 to the WDFEED register.
    //4. The Watchdog should be fed again before the Watchdog counter underflows to prevent reset/interrupt.
    
    Chip_WWDT_SelClockSource(LPC_WWDT, WWDT_CLKSRC_WATCHDOG_PCLK); // Set CLK src to PCLK

    const uint32_t ticksPerSecond = Chip_Clock_GetPeripheralClockRate(SYSCTL_PCLK_WDT) / 4; //WDT has a fixed /4 prescaler
    Chip_WWDT_SetTimeOut(LPC_WWDT, s_counter * ticksPerSecond / 1000);

    /*Manual says: The WDTC register determines the time-out value. Every time a feed sequence occurs
     the WDTC content is reloaded in to the Watchdog timer. It’s a 32-bit register with 8 LSB
     set to 1 on reset. Writing values below 0xFF will cause 0x0000 00FF to be loaded to the
     WDTC. Thus the minimum time-out interval is TWDCLK x 256 x 4.
     */
    Chip_WWDT_Start(LPC_WWDT); // Enables the watchdog and does the first feed

    NVIC_ClearPendingIRQ(WDT_IRQn);
    NVIC_SetPriority(WDT_IRQn, 0); //Highest priority
    NVIC_EnableIRQ(WDT_IRQn);
}

void WatchdogReset() noexcept
{
    Chip_WWDT_Feed(LPC_WWDT);
}
    
#ifdef __cplusplus
}
#endif

