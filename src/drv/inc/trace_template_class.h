/**************************************************************************//**

  @file smf_class.c
  @brief Private class definition file for the trace template object

******************************************************************************/
#ifndef TRACE_TEMPLATE_CLASS_H
#define TRACE_TEMPLATE_CLASS_H

/******************************************************************************
  Includes
******************************************************************************/
//#include "rtc.h"
//#include "target.h"
#include <stdint.h>

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
/*  Trace Template Class Definition */
typedef struct trace_template
{
    int id;
    int count;
    uint8_t * member[RECORD_PAYLOAD_SIZE];
} trace_template_t;

/******************************************************************************
  Prototypes
******************************************************************************/

extern p_trace_template_t trace_template_new_body(const char *);
extern void trace_template_subscribe_body(p_trace_template_t, uint8_t *);
extern void trace_template_new_and_subscribe_body(p_trace_template_t *,
                                                  const char *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *);

extern void trace_template_capture_body(p_trace_template_t);

#endif
