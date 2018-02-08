/**************************************************************************//**

  @file trace_template.h
  @brief Public API definition file for the trace template object
  @details To use the tracing module do the following:
           1: during thread initializtion call trace_template_new()
              to get a pointer to a record definition
           2: call trace_template_subscribe() for each variable
              you want to capture in this trace record
           3: during task run-time call trace_template_capture as desired

           NOTE1: the frequency of your capture_records should not be such
                  that the trace fills up too quickly, or that the burden
                  of serivcing the capture routine is too great
           NOTE2: the implementation writes records from a local buffer
                  to the eeprom at a periodic interval, so if you have
                  short bursts of lots of traces then some may be
                  overwritten before they get copied to the eeprom
******************************************************************************/
#ifndef TRACE_TEMPLATE_H
#define TRACE_TEMPLATE_H

/******************************************************************************
  Includes
******************************************************************************/
/* std c library */
#include <stdint.h>

/* project specific */
//#include "trace.h"

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
/* This value determines the size of the each records data payload */
#define RECORD_PAYLOAD_SIZE (5)

/******************************************************************************
  User Defined Datatypes
******************************************************************************/
/* pointer to trace template object */
typedef struct trace_template * p_trace_template_t;
/* pointer to trace template pointers object */
typedef struct trace_template_pointers * p_trace_template_pointers_t;

/******************************************************************************
  Prototypes
******************************************************************************/

/* Function to allocate memory for a trace template and subscribe up to
 * 5 8-bit variables */
extern void trace_template_new_and_subscribe(p_trace_template_t *,
                                             const char *,
                                             uint8_t *,
                                             uint8_t *,
                                             uint8_t *,
                                             uint8_t *,
                                             uint8_t *);

/* Function to deallocate memory used by a trace template */
extern void trace_template_delete(p_trace_template_t);

/* This function captures a new record to the trace based on the template */
extern void trace_template_capture(p_trace_template_t);

//TODO move this prototype to class file when class file exists
extern void trace_template_new_and_subscribe_body(p_trace_template_t *,
                                                  const char *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *,
                                                  uint8_t *);

#endif
