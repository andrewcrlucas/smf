/**************************************************************************//**

  @file trace_template.c
  @brief Implementation file for the trace template object

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module specific */
#include "trace_template.h"
#include "trace_template_class.h"

/* project specific */
#include "assert.h"
//#include "trace_class.h"
#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************
  Private Variables
******************************************************************************/
DEFINE_THIS_FILE

/******************************************************************************
  Private Prototypes
******************************************************************************/
#if 0
static void copy_trace_record_data(p_trace_template_t, trace_record_t *);
#endif

/******************************************************************************
  Public Interface Functions
******************************************************************************/

/**************************************************************************//**

  @brief Function to allocate memory for a trace template and subscribe
                up to 5 8-bit variables

  @param pp_trace_template
  @param thread_name
  @param p_data_member1
  @param p_data_member2
  @param p_data_member3
  @param p_data_member4
  @param p_data_member5

  @return void

******************************************************************************/
__attribute__((weak)) void trace_template_new_and_subscribe(p_trace_template_t * pp_trace_template,
                                                            const char * thread_name,
                                                            uint8_t * p_data_member1,
                                                            uint8_t * p_data_member2,
                                                            uint8_t * p_data_member3,
                                                            uint8_t * p_data_member4,
                                                            uint8_t * p_data_member5)
{
    trace_template_new_and_subscribe_body(pp_trace_template,
                                          thread_name,
                                          p_data_member1,
                                          p_data_member2,
                                          p_data_member3,
                                          p_data_member4,
                                          p_data_member5);
}

/**************************************************************************//**

  @brief Function to allocate memory for a trace template and subscribe
                up to 5 8-bit variables

  @param pp_trace_template
  @param thread_name
  @param p_data_member1
  @param p_data_member2
  @param p_data_member3
  @param p_data_member4
  @param p_data_member5

  @return void

******************************************************************************/
void trace_template_new_and_subscribe_body(p_trace_template_t * pp_trace_template,
                                           const char * thread_name,
                                           uint8_t * p_data_member1,
                                           uint8_t * p_data_member2,
                                           uint8_t * p_data_member3,
                                           uint8_t * p_data_member4,
                                           uint8_t * p_data_member5)
{
    /* use function body */
    if (thread_name == NULL)
    {
        (*pp_trace_template) = NULL;
    }
    else
    {
        if ((*pp_trace_template) == NULL)
        {
            (*pp_trace_template) = trace_template_new(thread_name);

            if ((*pp_trace_template) == NULL)
            {
                ASSERT(false);
            }
            else
            {
                if (p_data_member1 != NULL)
                {
                    trace_template_subscribe((*pp_trace_template), p_data_member1);
                }

                if (p_data_member2 != NULL)
                {
                    trace_template_subscribe((*pp_trace_template), p_data_member2);
                }

                if (p_data_member3 != NULL)
                {
                    trace_template_subscribe((*pp_trace_template), p_data_member3);
                }

                if (p_data_member4 != NULL)
                {
                    trace_template_subscribe((*pp_trace_template), p_data_member4);
                }

                if (p_data_member5 != NULL)
                {
                    trace_template_subscribe((*pp_trace_template), p_data_member5);
                }
            }
        }
    }
}

/**************************************************************************//**

  @brief

  @param thread_name

  @return p_trace_template_t

******************************************************************************/
__attribute__((weak)) p_trace_template_t trace_template_new(const char * thread_name)
{
    return trace_template_new_body(thread_name);
}

/**************************************************************************//**

  @brief

  @param thread_name

  @return p_trace_template_t

******************************************************************************/
p_trace_template_t trace_template_new_body(const char * thread_name)
{
    p_trace_template_t me;

    /* Allocate a new trace template */
    me = (p_trace_template_t) malloc(sizeof(trace_template_t));

    if (me == NULL)
    {
        ASSERT(false);
    }
    else
    {
#if 0
        /* Allocate a new trace legend entry */
        me->id = trace_legend_append(TRACE_1, thread_name);
#endif
        me->count = 0;
    }

    return me;
}

/**************************************************************************//**

  @brief  deallocates memory for a record definition

  @param  me

  @return void

******************************************************************************/
void trace_template_delete(p_trace_template_t me)
{
    if (me != NULL)
    {
        free(me);
    }
}

/**************************************************************************//**

  @brief  puts address of an 8bit data member into a record definition

  @param  me
  @param  p_data_member

  @return void

******************************************************************************/
__attribute__((weak))  void trace_template_subscribe(p_trace_template_t me, uint8_t * p_data_member)
{
    trace_template_subscribe_body(me, p_data_member);
}

/**************************************************************************//**

  @brief  puts address of an 8bit data member into a record definition

  @param  me
  @param  p_data_member

  @return void

******************************************************************************/
void trace_template_subscribe_body(p_trace_template_t me, uint8_t * p_data_member)
{
    if (me == NULL)
    {
        ASSERT(false);
    }
    else
    {
        /* use function body */
        if (me->count < RECORD_PAYLOAD_SIZE)
        {
            me->member[me->count] = p_data_member;
            me->count++;
        }
        else
        {
            ASSERT(false);
        }
    }
}

/**************************************************************************//**

  @brief  triggers the capture of a template record

  @param  me

  @return void

******************************************************************************/
__attribute__((weak))  void trace_template_capture(p_trace_template_t me)
{
    trace_template_capture_body(me);
}

/**************************************************************************//**

  @brief  triggers the capture of a template record

  @param  me

  @return void

******************************************************************************/
void trace_template_capture_body(p_trace_template_t me)
{
#if 0
    if (me == NULL)
    {
        ASSERT(false);
    }
    else
    {
        /* use function body */
        trace_record_t record;

        record.id = (uint8_t) me->id;
        rtc_get_timestamp(&record.time);
        copy_trace_record_data(me, &record);

        trace_append(TRACE_1, &record);
    }
#endif
}

/******************************************************************************
  Private Helper Functions
******************************************************************************/
#if 0
/**************************************************************************//**

  @brief  copies each data byte pointed to by the record definition into the
          trace record

  @param  me

  @return void

******************************************************************************/
static void copy_trace_record_data(p_trace_template_t me, trace_record_t * p_trace_record)
{
    for (int i = 0; i < RECORD_PAYLOAD_SIZE; i++)
    {
        if (i < me->count)
        {
            p_trace_record->trace_data[i] = *(me->member[i]);
        }
        else
        {
            p_trace_record->trace_data[i] = 0;
        }
    }
}

#endif
