/*
 * thread6.c
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread6.h"
/* os */
#include "cmsis_os2.h"
#include "os_event_flags.h"
/* project */
#include "const.h"

void thread6(void *me)
{
	while(1)
	{
		/* Give up processor */
        osDelay(80);

        osEventFlagsSet(g_my_flags_event_flags_id, FLAG1);
	}
}
