/*
 * thread.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

#include "thread.h"
#include "thread0.h"
#include "thread1.h"
#include "thread2.h"
#include "thread3.h"
#include "thread4.h"

#define EXPAND_AS_THREAD_ATTR(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
	osThreadAttr_t _name##_attr =                                                                                   \
	{                                                                                                               \
        .name = #_name,                                                                                             \
        .attr_bits = _attr_bits,                                                                                    \
        .cb_mem = _cb_mem,                                                                                          \
        .cb_size = _cb_size,                                                                                        \
        .stack_mem = _stack_mem,                                                                                    \
        .stack_size = _stack_size,                                                                                  \
        .priority = _priority,                                                                                      \
        .tz_module = _tz_module                                                                                     \
	};

#define EXPAND_AS_THREAD_NEW(_name, _attr_bits, _cb_mem, _cb_size, _stack_mem, _stack_size, _priority, _tz_module) \
    g_##_name##_id = osThreadNew(_name, (void *) 0, &_name##_attr);

void thread_init(void)
{
    THREAD_TABLE(EXPAND_AS_THREAD_ATTR)
    THREAD_TABLE(EXPAND_AS_THREAD_NEW)
}
