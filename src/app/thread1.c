/*
 * thread1.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread1.h"
/* os */
#include "cmsis_os2.h"
#include "os_semaphore.h"

void thread1(void *me)
{
	while(1)
	{
        osSemaphoreAcquire(g_empty_id, osWaitForever);
        // produce data
        osSemaphoreRelease(g_full_id);
	}
}
