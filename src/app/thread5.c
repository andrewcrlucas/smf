/*
 * thread5.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread5.h"
/* os */
#include "cmsis_os2.h"
#include "os_event_flags.h"
/* project */
#include "const.h"

void thread5(void *me)
{
    while (1)
    {
        /* Give up processor */
        osDelay(50);

        osEventFlagsSet(g_my_flags_event_flags_id, FLAG0);
    }
}

