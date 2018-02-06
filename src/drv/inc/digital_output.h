/**************************************************************************//**

  @file digital_output.h
  @brief Public API definition file for the digital_output object

******************************************************************************/
#ifndef DIGITAL_OUTPUT_H
#define DIGITAL_OUTPUT_H

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
/* ----------- INSTANCE_NAME ---------- GROUP ------ GPIO_PIN ---- DEFAULT_STATE - FREQ - PULL ---- TRACE_ENABLED ----- */
#define DIGITAL_OUTPUT_TABLE(ENTRY)                                                                        \
    ENTRY(HEARTBEAT_LED,                GPIOI,       GPIO_PIN_1,   LED_OFF,        LOW,   PULLUP,   false) \

#define EXPAND_AS_DIGITAL_OUTPUT_ENUM(id, group, pin, _default_state, _freq, _pull, b_trace_enabled) id,

/******************************************************************************
  Public Defined Datatypes
******************************************************************************/
typedef enum
{
    OUTPUT_LOW = 0,
    OUTPUT_HIGH = 1,

    LED_ON = OUTPUT_LOW,
    LED_OFF = OUTPUT_HIGH,

    CS_DISABLE = OUTPUT_HIGH,
    CS_ENABLE = OUTPUT_LOW,
} digital_output_state_t;

typedef enum
{
    DIGITAL_OUTPUT_TABLE(EXPAND_AS_DIGITAL_OUTPUT_ENUM)
    N_DIGITAL_OUTPUTS,
} digital_output_index_t;

typedef struct digital_output * p_digital_output_t;

/******************************************************************************
  Public Prototypes
******************************************************************************/
extern p_digital_output_t digital_output_init(void);

extern void digital_output_set(digital_output_index_t, digital_output_state_t);
extern void digital_output_toggle(digital_output_index_t);

#endif
