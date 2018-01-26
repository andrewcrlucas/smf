/*
 * thread4.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread4.h"
/* os */
#include "cmsis_os2.h"
/* project */
#include "mutex.h"

void thread4(void *me)
{
	while(1)
	{
		/* Give up processor */
        osThreadYield();

        osMutexAcquire(g_resource1_mutex_id, osWaitForever);

        /* use resource for a period of time */
        osDelay(5);

        osMutexRelease(g_resource1_mutex_id);
	}
}
