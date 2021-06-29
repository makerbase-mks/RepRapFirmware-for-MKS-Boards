/*
 * Copyright 2017 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* freertos_tasks_c_additions.h Rev. 1.2 */
#ifndef FREERTOS_TASKS_C_ADDITIONS_H
#define FREERTOS_TASKS_C_ADDITIONS_H

#include <stdint.h>

//#if (configUSE_TRACE_FACILITY == 0)
//#error "configUSE_TRACE_FACILITY must be enabled"
//#endif

#define FREERTOS_DEBUG_CONFIG_MAJOR_VERSION 1
#define FREERTOS_DEBUG_CONFIG_MINOR_VERSION 1

/* NOTE!!
 * Default to a FreeRTOS version which didn't include these macros. FreeRTOS
 * v7.5.3 is used here.
 */
#ifndef tskKERNEL_VERSION_BUILD
#define tskKERNEL_VERSION_BUILD 3
#endif
#ifndef tskKERNEL_VERSION_MINOR
#define tskKERNEL_VERSION_MINOR 5
#endif
#ifndef tskKERNEL_VERSION_MAJOR
#define tskKERNEL_VERSION_MAJOR 7
#endif

/* NOTE!!
 * The configFRTOS_MEMORY_SCHEME macro describes the heap scheme using a value
 * 1 - 5 which corresponds to the following schemes:
 *
 * heap_1 - the very simplest, does not permit memory to be freed
 * heap_2 - permits memory to be freed, but not does coalescence adjacent free
 *          blocks.
 * heap_3 - simply wraps the standard malloc() and free() for thread safety
 * heap_4 - coalesces adjacent free blocks to avoid fragmentation. Includes
 *          absolute address placement option
 * heap_5 - as per heap_4, with the ability to span the heap across
 *          multiple nonOadjacent memory areas
 */
#ifndef configFRTOS_MEMORY_SCHEME
#define configFRTOS_MEMORY_SCHEME 5 /* thread safe malloc */
#endif

#if ((configFRTOS_MEMORY_SCHEME > 5) || (configFRTOS_MEMORY_SCHEME < 1))
#error "Invalid configFRTOS_MEMORY_SCHEME setting!"
#endif

#ifdef __cplusplus
extern "C" {
#endif
//SD Added to get top of task stacks

#if (configRECORD_STACK_HIGH_ADDRESS != 1)
# error configRECORD_STACK_HIGH_ADDRESS must be set to 1
#endif
volatile StackType_t *CheckSPCurrentTaskStack(const uint32_t *stackPointer)
{
    if(pxCurrentTCB == NULL || stackPointer == NULL) return NULL;
    if(stackPointer < pxCurrentTCB->pxStack || stackPointer > pxCurrentTCB->pxEndOfStack) return NULL; // stackPointer not in task stack
    return pxCurrentTCB->pxEndOfStack;
}

// GA Moved and modified to allow getting stack usage with configUSE_TRACE_FACILITY disabled
#if (configUSE_TRACE_FACILITY == 0)
	void vTaskGetInfo( TaskHandle_t xTask, TaskStatus_t *pxTaskStatus, BaseType_t xGetFreeStackSpace, eTaskState eState )
	{
	TCB_t *pxTCB;

		/* xTask is NULL then get the state of the calling task. */
		pxTCB = prvGetTCBFromHandle( xTask );

		pxTaskStatus->xHandle = ( TaskHandle_t ) pxTCB;
		pxTaskStatus->pcTaskName = ( const char * ) &( pxTCB->pcTaskName [ 0 ] );
		pxTaskStatus->uxCurrentPriority = pxTCB->uxPriority;
		pxTaskStatus->pxStackBase = pxTCB->pxStack;
        // not available without configUSE_TRACE_FACILITY
		//pxTaskStatus->xTaskNumber = pxTCB->uxTCBNumber;

		#if ( configUSE_MUTEXES == 1 )
		{
			pxTaskStatus->uxBasePriority = pxTCB->uxBasePriority;
		}
		#else
		{
			pxTaskStatus->uxBasePriority = 0;
		}
		#endif

		#if ( configGENERATE_RUN_TIME_STATS == 1 )
		{
			pxTaskStatus->ulRunTimeCounter = pxTCB->ulRunTimeCounter;
		}
		#else
		{
			pxTaskStatus->ulRunTimeCounter = 0;
		}
		#endif

		/* Obtaining the task state is a little fiddly, so is only done if the
		value of eState passed into this function is eInvalid - otherwise the
		state is just set to whatever is passed in. */
		if( eState != eInvalid )
		{
			if( pxTCB == pxCurrentTCB )
			{
				pxTaskStatus->eCurrentState = eRunning;
			}
			else
			{
				pxTaskStatus->eCurrentState = eState;

				#if ( INCLUDE_vTaskSuspend == 1 )
				{
					/* If the task is in the suspended list then there is a
					chance it is actually just blocked indefinitely - so really
					it should be reported as being in the Blocked state. */
					if( eState == eSuspended )
					{
						vTaskSuspendAll();
						{
							if( listLIST_ITEM_CONTAINER( &( pxTCB->xEventListItem ) ) != NULL )
							{
								pxTaskStatus->eCurrentState = eBlocked;
							}
						}
						( void ) xTaskResumeAll();
					}
				}
				#endif /* INCLUDE_vTaskSuspend */
			}
		}
		else
		{
			pxTaskStatus->eCurrentState = eTaskGetState( pxTCB );
		}

		/* Obtaining the stack space takes some time, so the xGetFreeStackSpace
		parameter is provided to allow it to be skipped. */
		if( xGetFreeStackSpace != pdFALSE )
		{
			#if ( portSTACK_GROWTH > 0 )
			{
				pxTaskStatus->usStackHighWaterMark = prvTaskCheckFreeStackSpace( ( uint8_t * ) pxTCB->pxEndOfStack );
			}
			#else
			{
				pxTaskStatus->usStackHighWaterMark = prvTaskCheckFreeStackSpace( ( uint8_t * ) pxTCB->pxStack );
			}
			#endif
		}
		else
		{
			pxTaskStatus->usStackHighWaterMark = 0;
		}
	}
#endif

#if (configUSE_TRACE_FACILITY != 0)

extern const uint8_t FreeRTOSDebugConfig[];

/* NOTES!!
 * IAR documentation is confusing. It suggests the data must be statically
 * linked, and the #pragma placed immediately before the symbol definition.
 * The IAR supplied examples violate both "rules", so this is a best guess.
 */
#if defined(__GNUC__)
const uint8_t FreeRTOSDebugConfig[] __attribute__((section(".rodata"))) =
#elif defined(__CC_ARM)
const uint8_t FreeRTOSDebugConfig[] __attribute__((used)) =
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma required=FreeRTOSDebugConfig
const uint8_t FreeRTOSDebugConfig[] =
#endif
{
    FREERTOS_DEBUG_CONFIG_MAJOR_VERSION,
    FREERTOS_DEBUG_CONFIG_MINOR_VERSION,
    tskKERNEL_VERSION_MAJOR,
    tskKERNEL_VERSION_MINOR,
    tskKERNEL_VERSION_BUILD,
    configFRTOS_MEMORY_SCHEME,
    offsetof(struct tskTaskControlBlock, pxTopOfStack),
#if (tskKERNEL_VERSION_MAJOR > 8)
    offsetof(struct tskTaskControlBlock, xStateListItem),
#else
    offsetof(struct tskTaskControlBlock, xGenericListItem),
#endif
    offsetof(struct tskTaskControlBlock, xEventListItem),
    offsetof(struct tskTaskControlBlock, pxStack),
    offsetof(struct tskTaskControlBlock, pcTaskName),
    offsetof(struct tskTaskControlBlock, uxTCBNumber),
    offsetof(struct tskTaskControlBlock, uxTaskNumber),
    configMAX_TASK_NAME_LEN,
    configMAX_PRIORITIES,
    0 /* pad to 32-bit boundary */
};
#endif

#ifdef __cplusplus
}
#endif

#endif // FREERTOS_TASKS_C_ADDITIONS_H
