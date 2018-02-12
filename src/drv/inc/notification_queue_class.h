/**************************************************************************//**

  @file notification_queue_class.h
  @brief Private class definition file for the notification_queue object

******************************************************************************/
#ifndef NOTIFICATION_QUEUE_CLASS_H
#define NOTIFICATION_QUEUE_CLASS_H

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
typedef struct
{
    uint8_t notification_state;
    osThreadId_t thread_id;                         /* subscribing thread id */
    int32_t signal;                          /* signal to use to report back */
} notify_entry_t;

typedef struct notification_queue
{
    bool b_empty;
    bool b_full;
    notify_entry_t notification_queue[NOTIFICATION_QUEUE_DEPTH];
} notification_queue_t;

/******************************************************************************
  Prototypes
******************************************************************************/
extern p_notification_queue_t notification_queue_new_body(void);
extern void notification_queue_update_state_body(p_notification_queue_t, uint8_t);
extern void notification_queue_subscribe_body(p_notification_queue_t const, uint8_t, osThreadId_t, int32_t);
extern void notification_queue_unsubscribe_body(p_notification_queue_t const, osThreadId_t, int32_t);

#endif
