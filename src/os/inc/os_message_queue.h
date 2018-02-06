/*************************************************************************//**

  @file os_message_queue.h
  @brief

******************************************************************************/

#ifndef OS_MESSAGE_QUEUE_H_
#define OS_MESSAGE_QUEUE_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* os */
#include "cmsis_os2.h"

#define MESSAGE_QUEUE_TABLE(ENTRY)        \
	   /* _name, _msg_count, _msg_size */ \
	ENTRY(my,     3,          1)

#define EXPAND_AS_OS_MESSAGE_QUEUE_ID(_name, _msg_count, _msg_size) osMessageQueueId_t g_##_name##_message_queue_id;

/* Global Objects of the format g_##_name##_message_queue_id */
MESSAGE_QUEUE_TABLE(EXPAND_AS_OS_MESSAGE_QUEUE_ID)

/* Public Prototypes */
void os_message_queue_init(void);

#endif /* OS_MESSAGE_QUEUE_H_ */
