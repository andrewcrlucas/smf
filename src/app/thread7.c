/*************************************************************************//**

  @file thread7.c
  @brief

******************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread7.h"
/* os */
#include "cmsis_os2.h"
#include "os_event_flags.h"
/* project */
#include "const.h"

void thread7(void *me)
{
    while (1)
    {
        osEventFlagsWait(g_my_flags_event_flags_id, (FLAG1 | FLAG0), osFlagsWaitAll, osWaitForever);
        /* Give up processor */
        osDelay(1);
    }
}

