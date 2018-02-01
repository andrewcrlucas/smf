/*
 * smf.h
 */

#ifndef SMF_H
#define SMF_H

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "cmsis_os2.h"

/*****************************************************************************
 * Initializer macros                                                        *
 *****************************************************************************/
#define SMF_CONSTRUCTOR(_initial_state, _trace_id, _index, _n_states)         \
    (smf((p_smf_t) me,                                                        \
         &g_smf_jump_table[0],                                                \
         _initial_state,                                                      \
         _trace_id,                                                           \
         _index,                                                              \
         _n_states))

#define SMF_DECONSTRUCTOR() (smf_((p_smf_t) me))

/*****************************************************************************
 * Macros used for pending on events                                         *
 *****************************************************************************/
#define SMF_PEND_AGAIN()

#define SMF_PEND_ON_NO_EVENT()                                                \
    smf_set_pending_event((p_smf_t) me, NO_EVENT);

#define SMF_PEND_ON_DELAY(timeout)                                            \
    smf_set_pending_event((p_smf_t) me, TIMEOUT_EVENT);                       \
    smf_set_delay((p_smf_t) me, timeout);

#define SMF_PEND_ON_DELAY_OR_HALT(timeout)                                    \
    SMF_PEND_ON_DELAY(timeout)                                                \
    smf_enable_halt_event_polling((p_smf_t) me);

#define SMF_PEND_ON_MUTEX(mutex,timeout)                                      \
    ASSERT(mutex != NULL);                                                    \
    smf_set_pending_event((p_smf_t) me, MUTEX_ACQUIRED_EVENT);                \
    smf_set_delay((p_smf_t) me, timeout);                                     \
    smf_set_os_pend_object((p_smf_t) me, mutex);

#define SMF_PEND_ON_MUTEX_OR_HALT(mutex,timeout)                              \
		SMF_PEND_ON_MUTEX(mutex, timeout)                                     \
        smf_enable_halt_event_polling((p_smf_t) me);

#define SMF_PEND_ON_SEMAPHORE(semaphore,timeout)                              \
    ASSERT(semaphore != NULL);                                                \
    smf_set_pending_event((p_smf_t) me, SEMAPHORE_ACQUIRED_EVENT);            \
    smf_set_delay((p_smf_t) me, timeout);                                     \
    smf_set_os_pend_object((p_smf_t) me, semaphore);

#define SMF_PEND_ON_SEMAPHORE_OR_HALT(semaphore,timeout)                      \
		SMF_PEND_ON_SEMAPHORE(semaphore, timeout)                             \
        smf_enable_halt_event_polling((p_smf_t) me);

#define SMF_PEND_ON_SIGNAL(mask,p_signal_dst,timeout)                         \
    ASSERT(p_signal_dst != NULL);                                             \
    smf_set_pending_event((p_smf_t) me, SIGNAL_RECEIVED_EVENT);               \
    smf_set_delay((p_smf_t) me, timeout);                                     \
    smf_set_os_event_data_dst((p_smf_t) me, p_signal_dst);                    \
    smf_set_os_pend_object((p_smf_t) me, (void *) (mask));

#define SMF_PEND_ON_SIGNAL_OR_HALT(mask,p_signal_dst,timeout)                 \
    SMF_PEND_ON_SIGNAL(mask,p_signal_dst,timeout)                             \
    smf_enable_halt_event_polling((p_smf_t) me);

#define SMF_PEND_ON_FLAG(mask,p_flag_dst,timeout)                             \
    ASSERT(p_flag_dst != NULL);                                               \
    smf_set_pending_event((p_smf_t) me, FLAG_RECEIVED_EVENT);                 \
    smf_set_delay((p_smf_t) me, timeout);                                     \
    smf_set_os_event_data_dst((p_smf_t) me, p_flag_dst);                      \
    smf_set_os_pend_object((p_smf_t) me, (void *) (mask));

#define SMF_PEND_ON_FLAG_OR_HALT(mask,p_flag_dst,timeout)                     \
    SMF_PEND_ON_SIGNAL(mask,p_flag_dst,timeout)                               \
    smf_enable_halt_event_polling((p_smf_t) me);

#define SMF_PEND_ON_MESSAGE(p_message_queue,p_message_dst,timeout)            \
    ASSERT(p_message_queue != NULL);                                          \
    ASSERT(p_message_dst != NULL);                                            \
    smf_set_pending_event((p_smf_t) me, MESSAGE_RECEIVED_EVENT);              \
    smf_set_delay((p_smf_t) me, timeout);                                     \
    smf_set_os_pend_object((p_smf_t) me, p_message_queue);                    \
    smf_set_os_event_data_dst((p_smf_t) me, p_message_dst);

#define SMF_PEND_ON_MESSAGE_OR_HALT(p_message_queue,p_message_dst,timeout)    \
    SMF_PEND_ON_MESSAGE(p_message_queue,p_message_dst,timeout)                \
    smf_enable_halt_event_polling((p_smf_t) me);

/*****************************************************************************
 * General Macros                                                            *
 *****************************************************************************/
#define SMF_MY_EVENT (smf_get_event((p_smf_t) me))
#define SMF_CHANGE_STATE(a) (smf_change_state((p_smf_t) me, a))
#define SMF_RUN() smf_run((p_smf_t) me)
#define SMF_ENABLE_TRACING() smf_enable_tracing((p_smf_t) me)
#define SMF_DISABLE_TRACING() smf_disable_tracing((p_smf_t) me)
#define SMF_SET_HALT_EVENT(me) smf_set_halt_event((p_smf_t) me)
#define SMF_CLR_HALT_EVENT(me) smf_clr_halt_event((p_smf_t) me)

#define SMF_RESPOND_WITH_SIGNAL(thread_id, p_signals)                         \
    smf_respond_to_client_with_signal((thread_id), (p_signals))

#define SMF_RESPOND_WITH_MESSAGE(p_message_queue, message)                    \
    smf_respond_to_client_with_message((p_message_queue), (message))

#define SMF_RELEASE_MUTEX(mutex) smf_release_mutex((mutex));
#define SMF_RELEASE_SEMAPHORE(semaphore) smf_release_mutex((semaphore));

#define SMF_EXPAND_AS_STATE_ENUM(a,b) a##_STATE,
#define SMF_EXPAND_AS_PROTOTYPES(a,b) static void b##_state(void *);

#define SMF_JUMP_TABLE_DECLARATION static void (*const g_smf_jump_table[]) (void *) =

#define SMF_EXPAND_AS_JUMP_TABLE_ENTRIES(a,b) b##_state,
#define SMF_CREATE_JUMP_TABLE(STATE_TABLE)                                    \
    static void (*const g_smf_jump_table[]) (void *) =                        \
    {                                                                         \
        STATE_TABLE(SMF_EXPAND_AS_JUMP_TABLE_ENTRIES)                         \
    };

#define SMF_HALT_EVENT_POLLING_PERIOD (5)

#define SMF_ANY_SIGNAL          (0)

#define SMF_NO_RESPONSE_SIGNAL  (0)
#define SMF_NO_RESPONSE_MESSAGE (NULL)

#define SMF_SMF_IS_SIGNAL_SET(_signal, _mask) smf_is_signal_set(_signal, _mask)

/*****************************************************************************
 * User Defined Datatypes                                                    *
 *****************************************************************************/
typedef struct smf * p_smf_t;

enum
{
    NO_EVENT,
    ENTRY_EVENT,
    EXIT_EVENT,
    ASSERT_EVENT,
    TIMEOUT_EVENT,
    MUTEX_ACQUIRED_EVENT,
    SEMAPHORE_ACQUIRED_EVENT,
    SIGNAL_RECEIVED_EVENT,
    SIGNAL_NOT_RECEIVED_EVENT,
    FLAG_RECEIVED_EVENT,
    FLAG_NOT_RECEIVED_EVENT,
    MESSAGE_RECEIVED_EVENT,
    MESSAGE_NOT_RECEIVED_EVENT,
    HALT_EVENT
};

typedef uint32_t (* p_pend_on_event_func_t)(p_smf_t);

/* state function prototype */
#define JUMP_TABLE_DECLARATION(a,b) static void (*const g_state_jump_table[b]) (a) =

/*****************************************************************************
 * Object initialization and creation functions                              *
 *****************************************************************************/
/* Constructor */
extern void smf(p_smf_t,
                void (*const *) (void *),
                unsigned int,
                const char *,
                unsigned int,
                unsigned int);

/* Deconstructor */
extern void smf_(p_smf_t);

/*****************************************************************************
 * Methods (use the macros to call these)                                    *
 *****************************************************************************/
extern uint32_t smf_get_event(p_smf_t);
extern void smf_set_pending_event(p_smf_t, unsigned int);
extern void smf_change_state(p_smf_t, unsigned int);
extern void smf_set_delay(p_smf_t, uint32_t);
extern void smf_set_os_pend_object(p_smf_t, void *);
extern void smf_set_os_event_data_dst(p_smf_t, void *);
extern void smf_disable_tracing(p_smf_t);
extern void smf_enable_tracing(p_smf_t);
extern void smf_run(p_smf_t);
extern void smf_run_new(p_smf_t);
extern void smf_set_halt_event(p_smf_t);
extern void smf_clr_halt_event(p_smf_t);
extern void smf_enable_halt_event_polling(p_smf_t);
extern void smf_respond_to_client_with_signal(osThreadId_t, int32_t *);
extern void smf_respond_to_client_with_message(osMessageQueueId_t, uint32_t);
extern void smf_send_command_message(osMessageQueueId_t, const void * const);
extern void smf_release_mutex(osMutexId_t);

/*****************************************************************************
 * Inline Public Functions                                                   *
 *****************************************************************************/
/* NOTE: use SMF_IS_SIGNAL_SET macro to call smf_is_signal_set for consistency */
inline static bool smf_is_signal_set(int32_t signal, int32_t requested_signal_mask)
{
    return ((signal & requested_signal_mask) == requested_signal_mask);
}

#endif
