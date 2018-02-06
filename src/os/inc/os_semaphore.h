/*************************************************************************//**

  @file os_semaphore.h
  @brief

******************************************************************************/
#ifndef OS_SEMAPHORE_H_
#define OS_SEMAPHORE_H_

/******************************************************************************
  Includes
******************************************************************************/
/* os */
#include "cmsis_os2.h"

#define SEMAPHORE_TABLE(ENTRY)            \
	  /* _name, _count, _initial_count */ \
	ENTRY(empty, 3,      3)               \
	ENTRY(full,  3,      0)

#define EXPAND_AS_OS_SEMAPHORE_ID(_name, _count, _initial_count) osSemaphoreId_t g_##_name##_id;

/* Global Objects of the format g_##_name##_id */
SEMAPHORE_TABLE(EXPAND_AS_OS_SEMAPHORE_ID)

/* Public Prototypes */
void os_semaphore_init(void);

#endif /* OS_SEMAPHORE_H_ */
