/*
 * smf.c
 */

/*****************************************************************************
 * Includes                                                                  *
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

/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
DEFINE_THIS_FILE               /* defines filename string required by assert */

/*****************************************************************************
 * Public Interface Functions                                                *
 *****************************************************************************/

/******************************************************************************

  FUNCTION:     smf_release_mutex

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void smf_release_mutex(osMutexId_t mutex_id)
{
    smf_release_mutex_body(mutex_id);
}

/******************************************************************************

  FUNCTION:     smf_release_mutex_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void smf_release_mutex_body(osMutexId_t mutex_id)
{
    osStatus_t os_status;

    os_status = osMutexRelease(mutex_id);
    ASSERT(os_status == osOK);
}

/******************************************************************************

  FUNCTION:     smf_send_command_mail

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void smf_send_command_message(osMessageQueueId_t message_queue_id,
                                                             const void * const p_mail)
{
    smf_send_command_message_body(message_queue_id, p_mail);
}

/******************************************************************************

  FUNCTION:     smf_send_command_message_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void smf_send_command_message_body(osMessageQueueId_t message_queue_id,
                                             const void * const p_mail)
{
    osStatus_t os_status;

    os_status = osMessageQueuePut(message_queue_id, p_mail, 0, 0);
    ASSERT(os_status == osOK);
}

/******************************************************************************

  FUNCTION:     smf_respond_to_client_with_signal

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void smf_respond_to_client_with_signal(osThreadId_t thread_id, int32_t * p_signals)
{
    smf_respond_to_client_with_signal_body(thread_id, p_signals);
}

/******************************************************************************

  FUNCTION:     smf_respond_to_client_with_signal_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

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

/******************************************************************************

  FUNCTION:     smf_respond_to_client_with_message

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void smf_respond_to_client_with_message(osMessageQueueId_t message_queue_id, uint32_t message)
{
    smf_respond_to_client_with_message_body(message_queue_id, message);
}

/******************************************************************************

  FUNCTION:     smf_respond_to_client_with_message_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

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

/******************************************************************************

  FUNCTION:     smf

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance
                initial_state - starting state
                p_func - pointer to event pending function
                instance_id - id for this instance used for tracing
                trace_id - 3 character string to identify trace record type

  RETURNS:      void

  DESCRIPTION:  constructor

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
    me->b_halt_event = false;
    me->b_halt_event_polling = false;

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

/******************************************************************************

  FUNCTION:     smf_

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:  deconstructor

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

/******************************************************************************

  FUNCTION:     smf_get_event

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      event

  DESCRIPTION:  getter for event attribute

******************************************************************************/
uint32_t smf_get_event(smf_t * me)
{
    return me->event;
}

/******************************************************************************

  FUNCTION:     smf_set_pending_event

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance
                pending - event to pend on

  RETURNS:      void

  DESCRIPTION:  setter for pending attribute

******************************************************************************/
void smf_set_pending_event(smf_t * me, unsigned int pending)
{
    me->pending = pending;
}

/******************************************************************************

  FUNCTION:     smf_change_state

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance
                state - state to change to

  RETURNS:      void

  DESCRIPTION:  triggers a state change

******************************************************************************/
void smf_change_state(smf_t * me, unsigned int state)
{
    me->next_state = state;
    me->b_change_state = true;
}

/******************************************************************************

  FUNCTION:     smf_set_delay

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance
                delay - delay variable

  RETURNS:      void

  DESCRIPTION:  set the delay variable

******************************************************************************/
void smf_set_delay(smf_t * me, uint32_t delay)
{
    me->delay = delay;
}

/******************************************************************************

  FUNCTION:     smf_set_os_pend_object

  SCOPE:        private

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_set_os_pend_object(smf_t * me, void * p)
{
    me->os_pend_object.p = p;
}

/******************************************************************************

  FUNCTION:     smf_set_os_event_data_dst

  SCOPE:        private

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void smf_set_os_event_data_dst(p_smf_t me, void * p_os_event_data_dst)
{
    me->p_os_event_data_dst = p_os_event_data_dst;
}

/******************************************************************************

  FUNCTION:     smf_disable_tracing

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_disable_tracing(smf_t * me)
{
    me->b_trace_enabled = false;
}

/******************************************************************************

  FUNCTION:     smf_enable_tracing

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_enable_tracing(smf_t * me)
{
    me->b_trace_enabled = true;
}

/******************************************************************************

  FUNCTION:     smf_set_halt_event

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_set_halt_event(smf_t * me)
{
    me->b_halt_event = true;
}

/******************************************************************************

  FUNCTION:     smf_clr_halt_event

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_clr_halt_event(smf_t * me)
{
    me->b_halt_event = false;
    me->b_halt_event_polling = false;
}

/******************************************************************************

  FUNCTION:     smf_enable_halt_event_polling

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void smf_enable_halt_event_polling(smf_t * me)
{
    me->b_halt_event_polling = true;
}

/******************************************************************************

  FUNCTION:     smf_run

  SCOPE:        public

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:  executes state jump table

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

/******************************************************************************

  FUNCTION:     smf_trigger_event

  SCOPE:        private

  PARAMETERS:   me - pointer to smf instance

  RETURNS:      void

  DESCRIPTION:  handles the sequencing of events

******************************************************************************/
void smf_trigger_event(smf_t * me)
{
    if (me->event == EXIT_EVENT)
    {
        me->b_change_state = false;
        me->event = ENTRY_EVENT;
        me->state = me->next_state;
        me->b_halt_event_polling = false;

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
            if ((me->b_halt_event_polling == true) &&
                (me->delay != 0)                   &&
                (me->pending != NO_EVENT))
            {
                me->event = smf_pend_on_event_and_poll_for_halt_event(me);
            }
            else
            {
                me->event = smf_pend_on_event(me);
            }
        }
        else
        {
            /* Handle a change event request */
            me->event = EXIT_EVENT;
        }
    }
}

/******************************************************************************

  FUNCTION:     smf_pend_on_event_and_poll_for_halt_event

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
unsigned int smf_pend_on_event_and_poll_for_halt_event(smf_t * me)
{
    unsigned int event;

    me->delay_counter = me->delay;
    me->delay = SMF_HALT_EVENT_POLLING_PERIOD;

    do
    {
        if (me->delay_counter < SMF_HALT_EVENT_POLLING_PERIOD)
        {
            /* remaining delay is less than SMF_HALT_EVENT_POLLING_PERIOD,
             * so use the remaining delay value for the last delay */
            me->delay = me->delay_counter;
        }

        event = smf_pend_on_event(me);

        if (me->delay_counter != osWaitForever)
        {
            me->delay_counter = me->delay_counter - me->delay;
        }

        if (me->b_halt_event == true)
        {
            me->b_halt_event = false;
            return HALT_EVENT;
        }
    } while ((me->delay_counter > 0) && (event == TIMEOUT_EVENT));

    return event;
}

/******************************************************************************

  FUNCTION:     smf_pend_on_event

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

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
