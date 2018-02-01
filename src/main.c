/*
 * main.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"
/* project */
#include "RTE_Components.h"
#include "os_event_flags.h"
#include "os_message_queue.h"
#include "os_mutex.h"
#include "os_semaphore.h"
#include "os_thread.h"
#include "os_timer.h"

/* main function */
int main(void)
{
    /* Initialize CMSIS-RTOS */
    osKernelInitialize ();

    /* Initialize RTOS Objects */
    os_semaphore_init();
    os_mutex_init();
    os_event_flags_init();
    os_message_queue_init();
    os_timer_init();

    /* Initialize Threads */
    os_thread_init();

    osTimerStart(g_my_os_timer_id, 100);

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}

