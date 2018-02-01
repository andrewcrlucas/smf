/*
 * heart_beat.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module header and class */
#include "heart_beat.h"
#include "heart_beat_class.h"

/* hal */
//#include "stm32l4xx_hal.h"

/* module specific */
#include "assert.h"
#include "const.h"
//#include "stack_monitor.h"

/*****************************************************************************
 * Private Prototypes                                                        *
 *****************************************************************************/
HEART_BEAT_STATE_TABLE(SMF_EXPAND_AS_PROTOTYPES)

void heart_beat_thread(void *);

/*****************************************************************************
 * Private Variables                                                         *
 *****************************************************************************/
DEFINE_THIS_FILE   /* defines g_this_file[] with the name of this source file */

SMF_CREATE_JUMP_TABLE(HEART_BEAT_STATE_TABLE)

#define MESSAGE_QUEUE_DEPTH (1)

static heart_beat_t g_heart_beat[N_HEART_BEATS];

/*****************************************************************************
 * Public Functions                                                          *
 *****************************************************************************/

/******************************************************************************

  FUNCTION:     heart_beat_start

  SCOPE:        public

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void heart_beat_start(void)
{
    for (unsigned int i = 0; i < N_HEART_BEATS; i++)
    {
        heart_beat_init(i);
    }
}

/******************************************************************************

  FUNCTION:     heart_beat_init

  SCOPE:        public

  PARAMETERS:   instance_id -

  RETURNS:      me - pointer

  DESCRIPTION:

******************************************************************************/
heart_beat_t * heart_beat_init(unsigned int thread_index)
{
    heart_beat_t * me = NULL;

    if (thread_index >= N_HEART_BEATS)
    {
        /* too many threads created */
        ASSERT(0);
    }
    else
    {
        me = &g_heart_beat[thread_index];

        if (me->super.p_state_jump_table != NULL)
        {
            /* state machine instance already initialized */
            ASSERT(false);
        }
        else
        {
            SMF_CONSTRUCTOR(HEART_CHECK_RESET_SOURCE_STATE,
                            "HTB",
                            thread_index,
                            N_HEART_BEAT_STATES);

            heart_beat(me, thread_index);
        }
    }

    return me;
}

/******************************************************************************

  FUNCTION:     heart_beat_deinit

  SCOPE:        public

  PARAMETERS:   me - pointer

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void heart_beat_deinit(heart_beat_index_t thread_index)
{
    heart_beat_t * me = &g_heart_beat[thread_index];

//    if (me->p_trace_template_reset_source != NULL)
//    {
//        trace_template_delete(me->p_trace_template_reset_source);
//        me->p_trace_template_reset_source = NULL;
//    }

    SMF_DECONSTRUCTOR();
}

/******************************************************************************

  FUNCTION:     heart_beat_thread

  SCOPE:        public

  PARAMETERS:   init_flag - pointer

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void heart_beat_thread(void * me)
{
    while (true)
    {
        SMF_RUN();
    }
}

/******************************************************************************

  FUNCTION:     heart_check_reset_source_state

  SCOPE:        private

  PARAMETERS:   me - pointer

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
static void heart_check_reset_source_state(void * p)
{
    heart_beat_t * me = (heart_beat_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_NO_EVENT();
            break;
        }

        case NO_EVENT:
        {
            if (me->p_reset_source_register == NULL)
            {
                ASSERT(false);
            }
            else
            {
                me->reset_source = (uint8_t) ((*(me->p_reset_source_register)) >> 24);

                /* capture reset source to trace */
//                trace_template_capture(me->p_trace_template_reset_source);

                /* check if reset source is watchdog */
                if ((me->reset_source & BIT5) != 0)
                {
                    /* reset source is watchdog */
                    SMF_CHANGE_STATE(HEART_BEAT_FAST_STATE);
                }
                else
                {
                    /* reset source is not watchdog */
                    SMF_CHANGE_STATE(HEART_BEAT_SLOW_STATE);
                }
            }

            break;
        }

        case EXIT_EVENT:
        {
            /* clear reset source after its been read */
            //__HAL_RCC_CLEAR_RESET_FLAGS();
            break;
        }

        default:
        {
            ASSERT(false);
        }
    }
}

/******************************************************************************

  FUNCTION:     heart_beat_fast_state

  SCOPE:        private

  PARAMETERS:   me - pointer

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
static void heart_beat_fast_state(void * p)
{
    heart_beat_t * me = (heart_beat_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_DELAY(FAST_DELAY / 2);
            break;
        }

        case TIMEOUT_EVENT:
        {
            //digital_output_toggle(HEART_BEAT_LED);
            SMF_PEND_AGAIN();
            break;
        }

        /* No exit event, because once in this state we never come out */

        default:
        {
            ASSERT(false);
        }
    }
}

/******************************************************************************

  FUNCTION:     heart_beat_slow_state

  SCOPE:        private

  PARAMETERS:   me - pointer

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
static void heart_beat_slow_state(void * p)
{
    heart_beat_t * me = (heart_beat_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_DELAY(SLOW_DELAY / 2);
            break;
        }

        case TIMEOUT_EVENT:
        {
            //digital_output_toggle(HEART_BEAT_LED);
            SMF_PEND_AGAIN();
            break;
        }

        case EXIT_EVENT:
        {
            break;
        }

        default:
        {
            ASSERT(false);
        }
    }
}

/*****************************************************************************
 * Private Helper Functions                                                  *
 *****************************************************************************/

/******************************************************************************

  FUNCTION:     heart_beat

  SCOPE:        private

  PARAMETERS:

  RETURNS:      void

  DESCRIPTION:

******************************************************************************/
void heart_beat(heart_beat_t * me, unsigned int this_index)
{
    osThreadId_t thread_id;

    osThreadAttr_t thread_attr =
    {
        .stack_size = HEART_BEAT_STACK_SIZE
    };

    thread_id = osThreadNew(heart_beat_thread, (void *) me, &thread_attr);

    if (thread_id == NULL)
    {
        ASSERT(false);
    }
    else
    {
        /* initialize struct from table in .h file */
        #define EXPAND_AS_STRUCT_INIT(_index, _digital_output) \
    if (this_index == _index)                                  \
    {                                                          \
        /*me->p_reset_source_register = &RCC->CSR; */          \
        /*me->digital_output = _digital_output;*/              \
    }

        HEART_BEAT_TABLE(EXPAND_AS_STRUCT_INIT)

        //TODO put stack monitor subscription under test via a mock
//        stack_monitor_subscribe(thread_id, "XXX");

//        /* trace highest 8 bits of reset source register */
//        trace_template_new_and_subscribe(&me->p_trace_template_reset_source,
//                                         "RST",
//                                         &me->reset_source,
//                                         NULL,
//                                         NULL,
//                                         NULL,
//                                         NULL);
    }
}

