/**************************************************************************//**

  @file digital_output_class.h
  @brief Private class definition file for the digital_output object

******************************************************************************/
#ifndef DIGITAL_OUTPUT_CLASS_H
#define DIGITAL_OUTPUT_CLASS_H

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
typedef struct
{
    GPIO_TypeDef* group;
    uint16_t pin;
    bool b_trace_enabled;
} digital_output_gpio_t;

typedef struct digital_output
{
    digital_output_gpio_t digital_output_gpio[N_DIGITAL_OUTPUTS];

    /* for trace */
    digital_output_index_t digital_output_index;
    digital_output_state_t digital_output_state;
//    p_trace_template_t p_template;
} digital_output_t;

/******************************************************************************
  Class Prototypes
******************************************************************************/
extern void digital_output_deinit(digital_output_index_t);
extern void digital_output_set_body(digital_output_index_t,
                                    digital_output_state_t);
extern void digital_output_toggle_body(digital_output_index_t);

#endif
