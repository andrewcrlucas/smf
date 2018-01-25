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
#include "cmsis_os2.h" /* CMSIS RTOS header file */
/* project */
#include "RTE_Components.h"             // Component selection
#include "thread.h"
#include "semaphore.h"

/* main function */
int main(void)
{
    /* Initialize CMSIS-RTOS */
    osKernelInitialize ();

    /* Initialize Objects */
    semaphore_init();
    thread_init();

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}
