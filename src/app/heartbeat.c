/*************************************************************************//**

  @file heartbeat.c
  @brief Implementation file for the heartbeat object

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module header and class */
#include "heartbeat.h"
#include "heartbeat_class.h"

/* hal */
//#include "stm32l4xx_hal.h"

/* module specific */
#include "assert.h"
#include "const.h"
//#include "stack_monitor.h"

/******************************************************************************
  Private Prototypes
******************************************************************************/
HEARTBEAT_STATE_TABLE(SMF_EXPAND_AS_PROTOTYPES)

void heartbeat_thread(void *);

/******************************************************************************
  Private Variables
******************************************************************************/
DEFINE_THIS_FILE               /* defines filename string required by assert */

SMF_CREATE_JUMP_TABLE(HEARTBEAT_STATE_TABLE)

#define MESSAGE_QUEUE_DEPTH (1)

static heartbeat_t g_heartbeat[N_HEARTBEATS];

/******************************************************************************
  Public Functions
******************************************************************************/

/**************************************************************************//**

  @brief Calls thread initialization routine for each heartbeat object in the
         system

  @param void

  @return void

******************************************************************************/
void heartbeat_start(void)
{
    for (unsigned int i = 0; i < N_HEARTBEATS; i++)
    {
        heartbeat_init(i);
    }
}

/**************************************************************************//**

  @brief Initialization routine for a heartbeat object

  @param thread_index

  @return me pointer for thread object

******************************************************************************/
heartbeat_t * heartbeat_init(unsigned int thread_index)
{
    heartbeat_t * me = NULL;

    if (thread_index >= N_HEARTBEATS)
    {
        /* too many threads created */
        ASSERT(0);
    }
    else
    {
        me = &g_heartbeat[thread_index];

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
                            N_HEARTBEAT_STATES);

            heartbeat(me, thread_index);
        }
    }

    return me;
}

/**************************************************************************//**

  @brief De-initialization routine for a heartbeat object

  @param thread_index

  @return void

******************************************************************************/
void heartbeat_deinit(heartbeat_index_t thread_index)
{
    heartbeat_t * me = &g_heartbeat[thread_index];

//    if (me->p_trace_template_reset_source != NULL)
//    {
//        trace_template_delete(me->p_trace_template_reset_source);
//        me->p_trace_template_reset_source = NULL;
//    }

    SMF_DECONSTRUCTOR();
}

/**************************************************************************//**

  @brief Thread outer loop which runs the state machine framework

  @param me pointer

  @return void

******************************************************************************/
void heartbeat_thread(void * me)
{
    while (true)
    {
        SMF_RUN();
    }
}

/**************************************************************************//**

  @brief The initial state which checks the reset source before determining
         how fast to flash the heartbeat

  @param p a void pointer corresponding to the me pointer of a heartbeat object

  @return void

******************************************************************************/
static void heart_check_reset_source_state(void * p)
{
    heartbeat_t * me = (heartbeat_t *) p;

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
                    SMF_CHANGE_STATE(HEARTBEAT_FAST_STATE);
                }
                else
                {
                    /* reset source is not watchdog */
                    SMF_CHANGE_STATE(HEARTBEAT_SLOW_STATE);
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

/**************************************************************************//**

  @brief The fast state which flashes the heartbeat led at a period of
         FAST_DELAY

  @param p a void pointer corresponding to the me pointer of a heartbeat object

  @return void

******************************************************************************/
static void heartbeat_fast_state(void * p)
{
    heartbeat_t * me = (heartbeat_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_DELAY(FAST_DELAY / 2);
            break;
        }

        case TIMEOUT_EVENT:
        {
            //digital_output_toggle(HEARTBEAT_LED);
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

/**************************************************************************//**

  @brief The fast state which flashes the heartbeat led at a period of
         SLOW_DELAY

  @param p a void pointer corresponding to the me pointer of a heartbeat object

  @return void

******************************************************************************/
static void heartbeat_slow_state(void * p)
{
    heartbeat_t * me = (heartbeat_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_DELAY(SLOW_DELAY / 2);
            break;
        }

        case TIMEOUT_EVENT:
        {
            //digital_output_toggle(HEARTBEAT_LED);
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

/******************************************************************************
  Private Helper Functions
******************************************************************************/

/**************************************************************************//**

  @brief The heartbeat object constructor

  @param me - pointer to heartbeat object being constructed
  @param index - index into the array of object structs which corresponds to
                 this object

  @return void

******************************************************************************/
void heartbeat(heartbeat_t * me, unsigned int index)
{
    osThreadId_t thread_id;

    osThreadAttr_t thread_attr =
    {
        .stack_size = HEARTBEAT_STACK_SIZE
    };

    thread_id = osThreadNew(heartbeat_thread, (void *) me, &thread_attr);

    if (thread_id == NULL)
    {
        ASSERT(false);
    }
    else
    {
        /* initialize struct from table in .h file */
        #define EXPAND_AS_STRUCT_INIT(_index, _digital_output)                \
            if (index == _index)                                              \
            {                                                                 \
                /*me->p_reset_source_register = &RCC->CSR; */                 \
                /*me->digital_output = _digital_output;*/                     \
            }

        HEARTBEAT_TABLE(EXPAND_AS_STRUCT_INIT)

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

