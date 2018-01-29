/*
 * thread10.c
 *
 *  Created on: Jan 29, 2018
 *      Author: Andrew Lucas
 */

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
/* module */
#include "thread10.h"

void thread10_callback(void *me)
{
	static int count;

	count++;
}
