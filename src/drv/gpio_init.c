/*************************************************************************//**

  @file gpio_init.c
  @brief Implementation file for the gpio_init object

******************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
#include "stm32f7xx_hal.h"

/* module header and class */
#include "gpio_init.h"
#include "gpio_init_class.h"

/*****************************************************************************
 * Private Variables                                                         *
 *****************************************************************************/

GPIO_InitTypeDef g_gpio_init_struct;

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/******************************************************************************

  FUNCTION:     gpio_init_output

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
__weak void gpio_init_output(GPIO_TypeDef * port, uint32_t pin, uint32_t speed, uint32_t pull)
{
    gpio_init_output_body(port, pin, speed, pull);
}

/******************************************************************************

  FUNCTION:     gpio_init_output_body

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void gpio_init_output_body(GPIO_TypeDef * port, uint32_t pin, uint32_t speed, uint32_t pull)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    g_gpio_init_struct.Speed = speed;
    g_gpio_init_struct.Pull = pull;

    HAL_GPIO_Init(port, &g_gpio_init_struct);
}

/******************************************************************************

  FUNCTION:     gpio_init_input

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
__weak void gpio_init_input(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    gpio_init_input_body(GPIOx, GPIO_Pin);
}

/******************************************************************************

  FUNCTION:     gpio_init_input_body

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void gpio_init_input_body(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    g_gpio_init_struct.Pin = GPIO_Pin;
    g_gpio_init_struct.Mode = GPIO_MODE_INPUT;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOx, &g_gpio_init_struct);
}

/******************************************************************************

  FUNCTION:     gpio_init_alternate_function

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
__weak void gpio_init_alternate_function(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    gpio_init_alternate_function_body(GPIOx, GPIO_Pin);
}

/******************************************************************************

  FUNCTION:     gpio_init_input_body

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void gpio_init_alternate_function_body(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    g_gpio_init_struct.Pin = GPIO_Pin;
    g_gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    g_gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOx, &g_gpio_init_struct);
}

/******************************************************************************

  FUNCTION:     gpio_init_analog

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
__weak void gpio_init_analog(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    gpio_init_analog_body(GPIOx, GPIO_Pin);
}

/******************************************************************************

  FUNCTION:     gpio_init_analog_body

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void gpio_init_analog_body(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
    g_gpio_init_struct.Pin = GPIO_Pin;
    g_gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(GPIOx, &g_gpio_init_struct);
}

/******************************************************************************

  FUNCTION:     gpio_init_exti

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
__weak void gpio_init_exti(GPIO_TypeDef * p_port, uint32_t pin, uint32_t mode, uint32_t pull)
{
    gpio_init_exti_body(p_port, pin, mode, pull);
}

/******************************************************************************

  FUNCTION:     gpio_init_analog_body

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void gpio_init_exti_body(GPIO_TypeDef * p_port, uint32_t pin, uint32_t mode, uint32_t pull)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = mode;
    g_gpio_init_struct.Pull = pull;

    HAL_GPIO_Init(p_port, &g_gpio_init_struct);
}

/*****************************************************************************
 * Private Helper Functions                                                  *
 *****************************************************************************/
