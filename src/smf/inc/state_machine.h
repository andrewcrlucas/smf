/*
 * state_machine.h
 */

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os2.h"

/*****************************************************************************
 * MACROS                                                                    *
 *****************************************************************************/
#define STATE_MACHINE_CONSTRUCTOR(a, b, c, d) (state_machine((p_state_machine_t)me, &g_state_jump_table[0], (a), (b), (c), (d)))
#define STATE_MACHINE_DECONSTRUCTOR() (state_machine_((p_state_machine_t)me))
#define STATE_MACHINE_GET_EVENT(module_name) (module_name##_get_event(me, state_machine_get_event((p_state_machine_t) me)))

#define PEND_ON(a, b)                                           \
    state_machine_set_pending_event((p_state_machine_t) me, a); \
    state_machine_set_delay((p_state_machine_t) me, b)

#define PEND_ON_NO_OS_EVENT() \
    state_machine_set_pending_event((p_state_machine_t) me, NO_OS_EVENT);

#define PEND_ON_DELAY(timeout)                                              \
    state_machine_set_pending_event((p_state_machine_t) me, TIMEOUT_EVENT); \
    state_machine_set_delay((p_state_machine_t) me, timeout);

#define PEND_ON_DELAY_OR_HALT(timeout) \
    PEND_ON_DELAY(timeout)             \
    state_machine_enable_halt_event_polling((p_state_machine_t) me);

#define PEND_ON_SIGNAL(mask,p_signal_dst,timeout)                                   \
    ASSERT(p_signal_dst != NULL);                                                   \
    state_machine_set_pending_event((p_state_machine_t) me, SIGNAL_RECEIVED_EVENT); \
    state_machine_set_delay((p_state_machine_t) me, timeout);                       \
    state_machine_set_os_event_data_dst((p_state_machine_t) me, p_signal_dst);      \
    state_machine_set_os_pend_object((p_state_machine_t) me, (void *) (mask));

#define PEND_ON_SIGNAL_OR_HALT(mask,p_signal_dst,timeout) \
    PEND_ON_SIGNAL(mask,p_signal_dst,timeout)             \
    state_machine_enable_halt_event_polling((p_state_machine_t) me);

#define PEND_ON_MESSAGE(p_message_queue,p_message_dst,timeout)                       \
    ASSERT(p_message_queue != NULL);                                                 \
    ASSERT(p_message_dst != NULL);                                                   \
    state_machine_set_pending_event((p_state_machine_t) me, MESSAGE_RECEIVED_EVENT); \
    state_machine_set_delay((p_state_machine_t) me, timeout);                        \
    state_machine_set_os_pend_object((p_state_machine_t) me, p_message_queue);       \
    state_machine_set_os_event_data_dst((p_state_machine_t) me, p_message_dst);

#define PEND_ON_MESSAGE_OR_HALT(p_message_queue,p_message_dst,timeout) \
    PEND_ON_MESSAGE(p_message_queue,p_message_dst,timeout)             \
    state_machine_enable_halt_event_polling((p_state_machine_t) me);

#define PEND_ON_MUTEX(mutex,timeout)                                               \
    ASSERT(mutex != NULL);                                                         \
    state_machine_set_pending_event((p_state_machine_t) me, MUTEX_ACQUIRED_EVENT); \
    state_machine_set_delay((p_state_machine_t) me, timeout);                      \
    state_machine_set_os_pend_object((p_state_machine_t) me, mutex);

#define PEND_AGAIN()
#define CHANGE_STATE(a) (state_machine_change_state((p_state_machine_t) me, a))
#define SET_SIGNAL_MASK(a) (state_machine_set_os_pend_object((p_state_machine_t) me, (void *) (a)))
#define RUN_STATE_MACHINE() state_machine_run((p_state_machine_t) me)
#define DISABLE_TRACING() state_machine_disable_tracing((p_state_machine_t) me)
#define ENABLE_TRACING() state_machine_enable_tracing((p_state_machine_t) me)
#define SET_HALT_EVENT(me) state_machine_set_halt_event((p_state_machine_t) me)
#define CLR_HALT_EVENT(me) state_machine_clr_halt_event((p_state_machine_t) me)
#define STATE_MACHINE_RESPOND_TO_CLIENT_WITH_SIGNAL(thread_id, p_signals) state_machine_respond_to_client_with_signal((thread_id), (p_signals))
#define STATE_MACHINE_RESPOND_TO_CLIENT_WITH_MESSAGE(p_message_queue, message) state_machine_respond_to_client_with_message((p_message_queue), (message))
#define STATE_MACHINE_SEND_COMMAND_MESSAGE(p_message_queue, p_temp_mail) (state_machine_send_command_message(p_message_queue, p_temp_mail))
#define STATE_MACHINE_RELEASE_MUTEX(mutex) state_machine_release_mutex((mutex));

#define EXPAND_AS_STATE_ENUM(a,b) a##_STATE,
#define EXPAND_AS_STATE_MACHINE_PROTOTYPES(a,b) static void b##_state(void *);

#define STATE_MACHINE_JUMP_TABLE_DECLARATION static void (*const g_state_jump_table[]) (void *) =

#define EXPAND_AS_STATE_MACHINE_JUMP_TABLE_ENTRIES(a,b) b##_state,
#define STATE_MACHINE_CREATE_JUMP_TABLE(STATE_TABLE)            \
    static void (*const g_state_jump_table[]) (void *) =        \
    {                                                           \
        STATE_TABLE(EXPAND_AS_STATE_MACHINE_JUMP_TABLE_ENTRIES) \
    };

#define HALT_EVENT_POLLING_PERIOD (5)

#define ANY_SIGNAL          (0)

#define NO_RESPONSE_SIGNAL  (0)
#define NO_RESPONSE_MESSAGE (NULL)

#define STATE_MACHINE_IS_SIGNAL_SET(signal, requested_signal_mask) state_machine_is_signal_set(signal, requested_signal_mask)

/*****************************************************************************
 * User Defined Datatypes                                                    *
 *****************************************************************************/
typedef struct state_machine * p_state_machine_t;

enum
{
    ENTRY_EVENT,
    EXIT_EVENT,
    ASSERT_EVENT,
    TIMEOUT_EVENT,
    SIGNAL_RECEIVED_EVENT,
    MESSAGE_RECEIVED_EVENT,
    MUTEX_ACQUIRED_EVENT,
    NO_OS_EVENT,
    SIGNAL_NOT_RECEIVED_EVENT,
    MESSAGE_NOT_RECEIVED_EVENT,
    HALT_EVENT,
    USER_EVENT
};

typedef uint32_t (* p_pend_on_event_func_t)(p_state_machine_t);

/* state function prototype */
#define JUMP_TABLE_DECLARATION(a,b) static void (*const g_state_jump_table[b]) (a) =

/*****************************************************************************
 * Object initialization and creation functions                              *
 *****************************************************************************/
/* Constructor */
extern void state_machine(p_state_machine_t,
                          void (*const *) (void *),
                          unsigned int,
                          const char *,
                          unsigned int,
                          unsigned int);

/* Deconstructor */
extern void state_machine_(p_state_machine_t);

/*****************************************************************************
 * Methods (use the macros to call these)                                    *
 *****************************************************************************/
extern uint32_t state_machine_get_event(p_state_machine_t);
extern void state_machine_set_pending_event(p_state_machine_t, unsigned int);
extern void state_machine_change_state(p_state_machine_t, unsigned int);
extern void state_machine_set_delay(p_state_machine_t, uint32_t);
extern void state_machine_set_os_pend_object(p_state_machine_t, void *);
extern void state_machine_set_os_event_data_dst(p_state_machine_t, void *);
extern void state_machine_disable_tracing(p_state_machine_t);
extern void state_machine_enable_tracing(p_state_machine_t);
extern void state_machine_run(p_state_machine_t);
extern void state_machine_run_new(p_state_machine_t);
extern void state_machine_set_halt_event(p_state_machine_t);
extern void state_machine_clr_halt_event(p_state_machine_t);
extern void state_machine_enable_halt_event_polling(p_state_machine_t);
extern void state_machine_respond_to_client_with_signal(osThreadId_t, int32_t *);
extern void state_machine_respond_to_client_with_message(osMessageQueueId_t, uint32_t);
extern void state_machine_send_command_message(osMessageQueueId_t, const void * const);
extern void state_machine_release_mutex(osMutexId_t);

/*****************************************************************************
 * Inline Public Functions                                                   *
 *****************************************************************************/
/* NOTE: use STATE_MACHINE_IS_SIGNAL_SET macro to call state_machine_is_signal_set for consistency */
inline static bool state_machine_is_signal_set(int32_t signal, int32_t requested_signal_mask)
{
    return ((signal & requested_signal_mask) == requested_signal_mask);
}

#endif
