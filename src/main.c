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

/* main function */
int main(void)
{
    /* Initialize CMSIS-RTOS */
    osKernelInitialize ();

    /* Initialize RTOS Objects */
    semaphore_init();
    mutex_init();
    event_flags_init();

    /* Initialize Threads */
    thread_init();

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}
