/*************************************************************************//**

  @file digital_output.c
  @brief Implementation file for the digital_output object

******************************************************************************/

/*****************************************************************************
  Includes
 *****************************************************************************/
#include "stm32f7xx_hal.h"
#include <stdbool.h>
//#include "trace_template.h"

/* module header and class */
#include "digital_output.h"
#include "digital_output_class.h"

#include "gpio_init.h"

/*****************************************************************************
  Private Variables
 *****************************************************************************/

static digital_output_t g_digital_output;

/*****************************************************************************
  Public Functions
 *****************************************************************************/

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
__weak void digital_output_toggle(digital_output_index_t index)
{
    digital_output_toggle_body(index);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_output_toggle_body(digital_output_index_t index)
{
    digital_output_t * me = &g_digital_output;

    HAL_GPIO_TogglePin(me->digital_output_gpio[index].group, me->digital_output_gpio[index].pin);
}

/**************************************************************************//**

  @brief

  @param index
  @param state

  @return void

******************************************************************************/
__weak void digital_output_set(digital_output_index_t index, digital_output_state_t state)
{
    digital_output_set_body(index, state);
}

/**************************************************************************//**

  @brief

  @param index
  @param state

  @return void

******************************************************************************/
void digital_output_set_body(digital_output_index_t index, digital_output_state_t digital_output_state)
{
    digital_output_t * me = &g_digital_output;

    if (digital_output_state == OUTPUT_HIGH)
    {
        HAL_GPIO_WritePin(me->digital_output_gpio[index].group, me->digital_output_gpio[index].pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(me->digital_output_gpio[index].group, me->digital_output_gpio[index].pin, GPIO_PIN_RESET);
    }

    if (me->digital_output_gpio[index].b_trace_enabled == true)
    {
        /* trace digital output state */
        me->digital_output_index = index;
        me->digital_output_state = digital_output_state;
        //trace_template_capture(g_digital_output.p_template);
    }
}

/**************************************************************************//**

  @brief

  @param void

  @return instance pointer

******************************************************************************/
digital_output_t * digital_output_init(void)
{
#define EXPAND_AS_INIT(_id, _group, _pin, _default_state, _freq, _pull, _b_trace_enabled) \
    me->digital_output_gpio[_id].group = _group;                                          \
    me->digital_output_gpio[_id].pin = _pin;                                              \
    me->digital_output_gpio[_id].b_trace_enabled = _b_trace_enabled;                      \
                                                                                          \
    __HAL_RCC_##_group##_CLK_ENABLE();                                                    \
    digital_output_set(_id, _default_state);                                              \
    gpio_init_output(_group, _pin, GPIO_SPEED_FREQ_##_freq, GPIO_##_pull);

    digital_output_t * me = &g_digital_output;

//    trace_template_new_and_subscribe(&me->p_template,
//                                     "DOP",
//                                     (uint8_t *) &me->digital_output_index,
//                                     (uint8_t *) &me->digital_output_state,
//                                     NULL,
//                                     NULL,
//                                     NULL);

    DIGITAL_OUTPUT_TABLE(EXPAND_AS_INIT)

    return &g_digital_output;
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_output_deinit(digital_output_index_t index)
{
//    digital_output_t * me = &g_digital_output;

//    if (me->p_template != NULL)
//    {
//        trace_template_delete(me->p_template);
//        me->p_template = NULL;
//    }
}

