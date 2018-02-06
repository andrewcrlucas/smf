/*************************************************************************//**

  @file os_event_flags.c
  @brief

******************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_event_flags.h"
/* os */
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_OS_EVENT_FLAGS_ATTR(_name) \
    osEventFlagsAttr_t _name##_attr =        \
    {                                        \
        .name = #_name,                      \
        .attr_bits = 0,                      \
        .cb_mem = NULL,                      \
        .cb_size = 0,                        \
    };

#define EXPAND_AS_OS_EVENT_FLAGS_NEW(_name) g_##_name##_event_flags_id = osEventFlagsNew(&_name##_attr);

void os_event_flags_init(void)
{
    /* Declare attr objects */
    EVENT_FLAGS_TABLE(EXPAND_AS_OS_EVENT_FLAGS_ATTR)
    /* Create event_flags objects */
    EVENT_FLAGS_TABLE(EXPAND_AS_OS_EVENT_FLAGS_NEW)
}

