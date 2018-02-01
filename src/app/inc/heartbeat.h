/*************************************************************************//**

  @file heartbeat.h
  @brief Public API definition file for the heartbeat object

******************************************************************************/
#ifndef HEARTBEAT_H_
#define HEARTBEAT_H_

/******************************************************************************
  Includes
******************************************************************************/
#include "cmsis_os2.h"

/******************************************************************************
  Defined and Enumerated Constants
******************************************************************************/
#define HEARTBEAT_STACK_SIZE (0)

/******** INSTANCE ****** DIGITAL_OUTPUT **/
#define HEARTBEAT_TABLE(ENTRY) \
    ENTRY(HEARTBEAT_1, HEARTBEAT_LED)

#define EXPAND_AS_HEARTBEAT_ENUM(_index, _digital_output) _index,

/******************************************************************************
  Public Defined Datatypes
******************************************************************************/
typedef enum
{
    HEARTBEAT_TABLE(EXPAND_AS_HEARTBEAT_ENUM)
    N_HEARTBEATS,
} heartbeat_index_t;

/* Delays in ms */
#define FAST_DELAY   (500)
#define NORMAL_DELAY (1000)
#define SLOW_DELAY   (2000)

/******************************************************************************
  Public Prototypes
******************************************************************************/
extern void heartbeat_create(uint32_t);
extern void heartbeat_start(void);

/******************************************************************************
  Public Variables
******************************************************************************/
extern osThreadId_t gp_heartbeat_thread_id[N_HEARTBEATS];

#endif /* HEARTBEAT_H_ */
