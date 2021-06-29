#ifndef INTERRUPT_LPC_H
#define INTERRUPT_LPC_H

#include <stdbool.h>
#include <stdint.h>
//#include "chip.h"



#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t irqflags_t;
#define cpu_irq_is_enabled()    (__get_PRIMASK() == 0)


#define cpu_irq_enable()                       \
    do {                                       \
        __DMB();                               \
		__enable_irq();                        \
	} while (0)
# define cpu_irq_disable()                     \
	do {                                       \
		__disable_irq();                       \
		__DMB();                               \
	} while (0)


static inline irqflags_t cpu_irq_save(void) noexcept
{
	irqflags_t flags = cpu_irq_is_enabled();
	cpu_irq_disable();
	return flags;
}

static inline bool cpu_irq_is_enabled_flags(irqflags_t flags) noexcept
{
	return (flags);
}

static inline void cpu_irq_restore(irqflags_t flags) noexcept
{
	if (cpu_irq_is_enabled_flags(flags))
		cpu_irq_enable();
}
    
// Return true if we are in any interrupt service routine
static inline bool inInterrupt() noexcept
{
    //bits 0:8 are the ISR_NUMBER
    //bits 9:31 reserved
    return (__get_IPSR() & 0xFF) != 0;
}


// Functions to change the base priority, to shut out interrupts up to a priority level

// From section 3.12.7 of http://infocenter.arm.com/help/topic/com.arm.doc.dui0553b/DUI0553.pdf:
// When you write to BASEPRI_MAX, the instruction writes to BASEPRI only if either:
// - Rn is non-zero and the current BASEPRI value is 0
// - Rn is non-zero and less than the current BASEPRI value
//__attribute__( ( always_inline ) ) __STATIC_INLINE void __set_BASEPRI_MAX(uint32_t value)
//{
//  __ASM volatile ("MSR basepri_max, %0" : : "r" (value) : "memory");
//}

// Get the base priority and shut out interrupts lower than or equal to a specified priority
inline uint32_t ChangeBasePriority(uint32_t prio) noexcept
{
        const uint32_t oldPrio = __get_BASEPRI();
        __set_BASEPRI_MAX(prio << (8 - __NVIC_PRIO_BITS));
        return oldPrio;
}

// Restore the base priority following a call to ChangeBasePriority
inline void RestoreBasePriority(uint32_t prio) noexcept
{
        __set_BASEPRI(prio);
}

// Set the base priority when we are not interested in the existing value i.e. definitely in non-interrupt code
inline void SetBasePriority(uint32_t prio) noexcept
{
        __set_BASEPRI(prio << (8 - __NVIC_PRIO_BITS));
}    
#ifdef __cplusplus
}

// Atomic section locker, alternative to InterruptCriticalSectionLocker (is safe to call from within an ISR, and may be faster)
class AtomicCriticalSectionLocker
{
public:
        AtomicCriticalSectionLocker() noexcept : flags(cpu_irq_save())
        {
        }

        ~AtomicCriticalSectionLocker()
        {
                cpu_irq_restore(flags);
        }

private:
        irqflags_t flags;
};

#endif

#endif /* INTERRUPT_LPC_H */
