/*
 * main.c
 *
 *  Created on: Jan 24, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"
/* project */
#include "RTE_Components.h"
#include "thread.h"
#include "semaphore.h"
#include "mutex.h"
#include "event_flags.h"
#include "message_queue.h"
#include "os_timer.h"

/* main function */
int main(void)
{
    /* Initialize CMSIS-RTOS */
    osKernelInitialize ();

    /* Initialize RTOS Objects */
    semaphore_init();
    mutex_init();
    event_flags_init();
    message_queue_init();
    os_timer_init();

    /* Initialize Threads */
    thread_init();

    osTimerStart(g_my_os_timer_id, 100);

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}
