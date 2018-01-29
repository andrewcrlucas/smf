/*
 * thread9.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread9.h"
/* os */
#include "cmsis_os2.h"
/* project */
#include "message_queue.h"
#include "thread8.h"

void thread9(void *me)
{
	msg_t msg;

	while(1)
	{
	    osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
	    osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
	    osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
	    osDelay(1);
	}
}
