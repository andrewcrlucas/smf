/*
 * event_flags.c
 *
 *  Created on: Jan 26, 2018
 *      Author: al100017
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "event_flags.h"
/* os */
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_EVENT_FLAGS_NEW(_name, _attr) g_##_name##_event_flags_id = osEventFlagsNew(_attr);
#define EXPAND_AS_EVENT_FLAGS_ADD_TO_REGISTRY(_name, _attr) vQueueAddToRegistry(g_##_name##_event_flags_id, #_name);

void event_flags_init(void)
{
	/* Create mutex objects */
    EVENT_FLAGS_TABLE(EXPAND_AS_EVENT_FLAGS_NEW)
}
