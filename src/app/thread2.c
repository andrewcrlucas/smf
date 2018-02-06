/*************************************************************************//**

  @file thread2.c
  @brief

******************************************************************************/

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread2.h"
/* os */
#include "cmsis_os2.h"
#include "os_semaphore.h"

void thread2(void *me)
{
    while (1)
    {
        osSemaphoreAcquire(g_full_id, osWaitForever);
        // consume data
        osSemaphoreRelease(g_empty_id);
    }
}

