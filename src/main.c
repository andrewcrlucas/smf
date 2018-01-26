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

/* main function */
int main(void)
{
    /* Initialize CMSIS-RTOS */
    osKernelInitialize ();

    /* Initialize Objects */
    semaphore_init();
    mutex_init();
    thread_init();

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}
