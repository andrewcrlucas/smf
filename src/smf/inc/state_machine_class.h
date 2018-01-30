/*
 * state_machine_class.c
 */

#ifndef STATE_MACHINE_CLASS_H
#define STATE_MACHINE_CLASS_H

/*****************************************************************************
 * User Defined Datatypes                                                    *
 *****************************************************************************/
typedef union
{
    int32_t signal_mask;
    osMessageQueueId_t message_queue;
    osMutexId_t mutex;
    void * p;
} os_pend_object_t;

typedef struct state_machine
{
    unsigned int state;
    unsigned int next_state;
    unsigned int n_states;
    unsigned int event;
    unsigned int pending;
    void (*const * p_state_jump_table) (void *);
    p_pend_on_event_func_t p_pend_on_event_func;
    bool b_change_state;
//    p_trace_template_t p_trace_template;
    unsigned int index;
    uint32_t delay;
    uint32_t delay_counter;
    os_pend_object_t os_pend_object;
    void * p_os_event_data_dst;
    bool b_trace_enabled;
    volatile bool b_halt_event;
    bool b_halt_event_polling;
} state_machine_t;

#endif

extern unsigned int state_machine_pend_on_event(state_machine_t *);
extern unsigned int state_machine_pend_on_event_and_poll_for_halt_event(state_machine_t *);
extern void state_machine_trigger_event(p_state_machine_t);
extern void state_machine_respond_to_client_with_signal_body(osThreadId_t, int32_t *);
extern void state_machine_respond_to_client_with_message_body(osMessageQueueId_t, uint32_t);
extern void state_machine_send_command_message_body(osMessageQueueId_t, const void * const);
extern void state_machine_release_mutex_body(osMutexId_t);
