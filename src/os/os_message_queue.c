/*************************************************************************//**

  @file os_message_queue.c
  @brief

******************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "os_message_queue.h"
/* os */
#include "FreeRTOS.h"
#include "queue.h"

#define EXPAND_AS_OS_MESSAGE_QUEUE_ATTR(_name, _msg_count, _msg_size) \
    osMessageQueueAttr_t _name##_attr =                               \
    {                                                                 \
        .name = #_name,                                               \
        .attr_bits = 0,                                               \
        .cb_mem = NULL,                                               \
        .cb_size = 0,                                                 \
        .mq_mem = NULL,                                               \
        .mq_size = 0                                                  \
    };

#define EXPAND_AS_OS_MESSAGE_QUEUE_NEW(_name, _msg_count, _msg_size) g_##_name##_message_queue_id = osMessageQueueNew(_msg_count, _msg_size, &_name##_attr);
#define EXPAND_AS_OS_MESSAGE_QUEUE_ADD_TO_REGISTRY(_name, _msg_count, _msg_size) vQueueAddToRegistry(g_##_name##_message_queue_id, #_name);

void os_message_queue_init(void)
{
    /* Declare attr objects */
    MESSAGE_QUEUE_TABLE(EXPAND_AS_OS_MESSAGE_QUEUE_ATTR)
    /* Create message_queue objects */
    MESSAGE_QUEUE_TABLE(EXPAND_AS_OS_MESSAGE_QUEUE_NEW)

#ifdef DEBUG
    /* For RTOS aware debugging we need to register the message_queues */
    MESSAGE_QUEUE_TABLE(EXPAND_AS_OS_MESSAGE_QUEUE_ADD_TO_REGISTRY)
#endif
}

