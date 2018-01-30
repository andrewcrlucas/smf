/*
 * os_mutex.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_mutex.h"
/* os */
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_OS_MUTEX_ATTR(_name) \
	osMutexAttr_t _name##_attr =       \
	{                                  \
        .name = #_name,                \
        .attr_bits = 0,                \
        .cb_mem = NULL,                \
        .cb_size = 0,                  \
	};

#define EXPAND_AS_OS_MUTEX_NEW(_name) g_##_name##_mutex_id = osMutexNew(&_name##_attr);
#define EXPAND_AS_OS_MUTEX_ADD_TO_REGISTRY(_name) vQueueAddToRegistry(g_##_name##_mutex_id, #_name);

void os_mutex_init(void)
{
	/* Declare attr objects */
    MUTEX_TABLE(EXPAND_AS_OS_MUTEX_ATTR)
	/* Create mutex objects */
    MUTEX_TABLE(EXPAND_AS_OS_MUTEX_NEW)

#ifdef DEBUG
	/* For RTOS aware debugging we need to register the mutexes */
    MUTEX_TABLE(EXPAND_AS_OS_MUTEX_ADD_TO_REGISTRY)
#endif

}
