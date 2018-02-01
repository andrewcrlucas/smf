/*
 * os_thread.c
 */

/* module */
#include "os_thread.h"
/* project */
#include "thread0.h"
#include "thread1.h"
#include "thread2.h"
#include "thread3.h"
#include "thread4.h"
#include "thread5.h"
#include "thread6.h"
#include "thread7.h"
#include "thread8.h"
#include "thread9.h"

#define EXPAND_AS_OS_THREAD_ATTR(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
    osThreadAttr_t _name##_attr =                                                                                      \
    {                                                                                                                  \
        .name = #_name,                                                                                                \
        .attr_bits = _attr_bits,                                                                                       \
        .cb_mem = _cb_mem,                                                                                             \
        .cb_size = _cb_size,                                                                                           \
        .stack_mem = _stack_mem,                                                                                       \
        .stack_size = _stack_size,                                                                                     \
        .priority = _priority,                                                                                         \
        .tz_module = _tz_module                                                                                        \
    };

#define EXPAND_AS_OS_THREAD_NEW(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
    g_##_name##_thread_id = osThreadNew(_name, (void *) 0, &_name##_attr);

void os_thread_init(void)
{
    /* Declare attr objects */
    THREAD_TABLE(EXPAND_AS_OS_THREAD_ATTR)
    /* Create thread objects */
    THREAD_TABLE(EXPAND_AS_OS_THREAD_NEW)
}

