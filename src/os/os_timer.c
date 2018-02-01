/*
 * os_timer.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_timer.h"
/* os */
#include "cmsis_os2.h"
/* project */
#include "thread10.h"

#define EXPAND_AS_OS_TIMER_ATTR(_name, _func, _type, _arg) \
    osTimerAttr_t _name##_attr =                           \
    {                                                      \
        .name = #_name,                                    \
        .attr_bits = 0,                                    \
        .cb_mem = NULL,                                    \
        .cb_size = 0,                                      \
    };

#define EXPAND_AS_OS_TIMER_NEW(_name, _func, _type, _arg) \
    g_##_name##_os_timer_id = osTimerNew(_func, _type, _arg, &_name##_attr);

void os_timer_init(void)
{
    /* Declare attr objects */
    OS_TIMER_TABLE(EXPAND_AS_OS_TIMER_ATTR)
    /* Create timer objects */
    OS_TIMER_TABLE(EXPAND_AS_OS_TIMER_NEW)
}

