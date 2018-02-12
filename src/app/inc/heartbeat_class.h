/**************************************************************************//**

  @file heartbeat_class.c
  @brief Private class definition file for the heartbeat object

******************************************************************************/
#ifndef HEARTBEAT_CLASS_H_
#define HEARTBEAT_CLASS_H_

/******************************************************************************
  Includes
******************************************************************************/
#include "digital_output.h"
#include "smf.h"
#include "smf_class.h"

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
#define HEARTBEAT_STATE_TABLE(ENTRY)                                          \
    ENTRY(HEART_CHECK_RESET_SOURCE,     heart_check_reset_source)             \
    ENTRY(HEARTBEAT_FAST,              heartbeat_fast)                        \
    ENTRY(HEARTBEAT_SLOW,              heartbeat_slow)

/* State enumeration */
typedef enum
{
    HEARTBEAT_STATE_TABLE(SMF_EXPAND_AS_STATE_ENUM)
    N_HEARTBEAT_STATES
} heartbeat_state_t;

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
typedef struct
{
    smf_t super;
    osThreadId_t thread_id;
    digital_output_index_t digital_output;
    p_trace_template_t p_trace_template_reset_source;
    uint32_t volatile const * p_reset_source_register;
    uint8_t reset_source;
} heartbeat_t;

/******************************************************************************
  Class Prototypes
******************************************************************************/
extern heartbeat_t * heartbeat_init(unsigned int);
extern void heartbeat_deinit(heartbeat_index_t);
extern uint32_t heartbeat_get_event(heartbeat_t *, uint32_t);
extern void heartbeat(heartbeat_t *, unsigned int);

#endif /* HEARTBEAT_CLASS_H_ */
