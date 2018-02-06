/**************************************************************************//**

  @file assert.c
  @brief

******************************************************************************/

/******************************************************************************
  Includes
******************************************************************************/
/* module specific */
#include "assert.h"
/* std c library */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
/* os */
#include "cmsis_os2.h"
/* project specific */
#include "const.h"
//#include "digital_output.h"
//#include "trace_template.h"

/******************************************************************************
  Private Variables
******************************************************************************/
//static p_trace_template_t gp_trace_template = NULL;

static uint8_t g_assert_buffer[4];

static int g_file_name_first_letter_index = 0;
static int g_file_name_last_letter_index = 1;
static int g_file_line_first_number_index = 2;
static int g_file_line_second_number_index = 3;

/******************************************************************************
  Public Interface Functions
******************************************************************************/

/******************************************************************************

  FUNCTION:     on_assert

  SCOPE:        public

  PARAMETERS:   file - string containing the module name where assert occured
                line - integer containing the line number of the assert

  RETURNS:      void

  DESCRIPTION:  outputs the file name and line number where the assert occurs
                to the assert buffer and then allows the watchdog timer to
                expire

******************************************************************************/
void on_assert(char const * file, int line)
{
    int directory_name_offset = 4; /* offset for "app/" */
    int file_extension_offset = 2; /* offset for ".c" */
    int file_name_len = 0;
    static bool b_running = false;

    /* only allow one thread to access os_assert().  If a second call is made,
     * hold this thread in osWaitForever to prevent this thread from potentially
     * crashing (eq seg fault) which would prevent the trace from being written */
    if (b_running == true)
    {
        osDelay(osWaitForever);
    }

    b_running = true;

    /* remove directory name characters from file name */
    file = &file[directory_name_offset];

    while (file[file_name_len] != 0)
    {
        file_name_len++;
    }

    /* write file name and line number to trace */
    g_assert_buffer[g_file_name_first_letter_index] = (uint8_t) file[0];
    g_assert_buffer[g_file_name_last_letter_index] = (uint8_t) file[file_name_len - (file_extension_offset + 1)];
    g_assert_buffer[g_file_line_first_number_index] = MSB(line);
    g_assert_buffer[g_file_line_second_number_index] = LSB(line);
    //trace_template_capture(gp_trace_template);

    //trace_write_to_eeprom(TRACE_1, NULL);

    /* delay while trace writes */
    osDelay(25);

    /* flash leds to indicate assert */
    while (true)
    {
        /* flash all leds to indicate assert */
        //digital_output_set(DEBUG_LED_1, DEBUG_LED_ON);
        //digital_output_set(DEBUG_LED_2, DEBUG_LED_ON);
        //digital_output_set(DEBUG_LED_3, DEBUG_LED_ON);
        //digital_output_set(DEBUG_LED_4, DEBUG_LED_ON);

        osDelay(300);

        //digital_output_set(DEBUG_LED_1, DEBUG_LED_OFF);
        //digital_output_set(DEBUG_LED_2, DEBUG_LED_OFF);
        //digital_output_set(DEBUG_LED_3, DEBUG_LED_OFF);
        //digital_output_set(DEBUG_LED_4, DEBUG_LED_OFF);

        osDelay(300);
    }
}

/******************************************************************************

  FUNCTION:     assert_init

  SCOPE:        public

  PARAMETERS:   void

  RETURNS:      void

  DESCRIPTION:  initialize template for trace

******************************************************************************/
void assert_init(void)
{
//    trace_template_new_and_subscribe(&gp_trace_template,
//                                     "AST",
//                                     &g_assert_buffer[g_file_name_first_letter_index],
//                                     &g_assert_buffer[g_file_name_last_letter_index],
//                                     &g_assert_buffer[g_file_line_first_number_index],
//                                     &g_assert_buffer[g_file_line_second_number_index],
//                                     NULL);
}

