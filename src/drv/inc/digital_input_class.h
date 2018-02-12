/**************************************************************************//**

  @file digital_input_class.h
  @brief Private class definition file for the digital_input object

******************************************************************************/
#ifndef DIGITAL_INPUT_CLASS_H
#define DIGITAL_INPUT_CLASS_H

/******************************************************************************
  Includes
******************************************************************************/
/* smf */
#include "smf.h"
#include "smf_class.h"
/* hal */
#include "stm32f7xx_hal.h"
/* drv */
#include "notification_queue.h"

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
#define DIGITAL_INPUT_STATE_TABLE(ENTRY)                                \
    ENTRY(DIGITAL_INPUT_INITIAL,                 digital_input_initial) \
    ENTRY(DIGITAL_INPUT_LOW,                     digital_input_low)     \
    ENTRY(DIGITAL_INPUT_HIGH,                    digital_input_high)    \
    ENTRY(DIGITAL_INPUT_SCANNING_DISABLED,       digital_input_scanning_disabled)

enum
{
    DISABLE_SCANNING_EVENT = USER_EVENT,
    ENABLE_SCANNING_EVENT
};

/* signals */
#define STATE_MACHINE_1_SIG     (SIG0)
#define STATE_MACHINE_2_SIG     (SIG1)
#define STATE_MACHINE_3_SIG     (SIG2)

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
typedef enum
{
    DIGITAL_INPUT_STATE_TABLE(SMF_EXPAND_AS_STATE_ENUM)
    N_DIGITAL_INPUT_STATES
} digital_input_state_t;

typedef enum
{
    DIGITAL_INPUT_DISABLE_SCANNING_CMD,
    DIGITAL_INPUT_ENABLE_SCANNING_CMD,
    N_DIGITAL_INPUT_CMDS
} digital_input_command_t;

typedef struct
{
    digital_input_command_t command;
} digital_input_message_t;

typedef struct
{
    smf_t super;
    osThreadId_t thread_id;
    osMessageQueueId_t message_queue_id;
    digital_input_message_t message;
    digital_input_value_t initial_state;
    uint32_t polling_period;
    uint32_t debounce_counter;
    uint32_t high_debounce_count;
    uint32_t low_debounce_count;
    GPIO_TypeDef * port;
    uint16_t pin;
    p_notification_queue_t p_notification_queue;
} digital_input_t;

/******************************************************************************
  Class Prototypes
******************************************************************************/
extern digital_input_t * digital_input_init(unsigned int);
extern void digital_input_deinit(digital_input_index_t);
extern uint32_t digital_input_get_event(digital_input_t const *, uint32_t);
extern void digital_input(digital_input_t *, unsigned int);

extern void digital_input_subscribe_body(digital_input_index_t, digital_input_value_t, int32_t);
extern void digital_input_unsubscribe_body(digital_input_index_t, int32_t);
extern digital_input_value_t digital_input_read_body(digital_input_index_t);
extern void digital_input_disable_scanning_body(digital_input_index_t);
extern void digital_input_enable_scanning_body(digital_input_index_t);
extern void digital_input_disable_tracing_body(digital_input_index_t);
extern void digital_input_constructor_disable_scanning(digital_input_index_t, bool);

#endif
