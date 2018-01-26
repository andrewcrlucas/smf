/*
 * thread0.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread0.h"
/* os */
#include "cmsis_os2.h" /* CMSIS RTOS header file */

void thread0(void *me)
{
	int count = 0;

	while(1)
	{
		count++;
        osDelay(1);
	}
}
