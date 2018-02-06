/**************************************************************************//**

  @file gpio_init.c
  @brief Implementation file for the gpio_init object

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module */
#include "gpio_init.h"
#include "gpio_init_class.h"

/******************************************************************************
  Private Variables
******************************************************************************/
GPIO_InitTypeDef g_gpio_init_struct;

/******************************************************************************
  Public Functions
******************************************************************************/

/**************************************************************************//**

  @brief

  @param port
  @param pin
  @param speed
  @param pull

  @return void

******************************************************************************/
__weak void gpio_init_output(GPIO_TypeDef * port,
                             uint32_t pin,
                             uint32_t speed,
                             uint32_t pull)
{
    gpio_init_output_body(port, pin, speed, pull);
}

/**************************************************************************//**

  @brief

  @param port
  @param pin
  @param speed
  @param pull

  @return void

******************************************************************************/
void gpio_init_output_body(GPIO_TypeDef * port,
                           uint32_t pin,
                           uint32_t speed,
                           uint32_t pull)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    g_gpio_init_struct.Speed = speed;
    g_gpio_init_struct.Pull = pull;

    HAL_GPIO_Init(port, &g_gpio_init_struct);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
__weak void gpio_init_input(GPIO_TypeDef * p_port, uint32_t pin)
{
    gpio_init_input_body(p_port, pin);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
void gpio_init_input_body(GPIO_TypeDef * p_port, uint32_t pin)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = GPIO_MODE_INPUT;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(p_port, &g_gpio_init_struct);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
__weak void gpio_init_alternate_function(GPIO_TypeDef * p_port, uint32_t pin)
{
    gpio_init_alternate_function_body(p_port, pin);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
void gpio_init_alternate_function_body(GPIO_TypeDef * p_port, uint32_t pin)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = GPIO_MODE_AF_PP;
    g_gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(p_port, &g_gpio_init_struct);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
__weak void gpio_init_analog(GPIO_TypeDef * p_port, uint32_t pin)
{
    gpio_init_analog_body(p_port, pin);
}

/**************************************************************************//**

  @brief

  @param GPIOx
  @param GPIO_Pin

  @return void

******************************************************************************/
void gpio_init_analog_body(GPIO_TypeDef * p_port, uint32_t pin)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = GPIO_MODE_ANALOG;
    g_gpio_init_struct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(p_port, &g_gpio_init_struct);
}

/**************************************************************************//**

  @brief

  @param p_port
  @param pin
  @param mode
  @param pull

  @return void

******************************************************************************/
__weak void gpio_init_exti(GPIO_TypeDef * p_port,
                           uint32_t pin,
                           uint32_t mode,
                           uint32_t pull)
{
    gpio_init_exti_body(p_port, pin, mode, pull);
}

/**************************************************************************//**

  @brief

  @param p_port
  @param pin
  @param mode
  @param pull

  @return void

******************************************************************************/
void gpio_init_exti_body(GPIO_TypeDef * p_port,
                         uint32_t pin,
                         uint32_t mode,
                         uint32_t pull)
{
    g_gpio_init_struct.Pin = pin;
    g_gpio_init_struct.Mode = mode;
    g_gpio_init_struct.Pull = pull;

    HAL_GPIO_Init(p_port, &g_gpio_init_struct);
}
