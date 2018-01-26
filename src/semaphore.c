/*
 * semaphore.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "semaphore.h"
/* os */
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_SEMAPHORE_NEW(_name, _count, _initial_count, _attr) g_##_name##_id = osSemaphoreNew(_count, _initial_count, _attr);
#define EXPAND_AS_SEMAPHORE_ADD_TO_REGISTRY(_name, _count, _initial_count, _attr) vQueueAddToRegistry(g_##_name##_id, #_name);

void semaphore_init(void)
{
	/* Create semaphore objects */
    SEMAPHORE_TABLE(EXPAND_AS_SEMAPHORE_NEW)

#ifdef DEBUG
	/* For RTOS aware debugging we need to register the semaphores */
    SEMAPHORE_TABLE(EXPAND_AS_SEMAPHORE_ADD_TO_REGISTRY)
#endif

}

