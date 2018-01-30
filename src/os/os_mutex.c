/*
 * os_mutex.c
 *
 *  Created on: Jan 26, 2018
 *      Author: al100017
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_mutex.h"
/* os */
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_MUTEX_NEW(_name, _attr) g_##_name##_mutex_id = osMutexNew(_attr);
#define EXPAND_AS_MUTEX_ADD_TO_REGISTRY(_name, _attr) vQueueAddToRegistry(g_##_name##_mutex_id, #_name);

void os_mutex_init(void)
{
	/* Create mutex objects */
    MUTEX_TABLE(EXPAND_AS_MUTEX_NEW)

#ifdef DEBUG
	/* For RTOS aware debugging we need to register the mutexes */
    MUTEX_TABLE(EXPAND_AS_MUTEX_ADD_TO_REGISTRY)
#endif

}
