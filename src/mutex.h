/*
 * mutex.h
 *
 *  Created on: Jan 26, 2018
 *      Author: al100017
 */

#ifndef SRC_MUTEX_H_
#define SRC_MUTEX_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"

#define MUTEX_TABLE(ENTRY) \
	  /* _name, _attr */   \
	ENTRY(resource1, NULL)

#define EXPAND_AS_MUTEX_ID(_name, _attr) osMutexId_t g_##_name##_mutex_id;

/* Global Objects of the format g_##_name##_id */
MUTEX_TABLE(EXPAND_AS_MUTEX_ID)

/* Public Prototypes */
void mutex_init(void);

#endif /* SRC_MUTEX_H_ */
