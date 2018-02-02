/*************************************************************************//**

  @file smf_class.c
  @brief Private class definition file for the smf object

******************************************************************************/
#ifndef SMF_CLASS_H
#define SMF_CLASS_H

/*****************************************************************************
  User defined datatypes
 *****************************************************************************/
typedef union
{
    int32_t mask;
    osMutexId_t mutex_id;
    osSemaphoreId_t semaphore_id;
    osEventFlagsId_t event_flags_id;
    osMessageQueueId_t message_queue_id;
    void * p;
} os_pend_object_t;

typedef struct smf
{
    unsigned int state;
    unsigned int next_state;
    unsigned int n_states;
    unsigned int event;
    unsigned int pending;
    void (*const * p_state_jump_table) (void *);
    bool b_change_state;
//    p_trace_template_t p_trace_template;
    unsigned int index;
    uint32_t delay;
    uint32_t delay_counter;
    os_pend_object_t os_pend_object;
    void * p_os_event_data_dst;
    bool b_trace_enabled;
} smf_t;

/*****************************************************************************
  Public prototypes
 *****************************************************************************/
extern unsigned int smf_pend_on_event(smf_t *);
extern void smf_trigger_event(p_smf_t);
extern void smf_respond_to_client_with_signal_body(osThreadId_t, int32_t *);
extern void smf_respond_to_client_with_message_body(osMessageQueueId_t, uint32_t);
extern void smf_send_command_message_body(osMessageQueueId_t, const void * const);
extern void smf_release_mutex_body(osMutexId_t);

#endif
