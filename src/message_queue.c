/*
 * message_queue.c
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "message_queue.h"
/* os */
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_MESSAGE_QUEUE_NEW(_name, _msg_count, _msg_size, _attr) g_##_name##_message_queue_id = osMessageQueueNew(_msg_count, _msg_size, _attr);
#define EXPAND_AS_MESSAGE_QUEUE_ADD_TO_REGISTRY(_name, _msg_count, _msg_size, _attr) vQueueAddToRegistry(g_##_name##_message_queue_id, #_name);

void message_queue_init(void)
{
	/* Create message_queue objects */
    MESSAGE_QUEUE_TABLE(EXPAND_AS_MESSAGE_QUEUE_NEW)

#ifdef DEBUG
	/* For RTOS aware debugging we need to register the message_queues */
    MESSAGE_QUEUE_TABLE(EXPAND_AS_MESSAGE_QUEUE_ADD_TO_REGISTRY)
#endif

}

