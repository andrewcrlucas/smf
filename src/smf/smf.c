/*************************************************************************//**

  @file smf.c
  @brief Implementation file for the smf object

******************************************************************************/

/*****************************************************************************
  Includes
 *****************************************************************************/
#include "assert.h"
#include "cmsis_os2.h"

/* std c library */
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* module specific */
#include "smf.h"
#include "smf_class.h"

/* project specific */
//#include "trace_template.h"
//#include "target.h"

/*****************************************************************************
  Private variables
 *****************************************************************************/
DEFINE_THIS_FILE               /* defines filename string required by assert */

/*****************************************************************************
  Public functions
 *****************************************************************************/

/**************************************************************************//**

  @brief - Wraper function necessary for TDD

  @param mutex_id - Mutex identifier

  @return void

******************************************************************************/
__attribute__((weak)) void smf_release_mutex(osMutexId_t mutex_id)
{
    smf_release_mutex_body(mutex_id);
}

/**************************************************************************//**

  @brief

  @param mutex_id - Mutex identifier

  @return void

******************************************************************************/
void smf_release_mutex_body(osMutexId_t mutex_id)
{
    osStatus_t os_status;

    os_status = osMutexRelease(mutex_id);
    ASSERT(os_status == osOK);
}

/**************************************************************************//**

  @brief - Wraper function necessary for TDD

  @param message_queue_id - Message queue identifier
  @param p_mail - Pointer to mail message

  @return void

******************************************************************************/
__attribute__((weak)) void smf_send_command_message(osMessageQueueId_t message_queue_id,
                                                    const void * const p_mail)
{
    smf_send_command_message_body(message_queue_id, p_mail);
}

/**************************************************************************//**

  @brief

  @param message_queue_id - Message queue identifier
  @param p_mail - Pointer to mail message

  @return void

******************************************************************************/
void smf_send_command_message_body(osMessageQueueId_t message_queue_id,
                                   const void * const p_mail)
{
    osStatus_t os_status;

    os_status = osMessageQueuePut(message_queue_id, p_mail, 0, 0);
    ASSERT(os_status == osOK);
}

/**************************************************************************//**

  @brief - Wraper function necessary for TDD

  @param thread_id - Thread identifier
  @param p_signals - Pointer to signal mask

  @return void

******************************************************************************/
__attribute__((weak)) void smf_respond_to_client_with_signal(osThreadId_t thread_id, int32_t * p_signals)
{
    smf_respond_to_client_with_signal_body(thread_id, p_signals);
}

/**************************************************************************//**

  @brief

  @param thread_id - Thread identifier
  @param p_signals - Pointer to signal mask

  @return void

******************************************************************************/
void smf_respond_to_client_with_signal_body(osThreadId_t thread_id, int32_t * p_signals)
{
    if ((*p_signals != SMF_NO_RESPONSE_SIGNAL) &&
        (thread_id != NULL))
    {
        osEventFlagsSet(thread_id, *p_signals);
        *p_signals = SMF_NO_RESPONSE_SIGNAL;
    }
}

/**************************************************************************//**

  @brief - Wraper function necessary for TDD

  @param message_queue_id - Message queue identifier
  @param message - Message to put in the queue

  @return void

******************************************************************************/
__attribute__((weak)) void smf_respond_to_client_with_message(osMessageQueueId_t message_queue_id, uint32_t message)
{
    smf_respond_to_client_with_message_body(message_queue_id, message);
}

/**************************************************************************//**

  @brief

  @param message_queue_id - Message queue identifier
  @param message - Message to put in the queue

  @return void

******************************************************************************/
void smf_respond_to_client_with_message_body(osMessageQueueId_t message_queue_id, uint32_t message)
{
    osStatus_t os_status;

    if (message_queue_id != SMF_NO_RESPONSE_MESSAGE)
    {
        os_status = osMessageQueuePut(message_queue_id, (void *) message, 0, 0);
        ASSERT(os_status == osOK);

        message_queue_id = SMF_NO_RESPONSE_MESSAGE;
    }
}

/**************************************************************************//**

  @brief constructor

  @param me - Pointer to smf object
  @param p_state_jump_table - Pointer to table of state machine function
                              pointers
  @param initial_state - The state to start the state machine in
  @param trace_id - Three character string identifying the trace record type
  @param index - Distinguishes between multiple instances of a state machine
  @param n_states - Number of states for this state machine

  @return void

******************************************************************************/
void smf(smf_t * me,
         void (*const *p_state_jump_table) (void *),
         unsigned int initial_state,
         const char * trace_id,
         unsigned int index,
         unsigned int n_states)
{
    ASSERT(p_state_jump_table != NULL);

    me->p_state_jump_table = p_state_jump_table;
    me->state = initial_state;
    me->index = index;
    me->n_states = n_states;
    me->b_change_state = false;

    me->next_state = initial_state;
    me->event = EXIT_EVENT;

//    trace_template_new_and_subscribe(&me->p_trace_template,
//                                     trace_id,
//                                     (uint8_t *) &me->index,
//                                     (uint8_t *) &me->state,
//                                     NULL,
//                                     NULL,
//                                     NULL);

    if (trace_id != NULL)
    {
        me->b_trace_enabled = true;
    }
    else
    {
        me->b_trace_enabled = false;
    }
}

/**************************************************************************//**

  @brief deconstructor

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_(smf_t * me)
{
//    if (me->p_trace_template != NULL)
//    {
//        free(me->p_trace_template);
//        me->p_trace_template = NULL;
//    }

    me->p_state_jump_table = NULL;
}

/**************************************************************************//**

  @brief Getter for event attribute

  @param me - Pointer to smf object

  @return void

******************************************************************************/
uint32_t smf_get_event(smf_t * me)
{
    return me->event;
}

/**************************************************************************//**

  @brief Setter for event attribute

  @param me - Pointer to smf object
  @param pending - Event to pend on

  @return void

******************************************************************************/
void smf_set_pending_event(smf_t * me, unsigned int pending)
{
    me->pending = pending;
}

/**************************************************************************//**

  @brief Trigger a state change

  @param me - Pointer to smf object
  @param state - State to change to

  @return void

******************************************************************************/
void smf_change_state(smf_t * me, unsigned int state)
{
    me->next_state = state;
    me->b_change_state = true;
}

/**************************************************************************//**

  @brief Setter for delay parameter

  @param me - Pointer to smf object
  @param delay - Delay value in ms

  @return void

******************************************************************************/
void smf_set_delay(smf_t * me, uint32_t delay)
{
    me->delay = delay;
}

/**************************************************************************//**

  @brief Updates the pending object pointer to point to the appropriate os
         object

  @param me - Pointer to smf object
  @param p - Pointer to an os object

  @return void

******************************************************************************/
void smf_set_os_pend_object(smf_t * me, void * p)
{
    me->os_pend_object.p = p;
}

/**************************************************************************//**

  @brief

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_set_os_event_data_dst(p_smf_t me, void * p_os_event_data_dst)
{
    me->p_os_event_data_dst = p_os_event_data_dst;
}

/**************************************************************************//**

  @brief Enables tracing for the state machine

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_enable_tracing(smf_t * me)
{
    me->b_trace_enabled = true;
}

/**************************************************************************//**

  @brief Disables tracing for the state machine

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_disable_tracing(smf_t * me)
{
    me->b_trace_enabled = false;
}

/**************************************************************************//**

  @brief Gets the next event and issues it to the state machine

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_run(p_smf_t me)
{
    /* Verify me pointer and then index into our jump table is valid */
    if ((me == NULL) || (me->state >= me->n_states))
    {
        ASSERT(false);
    }
    else
    {
        /* Update our event variable */
        smf_trigger_event((p_smf_t) me);
        /* Call the appropriate state function */
        me->p_state_jump_table[me->state](me);
    }
}

/**************************************************************************//**

  @brief Generates the next event, either ENTRY_EVENT, EXIT_EVENT or another
         event provided by the pend_on_event function

  @param me - Pointer to smf object

  @return void

******************************************************************************/
void smf_trigger_event(smf_t * me)
{
    if (me->event == EXIT_EVENT)
    {
        me->b_change_state = false;
        me->event = ENTRY_EVENT;
        me->state = me->next_state;

//        if ((me->p_trace_template != NULL) && (me->b_trace_enabled == true))
//        {
//            trace_template_capture(me->p_trace_template);
//        }
    }
    else
    {
        /* Do this for both entry events and default events */
        if ((me->event == ENTRY_EVENT) || (me->b_change_state != true))
        {
            me->event = smf_pend_on_event(me);
        }
        else
        {
            /* Handle a change event request */
            me->event = EXIT_EVENT;
        }
    }
}

/**************************************************************************//**

  @brief Blocks thread pending an event

  @param me - Pointer to smf object

  @return The event that unblocked the thread

******************************************************************************/
unsigned int smf_pend_on_event(smf_t * me)
{
    osStatus_t os_status;
    unsigned int event;

    switch (me->pending)
    {
        case NO_EVENT:
        {
            event = NO_EVENT;
            break;
        }

        case TIMEOUT_EVENT:
        {
            os_status = osDelay(me->delay);
            ASSERT(os_status == osOK);

            event = TIMEOUT_EVENT;
            break;
        }

        case MUTEX_ACQUIRED_EVENT:
        {
            os_status = osMutexAcquire(me->os_pend_object.mutex_id, me->delay);

            if (os_status == osOK)
            {
                event = MUTEX_ACQUIRED_EVENT;
            }
            else if (os_status == osErrorTimeout)
            {
                event = TIMEOUT_EVENT;
            }
            else
            {
                ASSERT(false);
            }

            break;
        }

        case SEMAPHORE_ACQUIRED_EVENT:
        {
            os_status = osSemaphoreAcquire(me->os_pend_object.semaphore_id, me->delay);

            if (os_status == osOK)
            {
                event = SEMAPHORE_ACQUIRED_EVENT;
            }
            else if (os_status == osErrorTimeout)
            {
                event = TIMEOUT_EVENT;
            }
            else
            {
                ASSERT(false);
            }

            break;
        }

        case SIGNAL_RECEIVED_EVENT:
        {
            uint32_t return_value;

            return_value = osThreadFlagsWait(me->os_pend_object.mask, osFlagsWaitAny, me->delay);

            if ((return_value & (1ul << ((sizeof(return_value) * 8) - 1))) == 0)
            {
                /* Top bit is clear meaning that a flag is received */

                /* copy signal mask to destination */
                *(uint32_t *) me->p_os_event_data_dst = return_value;
                event = SIGNAL_RECEIVED_EVENT;
            }
            else
            {
                /* Top bit is set meaning that an error was returned, cast as error status */
                os_status = (osStatus_t) return_value;

                if (os_status == osOK)
                {
                    event = NO_EVENT;
                }
                else if (os_status == osErrorTimeout)
                {
                    event = TIMEOUT_EVENT;
                }
                else
                {
                    ASSERT(false); /* bad status */
                }
            }

            break;
        }

        case FLAG_RECEIVED_EVENT:
        {
            uint32_t return_value;

            return_value = osEventFlagsWait(me->os_pend_object.event_flags_id, me->os_pend_object.mask, osFlagsWaitAny, me->delay);

            if ((return_value & (1ul << ((sizeof(return_value) * 8) - 1))) == 0)
            {
                /* Top bit is clear meaning that a flag is received */

                /* copy signal mask to destination */
                *(uint32_t *) me->p_os_event_data_dst = return_value;
                event = SIGNAL_RECEIVED_EVENT;
            }
            else
            {
                /* Top bit is set meaning that an error was returned, cast as error status */
                os_status = (osStatus_t) return_value;

                if (os_status == osOK)
                {
                    event = NO_EVENT;
                }
                else if (os_status == osErrorTimeout)
                {
                    event = TIMEOUT_EVENT;
                }
                else
                {
                    ASSERT(false); /* bad status */
                }
            }

            break;
        }

        case MESSAGE_RECEIVED_EVENT:
        {
            os_status = osMessageQueueGet(me->os_pend_object.message_queue_id, (uint8_t *) me->p_os_event_data_dst, 0, me->delay);

            if (os_status == osOK)
            {
                event = MESSAGE_RECEIVED_EVENT;
            }
            else if (os_status == osErrorTimeout)
            {
                event = TIMEOUT_EVENT;
            }
            else if (os_status == osErrorResource)
            {
                event = NO_EVENT;
            }
            else
            {
                ASSERT(false); /* bad status */
            }

            break;
        }

        default:
        {
            ASSERT(false);
            break;
        }
    }

    return event;
}
