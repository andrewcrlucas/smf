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
typedef void (* fp_trace_template_new_and_subscribe_t)(p_trace_template_t *,
                                                       const char *,
                                                       uint8_t *,
                                                       uint8_t *,
                                                       uint8_t *,
                                                       uint8_t *,
                                                       uint8_t *);
typedef p_trace_template_t (* fp_trace_template_new_t)(const char *);
typedef void (* fp_trace_template_subscribe_t)(p_trace_template_t, uint8_t *);
typedef void (* fp_trace_template_capture_t)(p_trace_template_t);

/*  Trace Template Class Definition */
typedef struct trace_template
{
    int id;
    int count;
    uint8_t * member[RECORD_PAYLOAD_SIZE];
} trace_template_t;

extern p_trace_template_t trace_template_new(const char *);
extern void trace_template_subscribe(p_trace_template_t, uint8_t *);

extern fp_trace_template_new_and_subscribe_t gfp_trace_template_new_and_subscribe;
extern fp_trace_template_new_t gfp_trace_template_new;
extern fp_trace_template_subscribe_t gfp_trace_template_subscribe;
extern fp_trace_template_capture_t gfp_trace_template_capture;

#endif
