/*
 * touch_panel.c
 *
 *  Created on: Nov 22, 2023
 *      Author: a5059731
 */

#include "user.h"
#include "hal_data.h"
#include "common_utils.h"

volatile _Bool panel_snd_flag = FALSE;
volatile _Bool panel_rcv_flag = FALSE;

void touch_panel_init(void)
{
    fsp_err_t status = FSP_SUCCESS;

    status = R_SCI_UART_Open(&g_uart_touch_panel_ctrl, &g_uart_touch_panel_cfg);
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nTouch Panel API Open Failed");
        APP_ERR_TRAP(status);
    }
}

void touch_panel_routine(void)
{

}

void touch_panel_callback(uart_callback_args_t *p_args)
{
    switch(p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
            panel_snd_flag = TRUE;
            break;
        case UART_EVENT_RX_COMPLETE:
            panel_rcv_flag = TRUE;
        default:
            break;
    }
}
