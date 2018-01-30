/*
 * os_mutex.h
 */

#ifndef OS_MUTEX_H_
#define OS_MUTEX_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"

#define MUTEX_TABLE(ENTRY) \
	  /* _name, _attr */   \
	ENTRY(my_resource)

#define EXPAND_AS_OS_MUTEX_ID(_name) osMutexId_t g_##_name##_mutex_id;

/* Global Objects of the format g_##_name##_id */
MUTEX_TABLE(EXPAND_AS_OS_MUTEX_ID)

/* Public Prototypes */
void os_mutex_init(void);

#endif /* OS_MUTEX_H_ */
