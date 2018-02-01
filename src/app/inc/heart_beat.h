/*
 * heart_beat.h
 */

#ifndef HEART_BEAT_H_
#define HEART_BEAT_H_

/*****************************************************************************
 * Includes                                                                  *
 *****************************************************************************/
#include "cmsis_os2.h"

/*****************************************************************************
 * Defined and Enumerated Constants                                          *
 *****************************************************************************/
#define HEART_BEAT_STACK_SIZE (0)

/******** INSTANCE ****** DIGITAL_OUTPUT **/
#define HEART_BEAT_TABLE(ENTRY) \
    ENTRY(HEART_BEAT_1, HEART_BEAT_LED)

#define EXPAND_AS_HEART_BEAT_ENUM(_index, _digital_output) _index,

/******************************************************************************
* Public Defined Datatypes
******************************************************************************/
typedef enum
{
    HEART_BEAT_TABLE(EXPAND_AS_HEART_BEAT_ENUM)
    N_HEART_BEATS,
} heart_beat_index_t;

/* Delays in ms */
#define FAST_DELAY   (500)
#define NORMAL_DELAY (1000)
#define SLOW_DELAY   (2000)

/*****************************************************************************
 * Public Prototypes                                                         *
 *****************************************************************************/
extern void heart_beat_create(uint32_t);
extern void heart_beat_start(void);

/*****************************************************************************
 * Public Variables                                                          *
 *****************************************************************************/
extern osThreadId_t gp_heart_beat_thread_id[N_HEART_BEATS];

#endif /* HEART_BEAT_H_ */
