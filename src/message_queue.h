/*
 * message_queue.h
 *
 *  Created on: Jan 25, 2018
 *      Author: Andrew Lucas
 */

#ifndef MESSAGE_QUEUE_H_
#define MESSAGE_QUEUE_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"

#define MESSAGE_QUEUE_TABLE(ENTRY)               \
	   /* _name, _msg_count, _msg_size, _attr */ \
	ENTRY(my,     3,          1,        NULL)

#define EXPAND_AS_MESSAGE_QUEUE_ID(_name, _msg_count, _msg_size, _attr) osMessageQueueId_t g_##_name##_message_queue_id;

/* Global Objects of the format g_##_name##_message_queue_id */
MESSAGE_QUEUE_TABLE(EXPAND_AS_MESSAGE_QUEUE_ID)

/* Public Prototypes */
void message_queue_init(void);

#endif /* MESSAGE_QUEUE_H_ */
