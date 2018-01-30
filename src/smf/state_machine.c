/*
 * state_machine.c
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
#include "state_machine.h"
#include "state_machine_class.h"

/* project specific */
//#include "trace_template.h"
//#include "target.h"

/*****************************************************************************/
/* Private Variables                                                         */
/*****************************************************************************/
DEFINE_THIS_FILE   /* defines g_this_file[] with the name of the source file */

/*****************************************************************************
 * Public Interface Functions                                                *
 *****************************************************************************/

/******************************************************************************

  FUNCTION:     state_machine_release_mutex

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void state_machine_release_mutex(osMutexId_t mutex)
{
    state_machine_release_mutex_body(mutex);
}

/******************************************************************************

  FUNCTION:     state_machine_release_mutex_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void state_machine_release_mutex_body(osMutexId_t mutex)
{
    osStatus_t os_status;

    os_status = osMutexRelease(mutex);
    ASSERT(os_status == osOK);
}

/******************************************************************************

  FUNCTION:     state_machine_send_command_mail

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void state_machine_send_command_message(osMessageQueueId_t message_queue,
                                                             const void * const p_mail)
{
    state_machine_send_command_message_body(message_queue, p_mail);
}

/******************************************************************************

  FUNCTION:     state_machine_send_command_message_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void state_machine_send_command_message_body(osMessageQueueId_t message_queue,
                                             const void * const p_mail)
{
    osStatus_t os_status;

    os_status = osMessageQueuePut(message_queue, p_mail, 0, 0);
    ASSERT(os_status == osOK);
}

/******************************************************************************

  FUNCTION:     state_machine_respond_to_client_with_signal

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void state_machine_respond_to_client_with_signal(osThreadId_t thread_id, int32_t * p_signals)
{
    state_machine_respond_to_client_with_signal_body(thread_id, p_signals);
}

/******************************************************************************

  FUNCTION:     state_machine_respond_to_client_with_signal_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void state_machine_respond_to_client_with_signal_body(osThreadId_t thread_id, int32_t * p_signals)
{
    if ((*p_signals != NO_RESPONSE_SIGNAL) &&
        (thread_id != NULL))
    {
        osEventFlagsSet(thread_id, *p_signals);
        *p_signals = NO_RESPONSE_SIGNAL;
    }
}

/******************************************************************************

  FUNCTION:     state_machine_respond_to_client_with_message

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
__attribute__((weak)) void state_machine_respond_to_client_with_message(osMessageQueueId_t message_queue_id, uint32_t message)
{
    state_machine_respond_to_client_with_message_body(message_queue_id, message);
}

/******************************************************************************

  FUNCTION:     state_machine_respond_to_client_with_message_body

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void state_machine_respond_to_client_with_message_body(osMessageQueueId_t message_queue_id, uint32_t message)
{
    osStatus_t os_status;

    if (message_queue_id != NO_RESPONSE_MESSAGE)
    {
        os_status = osMessageQueuePut(message_queue_id, (void *) message, 0, 0);
        ASSERT(os_status == osOK);

        message_queue_id = NO_RESPONSE_MESSAGE;
    }
}

/******************************************************************************

  FUNCTION:     state_machine

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance
                initial_state - starting state
                p_func - pointer to event pending function
                instance_id - id for this instance used for tracing
                trace_id - 3 character string to identify trace record type

  RETURNS:      void

  DESCRIPTION:  constructor

******************************************************************************/
void state_machine(state_machine_t * me,
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

  FUNCTION:     state_machine_

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:  deconstructor

******************************************************************************/
void state_machine_(state_machine_t * me)
{
//    if (me->p_trace_template != NULL)
//    {
//        free(me->p_trace_template);
//        me->p_trace_template = NULL;
//    }

    me->p_state_jump_table = NULL;
}

/******************************************************************************

  FUNCTION:     state_machine_get_event

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      event

  DESCRIPTION:  getter for event attribute

******************************************************************************/
uint32_t state_machine_get_event(state_machine_t * me)
{
    return me->event;
} /*lint !e818*/

/******************************************************************************

  FUNCTION:     state_machine_set_pending_event

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance
                pending - event to pend on

  RETURNS:      void

  DESCRIPTION:  setter for pending attribute

******************************************************************************/
void state_machine_set_pending_event(state_machine_t * me, unsigned int pending)
{
    me->pending = pending;
}

/******************************************************************************

  FUNCTION:     state_machine_change_state

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance
                state - state to change to

  RETURNS:      void

  DESCRIPTION:  triggers a state change

******************************************************************************/
void state_machine_change_state(state_machine_t * me, unsigned int state)
{
    me->next_state = state;
    me->b_change_state = true;
}

/******************************************************************************

  FUNCTION:     state_machine_set_delay

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance
                delay - delay variable

  RETURNS:      void

  DESCRIPTION:  set the delay variable

******************************************************************************/
void state_machine_set_delay(state_machine_t * me, uint32_t delay)
{
    me->delay = delay;
}

/******************************************************************************

  FUNCTION:     state_machine_set_os_pend_object

  SCOPE:        private

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_set_os_pend_object(state_machine_t * me, void * p)
{
    me->os_pend_object.p = p;
}

/******************************************************************************

  FUNCTION:     state_machine_set_os_event_data_dst

  SCOPE:        private

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
void state_machine_set_os_event_data_dst(p_state_machine_t me, void * p_os_event_data_dst)
{
    me->p_os_event_data_dst = p_os_event_data_dst;
}

/******************************************************************************

  FUNCTION:     state_machine_disable_tracing

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_disable_tracing(state_machine_t * me)
{
    me->b_trace_enabled = false;
}

/******************************************************************************

  FUNCTION:     state_machine_enable_tracing

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_enable_tracing(state_machine_t * me)
{
    me->b_trace_enabled = true;
}

/******************************************************************************

  FUNCTION:     state_machine_set_halt_event

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_set_halt_event(state_machine_t * me)
{
    me->b_halt_event = true;
}

/******************************************************************************

  FUNCTION:     state_machine_clr_halt_event

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_clr_halt_event(state_machine_t * me)
{
    me->b_halt_event = false;
    me->b_halt_event_polling = false;
}

/******************************************************************************

  FUNCTION:     state_machine_enable_halt_event_polling

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void state_machine_enable_halt_event_polling(state_machine_t * me)
{
    me->b_halt_event_polling = true;
}

/******************************************************************************

  FUNCTION:     state_machine_run

  SCOPE:        public

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:  executes state jump table

******************************************************************************/
void state_machine_run(p_state_machine_t me)
{
    /* Verify me pointer and then index into our jump table is valid */
    if ((me == NULL) || (me->state >= me->n_states))
    {
        ASSERT(false);
    }
    else
    {
        /* Update our event variable */
        state_machine_trigger_event((p_state_machine_t) me);
        /* Call the appropriate state function */
        me->p_state_jump_table[me->state](me);
    }
}

/******************************************************************************

  FUNCTION:     state_machine_trigger_event

  SCOPE:        private

  PARAMETERS:   me - pointer to state_machine instance

  RETURNS:      void

  DESCRIPTION:  handles the sequencing of events

******************************************************************************/
void state_machine_trigger_event(state_machine_t * me)
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
                (me->delay != 0) &&
                (me->pending != NO_OS_EVENT))
            {
                me->event = state_machine_pend_on_event_and_poll_for_halt_event(me);
            }
            else
            {
                me->event = state_machine_pend_on_event(me);
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

  FUNCTION:     state_machine_pend_on_event_and_poll_for_halt_event

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
unsigned int state_machine_pend_on_event_and_poll_for_halt_event(state_machine_t * me)
{
    unsigned int event;

    me->delay_counter = me->delay;
    me->delay = HALT_EVENT_POLLING_PERIOD;

    do
    {
        if (me->delay_counter < HALT_EVENT_POLLING_PERIOD)
        {
            /* remaining delay is less than HALT_EVENT_POLLING_PERIOD,
             * so use the remaining delay value for the last delay */
            me->delay = me->delay_counter;
        }

        event = state_machine_pend_on_event(me);

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

  FUNCTION:     state_machine_pend_on_event

  SCOPE:

  PARAMETERS:

  RETURNS:

  DESCRIPTION:

******************************************************************************/
unsigned int state_machine_pend_on_event(state_machine_t * me)
{
    osStatus_t os_status;
    unsigned int event;

    switch (me->pending)
    {
        case NO_OS_EVENT:
        {
            event = NO_OS_EVENT;
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
            os_status = osMutexAcquire(me->os_pend_object.mutex, me->delay);

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
                ASSERT(false); /* bad status */
            }

            break;
        }

        case SIGNAL_RECEIVED_EVENT:
        {
            uint32_t return_value;

            return_value = osThreadFlagsWait(me->os_pend_object.signal_mask, osFlagsWaitAny, me->delay);

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
                    event = NO_OS_EVENT;
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
            os_status = osMessageQueueGet(me->os_pend_object.message_queue, (uint8_t *) me->p_os_event_data_dst, 0, me->delay);

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
                event = NO_OS_EVENT;
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

