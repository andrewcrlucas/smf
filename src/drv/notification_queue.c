/**************************************************************************//**

  @file notification_queue.c
  @brief Implementation file for the notification_queue object

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* std c library */
#include "cmsis_os2.h"
#include <stdbool.h>
#include <stdlib.h>

/* module specific */
#include "notification_queue.h"
#include "notification_queue_class.h"

/* project specific */
#include "assert.h"

/******************************************************************************
  Private Prototypes
******************************************************************************/
static void initialize_queue_entry(notify_entry_t *);

/******************************************************************************
  Private Variables
******************************************************************************/
DEFINE_THIS_FILE

/******************************************************************************
  Public Functions
******************************************************************************/

/**************************************************************************//**

  @brief

  @param me
  @param state

  @return void

******************************************************************************/
__attribute__((weak)) void notification_queue_update_state(p_notification_queue_t const me, uint8_t state)
{
    notification_queue_update_state_body(me, state);
}

/**************************************************************************//**

  @brief

  @param me
  @param state

  @return void

******************************************************************************/
void notification_queue_update_state_body(p_notification_queue_t const me, uint8_t state)
{
    /* b_empty is set false if an entry is found.  If no entries are found,
     * b_empty stays set as true */
    me->b_empty = true;

    for (int i = 0; i < NOTIFICATION_QUEUE_DEPTH; i++)
    {
        if (me->notification_queue[i].thread_id != NULL)
        {
            if (me->notification_queue[i].notification_state == state)
            {
                osThreadFlagsSet(me->notification_queue[i].thread_id,
                                 me->notification_queue[i].signal);

                initialize_queue_entry(&me->notification_queue[i]);

                me->b_full = false;
            }
            else
            {
                /* notification is for a different state, so queue is not empty */
                me->b_empty = false;
            }
        }
    }
}

/**************************************************************************//**

  @brief

  @param me
  @param thread_id
  @param signal

  @return void

******************************************************************************/
__attribute__((weak)) void notification_queue_unsubscribe(p_notification_queue_t const me, osThreadId_t thread_id, int32_t signal)
{
    notification_queue_unsubscribe_body(me, thread_id, signal);
}

/**************************************************************************//**

  @brief

  @param me
  @param thread_id
  @param signal

  @return void

******************************************************************************/
void notification_queue_unsubscribe_body(p_notification_queue_t const me, osThreadId_t thread_id, int32_t signal)
{
    if (me->b_empty == true)
    {
        /* queue is empty, skip checking queue elements */
    }
    else
    {
        /* b_empty is set false if an entry is found.  If no entries are found,
         * b_empty stays set as true */
        me->b_empty = true;

        for (int i = 0; i < NOTIFICATION_QUEUE_DEPTH; i++)
        {
            if (me->notification_queue[i].thread_id != NULL)
            {
                if ((me->notification_queue[i].thread_id == thread_id) &&
                    (me->notification_queue[i].signal == signal))
                {
                    initialize_queue_entry(&me->notification_queue[i]);

                    me->b_full = false;
                }
                else
                {
                    /* notification is for a different state, so queue is not empty */
                    me->b_empty = false;
                }
            }
        }
    }

    /* client thread's signal is no longer wanted so clear it */
    osThreadFlagsClear(signal);
}

/**************************************************************************//**

  @brief

  @param me
  @param state
  @param thread_id
  @param signal

  @return void

******************************************************************************/
__attribute__((weak)) void notification_queue_subscribe(p_notification_queue_t const me, uint8_t state, osThreadId_t thread_id, int32_t signal)
{
    notification_queue_subscribe_body(me, state, thread_id, signal);
}

/**************************************************************************//**

  @brief

  @param me
  @param state
  @param thread_id
  @param signal

  @return void

******************************************************************************/
void notification_queue_subscribe_body(p_notification_queue_t const me, uint8_t state, osThreadId_t thread_id, int32_t signal)
{
    int i = 0;

    while ((i < NOTIFICATION_QUEUE_DEPTH) &&
           (me->notification_queue[i].thread_id != NULL))
    {
        i++;
    }

    if (i == (NOTIFICATION_QUEUE_DEPTH - 1))
    {
        me->b_full = true;
    }
    else if (i > (NOTIFICATION_QUEUE_DEPTH - 1))
    {
        ASSERT(i > NOTIFICATION_QUEUE_DEPTH); /* notification queue is full */
        return;
    }
    else
    {
        /* Default case */
    }

    me->notification_queue[i].notification_state = state;
    me->notification_queue[i].signal = signal;
    me->notification_queue[i].thread_id = thread_id;

    me->b_empty = false;
}

/**************************************************************************//**

  @brief

  @param void

  @return p_notification_queue_t

******************************************************************************/
__attribute__((weak)) p_notification_queue_t notification_queue_new(void)
{
    return notification_queue_new_body();
}

/**************************************************************************//**

  @brief

  @param void

  @return p_notification_queue_t

******************************************************************************/
p_notification_queue_t notification_queue_new_body(void)
{
    notification_queue_t * me = (notification_queue_t *) malloc(sizeof(notification_queue_t));

    if (me == NULL)
    {
        ASSERT(false);
    }
    else
    {
        for (unsigned int i = 0; i < NOTIFICATION_QUEUE_DEPTH; i++)
        {
            initialize_queue_entry(&me->notification_queue[i]);
        }

        me->b_empty = true;
        me->b_full = false;
    }

    return me;
}

/**************************************************************************//**

  @brief

  @param me

  @return void

******************************************************************************/
void notification_queue_delete(p_notification_queue_t me)
{
    if (me != NULL)
    {
        free(me);
    }
}

/**************************************************************************//**

  @brief

  @param me

  @return bool

******************************************************************************/
bool notification_queue_is_empty(p_notification_queue_t me)
{
    return me->b_empty;
}

/**************************************************************************//**

  @brief

  @param me

  @return bool

******************************************************************************/
bool notification_queue_is_full(p_notification_queue_t me)
{
    return me->b_full;
}

/**************************************************************************//**

  @brief

  @param me

  @return void

******************************************************************************/
void notification_queue_flush(p_notification_queue_t const me)
{
    ASSERT(me != NULL);

    for (int i = 0; i < NOTIFICATION_QUEUE_DEPTH; i++)
    {
        initialize_queue_entry(&me->notification_queue[i]);
    }

    me->b_empty = true;
    me->b_full = false;
}

/******************************************************************************
  Private Helpers
******************************************************************************/

/**************************************************************************//**

  @brief

  @param p_entry

  @return void

******************************************************************************/
static void initialize_queue_entry(notify_entry_t * p_entry)
{
    p_entry->notification_state = 0xff;
    p_entry->thread_id = NULL;
    p_entry->signal = 0;
}

