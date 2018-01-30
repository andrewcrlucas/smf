/*
 * thread0.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread0.h"
/* os */
#include "cmsis_os2.h"

void thread0(void *me)
{
	int count = 0;

	while(1)
	{
		count++;
        osDelay(1);
	}
}
