/**************************************************************************//**

  @file notification_queue.h
  @brief Public API definition file for the notification_queue object

******************************************************************************/
#ifndef NOTIFICATION_QUEUE_H
#define NOTIFICATION_QUEUE_H

/******************************************************************************
  Includes
******************************************************************************/
#include "cmsis_os2.h"
#include <stdbool.h>

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
#define NOTIFICATION_QUEUE_DEPTH 4

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
typedef struct notification_queue * p_notification_queue_t;

/******************************************************************************
  Public Prototypes
******************************************************************************/
extern p_notification_queue_t notification_queue_new(void);
extern void notification_queue_delete(p_notification_queue_t);
extern bool notification_queue_is_empty(p_notification_queue_t const);
extern bool notification_queue_is_full(p_notification_queue_t const);
extern void notification_queue_subscribe(p_notification_queue_t const, uint8_t, osThreadId_t, int32_t);
extern void notification_queue_unsubscribe(p_notification_queue_t const, osThreadId_t, int32_t);
extern void notification_queue_flush(p_notification_queue_t const);
extern void notification_queue_update_state(p_notification_queue_t const, uint8_t);

#endif
