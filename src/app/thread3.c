/*
 * thread3.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread3.h"
/* os */
#include "cmsis_os2.h"
#include "os_mutex.h"

void thread3(void *me)
{
	while(1)
	{
		/* Give up processor */
        osThreadYield();

        osMutexAcquire(g_my_resource_mutex_id, osWaitForever);

        /* use resource for a period of time */
        osDelay(3);

        osMutexRelease(g_my_resource_mutex_id);
	}
}
