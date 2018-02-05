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
#include "heartbeat.h"
#include "digital_output.h"

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

    digital_output_init();

    //BSP_LED_DeInit(Led_TypeDef Led);
    //BSP_LED_On(Led_TypeDef Led);
    //BSP_LED_Off(Led_TypeDef Led);
    //BSP_LED_Toggle(Led_TypeDef Led);
    heartbeat_start();

    /* Start thread execution */
    osKernelStart ();

    /* Infinite loop */
    while (1)
    {
        /* Add application code here */
    }
}

