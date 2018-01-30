/*
 * os_semaphore.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_semaphore.h"
/* os */
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_OS_SEMAPHORE_ATTR(_name, _count, _initial_count) \
	osSemaphoreAttr_t _name##_attr =                               \
	{                                                              \
        .name = #_name,                                            \
        .attr_bits = 0,                                            \
        .cb_mem = NULL,                                            \
        .cb_size = 0,                                              \
	};

#define EXPAND_AS_OS_SEMAPHORE_NEW(_name, _count, _initial_count) g_##_name##_id = osSemaphoreNew(_count, _initial_count, &_name##_attr);
#define EXPAND_AS_OS_SEMAPHORE_ADD_TO_REGISTRY(_name, _count, _initial_count) vQueueAddToRegistry(g_##_name##_id, #_name);

void os_semaphore_init(void)
{
	/* Declare attr objects */
    SEMAPHORE_TABLE(EXPAND_AS_OS_SEMAPHORE_ATTR)
	/* Create semaphore objects */
    SEMAPHORE_TABLE(EXPAND_AS_OS_SEMAPHORE_NEW)

#ifdef DEBUG
	/* For RTOS aware debugging we need to register the semaphores */
    SEMAPHORE_TABLE(EXPAND_AS_OS_SEMAPHORE_ADD_TO_REGISTRY)
#endif

}

