/*
 * semaphore.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h" /* CMSIS RTOS header file */

#define SEMAPHORE_TABLE(ENTRY)                   \
	  /* _name, _count, _initial_count, _attr */ \
	ENTRY(empty, 3,      3,              NULL)   \
	ENTRY(full,  3,      0,              NULL)

#define EXPAND_AS_SEMAPHORE_ID(_name, _count, _initial_count, _attr) osSemaphoreId_t g_##_name##_id;

/* Global Objects of the format g_##_name##_id */
SEMAPHORE_TABLE(EXPAND_AS_SEMAPHORE_ID)

/* Public Prototypes */
void semaphore_init(void);

#endif /* SEMAPHORE_H_ */
