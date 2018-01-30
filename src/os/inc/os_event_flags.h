/*
 * os_event_flags.h
 *
 *  Created on: Jan 26, 2018
 *      Author: al100017
 */

#ifndef OS_EVENT_FLAGS_H_
#define OS_EVENT_FLAGS_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"

#define EVENT_FLAGS_TABLE(ENTRY) \
	  /* _name */   \
	ENTRY(my_flags)

#define EXPAND_AS_OS_EVENT_FLAGS_ID(_name) osEventFlagsId_t g_##_name##_event_flags_id;

/* Global Objects of the format g_##_name##_event_flags_id */
EVENT_FLAGS_TABLE(EXPAND_AS_OS_EVENT_FLAGS_ID)

/* Public Prototypes */
void os_event_flags_init(void);

#endif /* OS_EVENT_FLAGS_H_ */
