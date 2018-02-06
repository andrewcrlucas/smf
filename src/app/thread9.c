/**************************************************************************//**

  @file thread9.c
  @brief

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module */
#include "thread9.h"
/* os */
#include "cmsis_os2.h"
#include "os_message_queue.h"
/* project */
#include "thread8.h"

/******************************************************************************
  Public functions
******************************************************************************/

/**************************************************************************//**

  @brief

  @param void

  @return void

******************************************************************************/
void thread9(void *me)
{
    msg_t msg;

    while (1)
    {
        osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
        osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
        osMessageQueueGet(g_my_message_queue_id, &msg, NULL, osWaitForever);
        osDelay(1);
    }
}

