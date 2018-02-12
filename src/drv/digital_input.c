/**************************************************************************//**

  @file digital_input.c
  @brief Implementation file for the digital_input object

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module */
#include "digital_input.h"
#include "digital_input_class.h"

/* std c library */
#include "cmsis_os2.h"
#include <stdbool.h>
#include <stdlib.h>

/* project */
#include "assert.h"
#include "gpio_init.h"
#include "notification_queue.h"
//#include "stack_monitor.h"
//#include "target.h"

/******************************************************************************
  Private Prototypes
******************************************************************************/
DIGITAL_INPUT_STATE_TABLE(SMF_EXPAND_AS_PROTOTYPES)

void digital_input_thread(void *);

/******************************************************************************
  Private Variables
******************************************************************************/
DEFINE_THIS_FILE   /* defines g_this_file[] with the name of this source file */

SMF_CREATE_JUMP_TABLE(DIGITAL_INPUT_STATE_TABLE)

#define MESSAGE_QUEUE_DEPTH (1)

static digital_input_t g_digital_input[N_DIGITAL_INPUTS];

/******************************************************************************
  Public Functions
******************************************************************************/

/**************************************************************************//**

  @brief

  @param index

  @return digital_input_value_t

******************************************************************************/
__attribute__((weak)) digital_input_value_t digital_input_read(digital_input_index_t index)
{
    return digital_input_read_body(index);
}

/**************************************************************************//**

  @brief

  @param index

  @return digital_input_value_t

******************************************************************************/
digital_input_value_t digital_input_read_body(digital_input_index_t index)
{
    digital_input_t * me = &g_digital_input[index];

    if (me->super.state == DIGITAL_INPUT_LOW_STATE)
    {
        return INPUT_LOW;
    }
    else
    {
        return INPUT_HIGH;
    }
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
__attribute__((weak)) void digital_input_disable_tracing(digital_input_index_t index)
{
    digital_input_disable_tracing_body(index);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_input_disable_tracing_body(digital_input_index_t index)
{
    //digital_input_t * me = &g_digital_input[index];
    //DISABLE_TRACING();
}

/**************************************************************************//**

  @brief

  @param index
  @param valud
  @param signal

  @return void

******************************************************************************/
__attribute__((weak)) void digital_input_subscribe(digital_input_index_t index,
                                    digital_input_value_t value,
                                    int32_t signal)
{
    digital_input_subscribe_body(index, value, signal);
}

/**************************************************************************//**

  @brief

  @param index
  @param valud
  @param signal

  @return void

******************************************************************************/
void digital_input_subscribe_body(digital_input_index_t index,
                                  digital_input_value_t value,
                                  int32_t signal)
{
    digital_input_t * me = &g_digital_input[index];

    if (value == INPUT_FALLING_EDGE)
    {
        notification_queue_subscribe(me->p_notification_queue, INPUT_LOW, osThreadGetId(), signal);
    }
    else if (value == INPUT_RISING_EDGE)
    {
        notification_queue_subscribe(me->p_notification_queue, INPUT_HIGH, osThreadGetId(), signal);
    }
    else
    {
        /* subscription is either low or high */
        if (digital_input_read(index) == value)
        {
            /* sensor is already in the subscription state, return signal */
            osThreadFlagsSet(osThreadGetId(), signal);
        }
        else
        {
            /* add notification to queue */
            notification_queue_subscribe(me->p_notification_queue, value, osThreadGetId(), signal);
        }
    }
}

/**************************************************************************//**

  @brief

  @param index
  @param signal

  @return void

******************************************************************************/
__attribute__((weak)) void digital_input_unsubscribe(digital_input_index_t index, int32_t signal)
{
    digital_input_unsubscribe_body(index, signal);
}

/**************************************************************************//**

  @brief

  @param index
  @param signal

  @return void

******************************************************************************/
void digital_input_unsubscribe_body(digital_input_index_t index, int32_t signal)
{
    digital_input_t * me = &g_digital_input[index];

    notification_queue_unsubscribe(me->p_notification_queue, osThreadGetId(), signal);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
__attribute__((weak)) void digital_input_enable_scanning(digital_input_index_t index)
{
    digital_input_enable_scanning_body(index);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_input_enable_scanning_body(digital_input_index_t index)
{
    digital_input_t * me = &g_digital_input[index];
    digital_input_message_t digital_input_message;

    digital_input_message.command = DIGITAL_INPUT_ENABLE_SCANNING_CMD;

    SMF_SEND_COMMAND_MESSAGE(me->message_queue_id, &digital_input_message);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
__attribute__((weak)) void digital_input_disable_scanning(digital_input_index_t index)
{
    digital_input_disable_scanning_body(index);
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_input_disable_scanning_body(digital_input_index_t index)
{
    digital_input_t * me = &g_digital_input[index];
    digital_input_message_t digital_input_message;

    digital_input_message.command = DIGITAL_INPUT_DISABLE_SCANNING_CMD;

    SMF_SEND_COMMAND_MESSAGE(me->message_queue_id, &digital_input_message);
}

/**************************************************************************//**

  @brief

  @param void

  @return void

******************************************************************************/
void digital_input_start(void)
{
    for (unsigned int i = 0; i < N_DIGITAL_INPUTS; i++)
    {
        digital_input_init(i);
    }
}

/**************************************************************************//**

  @brief

  @param index

  @return digital_input_t

******************************************************************************/
digital_input_t * digital_input_init(unsigned int index)
{
    digital_input_t * me = NULL;

    if (index >= N_DIGITAL_INPUTS)
    {
        /* too many threads created */
        ASSERT(0);
    }
    else
    {
        me = &g_digital_input[index];

        if (me->super.p_state_jump_table != NULL)
        {
            /* state machine instance already initialized */
            ASSERT(false);
        }
        else
        {
            SMF_CONSTRUCTOR(DIGITAL_INPUT_INITIAL_STATE,
                            "DIN",
                            index,
                            N_DIGITAL_INPUT_STATES);

            digital_input(me, index);
        }
    }

    return me;
}

/**************************************************************************//**

  @brief

  @param index

  @return void

******************************************************************************/
void digital_input_deinit(digital_input_index_t index)
{
    digital_input_t * me = &g_digital_input[index];

    SMF_DECONSTRUCTOR();
}

/**************************************************************************//**

  @brief

  @param me

  @return void

******************************************************************************/
void digital_input_thread(void * me)
{
    while (true)
    {
        SMF_RUN();
    }
}

/**************************************************************************//**

  @brief

  @param me
  @param event

  @return void

******************************************************************************/
uint32_t digital_input_get_event(digital_input_t const * me, uint32_t event)
{
    switch (event)
    {
        case MESSAGE_RECEIVED_EVENT:
        {
            if (me->message.command == DIGITAL_INPUT_DISABLE_SCANNING_CMD)
            {
                event = DISABLE_SCANNING_EVENT;
            }
            else if (me->message.command == DIGITAL_INPUT_ENABLE_SCANNING_CMD)
            {
                event = ENABLE_SCANNING_EVENT;
            }
            else
            {
                ASSERT(false);
                event = ASSERT_EVENT;
            }

            break;
        }

        default:
        {
            /* return state machine event */
            break;
        }
    }

    return event;
}

/**************************************************************************//**

  @brief

  @param p

  @return void

******************************************************************************/
static void digital_input_initial_state(void * p)
{
    digital_input_t * me = (digital_input_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_NO_EVENT();
            break;
        }

        case NO_EVENT:
        {
            if (me->initial_state == INPUT_LOW)
            {
                SMF_CHANGE_STATE(DIGITAL_INPUT_LOW_STATE);
            }
            else if (me->initial_state == INPUT_HIGH)
            {
                SMF_CHANGE_STATE(DIGITAL_INPUT_HIGH_STATE);
            }
            else
            {
                ASSERT(false);
            }

            break;
        }

        case EXIT_EVENT:
        {
            break;
        }

        default:
        {
            ASSERT(false);
            break;
        }
    }
}

/**************************************************************************//**

  @brief

  @param p

  @return void

******************************************************************************/
static void digital_input_low_state(void * p)
{
    digital_input_t * me = (digital_input_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            notification_queue_update_state(me->p_notification_queue, INPUT_LOW);

            me->debounce_counter = 0;
            SMF_PEND_ON_MESSAGE(me->message_queue_id, &me->message, me->polling_period);
            break;
        }

        case ENABLE_SCANNING_EVENT:
        {
            SMF_PEND_AGAIN();
            break;
        }

        case DISABLE_SCANNING_EVENT:
        {
            SMF_CHANGE_STATE(DIGITAL_INPUT_SCANNING_DISABLED_STATE);
            break;
        }

        case TIMEOUT_EVENT:
        {
            if (HAL_GPIO_ReadPin(me->port, me->pin) == GPIO_PIN_SET)
            {
                /* read input high */
                if (me->debounce_counter >= me->high_debounce_count)
                {
                    /* debounce count reached  */
                    SMF_CHANGE_STATE(DIGITAL_INPUT_HIGH_STATE);
                }
                else
                {
                    /* debounce count not reached so pend again */
                    me->debounce_counter++;
                    SMF_PEND_AGAIN();
                }
            }
            else
            {
                /* read input low - clear debounce count and pend again */
                me->debounce_counter = 0;
                SMF_PEND_AGAIN();
            }

            break;
        }

        case EXIT_EVENT:
        {
            break;
        }

        default:
        {
            ASSERT(false);
            break;
        }
    }
}

/**************************************************************************//**

  @brief

  @param p

  @return void

******************************************************************************/
static void digital_input_high_state(void * p)
{
    digital_input_t * me = (digital_input_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            notification_queue_update_state(me->p_notification_queue, INPUT_HIGH);

            me->debounce_counter = 0;
            SMF_PEND_ON_MESSAGE(me->message_queue_id, &me->message, me->polling_period);
            break;
        }

        case ENABLE_SCANNING_EVENT:
        {
            SMF_PEND_AGAIN();
            break;
        }

        case DISABLE_SCANNING_EVENT:
        {
            SMF_CHANGE_STATE(DIGITAL_INPUT_SCANNING_DISABLED_STATE);
            break;
        }

        case TIMEOUT_EVENT:
        {
            if (HAL_GPIO_ReadPin(me->port, me->pin) == GPIO_PIN_RESET)
            {
                /* read input low */
                if (me->debounce_counter >= me->low_debounce_count)
                {
                    /* debounce count reached  */
                    SMF_CHANGE_STATE(DIGITAL_INPUT_LOW_STATE);
                }
                else
                {
                    /* debounce count not reached so pend again */
                    me->debounce_counter++;
                    SMF_PEND_AGAIN();
                }
            }
            else
            {
                /* read input high - clear debounce count and pend again */
                me->debounce_counter = 0;
                SMF_PEND_AGAIN();
            }

            break;
        }

        case EXIT_EVENT:
        {
            break;
        }

        default:
        {
            ASSERT(false);
            break;
        }
    }
}

/**************************************************************************//**

  @brief

  @param p

  @return void

******************************************************************************/
static void digital_input_scanning_disabled_state(void * p)
{
    digital_input_t * me = (digital_input_t *) p;

    switch (SMF_MY_EVENT)
    {
        case ENTRY_EVENT:
        {
            SMF_PEND_ON_MESSAGE(me->message_queue_id, &me->message, osWaitForever);
            break;
        }

        case DISABLE_SCANNING_EVENT:
        {
            SMF_PEND_AGAIN();
            break;
        }

        case ENABLE_SCANNING_EVENT:
        {
            SMF_CHANGE_STATE(DIGITAL_INPUT_LOW_STATE);
            break;
        }

        case EXIT_EVENT:
        {
            break;
        }

        default:
        {
            ASSERT(false);
            break;
        }
    }
}

/******************************************************************************
  Private Helper Functions
******************************************************************************/

/**************************************************************************//**

  @brief

  @param me
  @param this_index

  @return void

******************************************************************************/
void digital_input(digital_input_t * me, unsigned int this_index)
{
    osThreadId_t thread_id;

    osThreadAttr_t thread_attr =
    {
        .stack_size = DIGITAL_INPUT_STACK_SIZE
    };

    thread_id = osThreadNew(digital_input_thread, (void *) me, &thread_attr);

    if (thread_id == NULL)
    {
        /* osThreadCreate returned NULL thread id */
        ASSERT(false);
    }
    else
    {
        me->message_queue_id = osMessageQueueNew(MESSAGE_QUEUE_DEPTH, sizeof(digital_input_message_t), NULL);

        if (me->message_queue_id == NULL)
        {
            ASSERT(false);
        }
        else
        {
            /* initialize struct from table in .h file */
            #define EXPAND_AS_STRUCT_INIT(_index, _initial_state, _polling_period, _high_debounce_count, _low_debounce_count, _port, _pin, _b_scanning_disable) \
    if (this_index == _index)                                                                                                                                   \
    {                                                                                                                                                           \
        me->initial_state = _initial_state;                                                                                                                     \
        me->polling_period = _polling_period;                                                                                                                   \
        me->high_debounce_count = _high_debounce_count;                                                                                                         \
        me->low_debounce_count = _low_debounce_count;                                                                                                           \
        me->port = _port;                                                                                                                                       \
        me->pin = _pin;                                                                                                                                         \
        __HAL_RCC_##_port##_CLK_ENABLE();                                                                                                                       \
        gpio_init_input(_port, _pin);                                                                                                                           \
        digital_input_constructor_disable_scanning(_index, _b_scanning_disable);                                                                                \
    }

            me->debounce_counter = 0;

            DIGITAL_INPUT_TABLE(EXPAND_AS_STRUCT_INIT)

            //TODO put stack monitor subscription under test via a mock
//            stack_monitor_subscribe(thread_id, "XXX");

            /* Add specific code here */
            me->p_notification_queue = notification_queue_new();
        }
    }
}

/**************************************************************************//**

  @brief

  @param index
  @param b_scanning_disable

  @return void

******************************************************************************/
void digital_input_constructor_disable_scanning(digital_input_index_t index, bool b_scanning_disable)
{
    if (b_scanning_disable == true)
    {
        digital_input_disable_scanning(index);
    }
}

