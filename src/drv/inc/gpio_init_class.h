/**************************************************************************//**

  @file gpio_init_class.h
  @brief Private header file exposing internals for testing purposes

******************************************************************************/
#ifndef GPIO_INIT_CLASS_H
#define GPIO_INIT_CLASS_H

/******************************************************************************
  Public Prototypes for testing purposes
******************************************************************************/
extern void gpio_init_output_body(GPIO_TypeDef *, uint32_t, uint32_t, uint32_t);
extern void gpio_init_input_body(GPIO_TypeDef *, uint32_t);
extern void gpio_init_alternate_function_body(GPIO_TypeDef *, uint32_t);
extern void gpio_init_analog_body(GPIO_TypeDef *, uint32_t);
extern void gpio_init_exti_body(GPIO_TypeDef *, uint32_t, uint32_t, uint32_t);

/******************************************************************************
  Public Variables for testing purposes
******************************************************************************/
extern GPIO_InitTypeDef g_gpio_init_struct;

#endif
