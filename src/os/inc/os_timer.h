/*************************************************************************//**

  @file os_timer.h
  @brief

******************************************************************************/
#ifndef OS_TIMER_H_
#define OS_TIMER_H_

/******************************************************************************
  Includes
******************************************************************************/
/* os */
#include "cmsis_os2.h"

#define OS_TIMER_TABLE(ENTRY)                                    \
	/*   _name,  _func,              _type,            _arg   */ \
    ENTRY(my,     thread10_callback,  osTimerPeriodic,  NULL)

#define EXPAND_AS_OS_TIMER_ID(_name, _func, _type, _arg) osTimerId_t g_##_name##_os_timer_id;

/* Global Objects of the format g_##_name##_os_timer_id */
OS_TIMER_TABLE(EXPAND_AS_OS_TIMER_ID)

/* Public Prototypes */
void os_timer_init(void);

#endif /* OS_TIMER_H_ */
