/*
 * thread.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

#ifndef THREAD_H_
#define THREAD_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h" /* CMSIS RTOS header file */

#define THREAD_TABLE(ENTRY) \
	ENTRY(thread0, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread1, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread2, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread3, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread4, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread5, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread6, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread7, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0)

#define EXPAND_AS_THREAD_IDS(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
    osThreadId_t g_##_name##_id;

/* Global Objects */
THREAD_TABLE(EXPAND_AS_THREAD_IDS)

/* Public Prototypes */
void thread_init(void);

#endif /* THREAD_H_ */
