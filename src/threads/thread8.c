/*
 * thread8.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread8.h"
/* os */
#include "cmsis_os2.h" /* CMSIS RTOS header file */
/* project */
#include "message_queue.h"

void thread8(void *me)
{
	msg_t msg;

	while(1)
	{
		osDelay(50);

		msg.field1 = 1;
	    osMessageQueuePut(g_my_message_queue_id, &msg, 0, osWaitForever);

	    msg.field1 = 2;
	    osMessageQueuePut(g_my_message_queue_id, &msg, 0, osWaitForever);

	    msg.field1 = 4;
	    osMessageQueuePut(g_my_message_queue_id, &msg, 0, osWaitForever);
	}
}
