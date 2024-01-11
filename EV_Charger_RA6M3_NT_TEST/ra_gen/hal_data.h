/* generated HAL header file - do not edit */
#ifndef HAL_DATA_H_
#define HAL_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "common_data.h"
#include "r_gpt.h"
#include "r_timer_api.h"
#include "r_sci_uart.h"
#include "r_uart_api.h"
#include "r_can.h"
#include "r_can_api.h"
FSP_HEADER
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer_485;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer_485_ctrl;
extern const timer_cfg_t g_timer_485_cfg;

#ifndef timer_485_callback
void timer_485_callback(timer_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart_485;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart_485_ctrl;
extern const uart_cfg_t g_uart_485_cfg;
extern const sci_uart_extended_cfg_t g_uart_485_cfg_extend;

#ifndef user_uart485_callback
void user_uart485_callback(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart2_card_test;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart2_card_test_ctrl;
extern const uart_cfg_t g_uart2_card_test_cfg;
extern const sci_uart_extended_cfg_t g_uart2_card_test_cfg_extend;

#ifndef card_test_callback
void card_test_callback(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart_touch_panel;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart_touch_panel_ctrl;
extern const uart_cfg_t g_uart_touch_panel_cfg;
extern const sci_uart_extended_cfg_t g_uart_touch_panel_cfg_extend;

#ifndef touch_panel_callback
void touch_panel_callback(uart_callback_args_t *p_args);
#endif
/** UART on SCI Instance. */
extern const uart_instance_t g_uart_card_reader;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart_card_reader_ctrl;
extern const uart_cfg_t g_uart_card_reader_cfg;
extern const sci_uart_extended_cfg_t g_uart_card_reader_cfg_extend;

#ifndef card_reader_callback
void card_reader_callback(uart_callback_args_t *p_args);
#endif
/** CAN on CAN Instance. */
extern const can_instance_t g_can_acdc_main;
/** Access the CAN instance using these structures when calling API functions directly (::p_api is not used). */
extern can_instance_ctrl_t g_can_acdc_main_ctrl;
extern const can_cfg_t g_can_acdc_main_cfg;
extern const can_extended_cfg_t g_can_acdc_main_extended_cfg;

#ifndef can_acdc_callback
void can_acdc_callback(can_callback_args_t *p_args);
#endif
#define CAN_NO_OF_MAILBOXES_g_can_acdc_main (8)
/** CAN on CAN Instance. */
extern const can_instance_t g_can_main_acdc;
/** Access the CAN instance using these structures when calling API functions directly (::p_api is not used). */
extern can_instance_ctrl_t g_can_main_acdc_ctrl;
extern const can_cfg_t g_can_main_acdc_cfg;
extern const can_extended_cfg_t g_can_main_acdc_extended_cfg;

#ifndef can_main_callback
void can_main_callback(can_callback_args_t *p_args);
#endif
#define CAN_NO_OF_MAILBOXES_g_can_main_acdc (8)
void hal_entry(void);
void g_hal_init(void);
FSP_FOOTER
#endif /* HAL_DATA_H_ */
