/*
 * os_thread.h
 */

#ifndef OS_THREAD_H_
#define OS_THREAD_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h" /* CMSIS RTOS header file */

#define THREAD_TABLE(ENTRY) \
	ENTRY(thread1, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread2, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread3, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread4, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread5, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread6, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread7, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread8, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0) \
	ENTRY(thread9, osThreadDetached, 0, 0, 0, 0, osPriorityNormal, 0)

#define EXPAND_AS_OS_THREAD_IDS(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
    osThreadId_t g_##_name##_thread_id;

/* Global Objects */
THREAD_TABLE(EXPAND_AS_OS_THREAD_IDS)

/* Public Prototypes */
void os_thread_init(void);

#endif /* OS_THREAD_H_ */
