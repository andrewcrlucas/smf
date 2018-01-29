/*
 * thread2.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread2.h"
/* os */
#include "cmsis_os2.h"
/* project */
#include "semaphore.h"

void thread2(void *me)
{
	while(1)
	{
        osSemaphoreAcquire(g_full_id, osWaitForever);
        // consume data
        osSemaphoreRelease(g_empty_id);
	}
}
