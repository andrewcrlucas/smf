/**************************************************************************//**

  @file digital_input.h
  @brief Public API definition file for the digital_input object

******************************************************************************/
#ifndef DIGITAL_INPUT_H
#define DIGITAL_INPUT_H

/******************************************************************************
  Includes
******************************************************************************/
/* std c library */
#include <stdint.h>

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
#define DIGITAL_INPUT_STACK_SIZE (0)

/* ------ SIGNAL -------- INITIAL ---- T_POLL - N_DB - N_DB - GROUP - GPIO_PIN --- SCANNING
           NAME           STATE        HIGH     LOW                                DISABLED   */
#define DIGITAL_INPUT_TABLE(ENTRY) \
    ENTRY(SELECT_SWITCH,  SWITCH_OPEN, 10,      3,     3,     GPIOC,  GPIO_PIN_13, false)

#define EXPAND_AS_DIGITAL_INPUT_INDEX_ENUM(_index, _initial_state, _polling_period, _high_debounce_count, _low_debounce_count, _port, _pin, _b_scanning_disable) _index,

/******************************************************************************
  Public Defined Datatypes
******************************************************************************/
typedef enum
{
    DIGITAL_INPUT_TABLE(EXPAND_AS_DIGITAL_INPUT_INDEX_ENUM)
    N_DIGITAL_INPUTS,
} digital_input_index_t;

/* TODO - update enumeration as per project */
typedef enum
{
    /* Reference enum values only do not use directly */
    INPUT_LOW = 0,
    INPUT_HIGH = 1,
    INPUT_FALLING_EDGE = 2,
    INPUT_RISING_EDGE = 3,

    /* Switch Derived enum values */
    SWITCH_OPEN = INPUT_HIGH,
    SWITCH_CLOSED = INPUT_LOW,
    SWITCH_GOING_OPEN = INPUT_RISING_EDGE,
    SWITCH_GOING_CLOSED = INPUT_FALLING_EDGE,
} digital_input_value_t;

/******************************************************************************
  Public Prototypes
******************************************************************************/
extern void digital_input_start(void);
extern void digital_input_subscribe(digital_input_index_t, digital_input_value_t, int32_t);
extern void digital_input_unsubscribe(digital_input_index_t, int32_t);
extern digital_input_value_t digital_input_read(digital_input_index_t);
extern void digital_input_disable_tracing(digital_input_index_t);
extern void digital_input_disable_scanning(digital_input_index_t);
extern void digital_input_enable_scanning(digital_input_index_t);

#endif
