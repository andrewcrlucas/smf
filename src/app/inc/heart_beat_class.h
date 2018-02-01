/*
 * heart_beat_class.h
 */

#ifndef HEART_BEAT_CLASS_H_
#define HEART_BEAT_CLASS_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
//#include "digital_output.h"
#include "smf.h"
#include "smf_class.h"

/*****************************************************************************
 * Defined and Enumerated Constants                                          *
 *****************************************************************************/
#define HEART_BEAT_STATE_TABLE(ENTRY)                                         \
    ENTRY(HEART_CHECK_RESET_SOURCE,     heart_check_reset_source)             \
    ENTRY(HEART_BEAT_FAST,              heart_beat_fast)                      \
    ENTRY(HEART_BEAT_SLOW,              heart_beat_slow)

/* State enumeration */
typedef enum
{
    HEART_BEAT_STATE_TABLE(SMF_EXPAND_AS_STATE_ENUM)
    N_HEART_BEAT_STATES
} heart_beat_state_t;

/*****************************************************************************
 * User Defined Datatypes                                                    *
 *****************************************************************************/
typedef struct
{
    smf_t super;
    osThreadId_t thread_id;
    //digital_output_index_t digital_output;
    //p_trace_template_t p_trace_template_reset_source;
    uint32_t volatile const * p_reset_source_register;
    uint8_t reset_source;
} heart_beat_t;

/*****************************************************************************
 * Class Prototypes                                                          *
 *****************************************************************************/
extern heart_beat_t * heart_beat_init(unsigned int);
extern void heart_beat_deinit(heart_beat_index_t);
extern uint32_t heart_beat_get_event(heart_beat_t *, uint32_t);
extern void heart_beat(heart_beat_t *, unsigned int);

#endif /* HEART_BEAT_CLASS_H_ */
