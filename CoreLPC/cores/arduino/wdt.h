
#ifndef WDT_H
#define WDT_H


#ifdef __cplusplus
extern "C" {
#endif

#define WDT 1
    
    
void WatchdogEnable (uint32_t s_counter) noexcept;
void WatchdogDisable() noexcept;
void WatchdogReset() noexcept; // compat with 3.2+
    
#ifdef __cplusplus
}
#endif

#endif /* WDT_H */
