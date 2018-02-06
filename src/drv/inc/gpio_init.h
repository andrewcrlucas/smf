/**************************************************************************//**

  @file gpio_init.h.c
  @brief Public API definition file for initializing the gpio

******************************************************************************/
#ifndef GPIO_INIT_H
#define GPIO_INIT_H

/******************************************************************************
  Public Prototypes
******************************************************************************/
extern void gpio_init_output(GPIO_TypeDef *, uint32_t, uint32_t, uint32_t);
extern void gpio_init_input(GPIO_TypeDef *, uint32_t);
extern void gpio_init_alternate_function(GPIO_TypeDef *, uint32_t);
extern void gpio_init_analog(GPIO_TypeDef *, uint32_t);
extern void gpio_init_exti(GPIO_TypeDef *, uint32_t, uint32_t, uint32_t);

#endif
