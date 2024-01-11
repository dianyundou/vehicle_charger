/*
 * card_reader.c
 *
 *  Created on: Nov 22, 2023
 *      Author: a5059731
 */

#include "user.h"
#include "hal_data.h"
#include "common_utils.h"

uint8_t card_reader_buf[16];
uint8_t card_swiping_data[3] = {0x0D, 0x0A, 0x03};
uint8_t card_no[8] = {0};

volatile _Bool card_rcv_flag = FALSE;

static volatile _Bool card_test_tx_flag = FALSE;  // only for card reader's test

void card_reader_init(void)
{
    fsp_err_t status = FSP_SUCCESS;

    status = R_SCI_UART_Open(&g_uart_card_reader_ctrl, &g_uart_card_reader_cfg);
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nCard Reader API Open Failed");
        APP_ERR_TRAP(status);
    }

    status = R_SCI_UART_Read(&g_uart_card_reader_ctrl, card_reader_buf, 12);
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nCard Reader API Open Failed");
        APP_ERR_TRAP(status);
    }
}

// only for test, simulating swiping card, using UART2, which can be deleted after testing
void card_swiping_test(void)
{
    fsp_err_t status = FSP_SUCCESS;
    uint8_t card_snd[12] = {0x02, 0x30, 0x30, 0x36, 0x44, 0x38, 0x34, 0x32, 0x41, 0x0D, 0x0A, 0x03};

    status = R_SCI_UART_Open(&g_uart2_card_test_ctrl, &g_uart2_card_test_cfg);
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nCard Reader API Open Failed");
        APP_ERR_TRAP(status);
    }

    R_SCI_UART_Write(&g_uart2_card_test_ctrl, card_snd, 12);
    while(!card_test_tx_flag);
    card_test_tx_flag = FALSE;
}

// only for test, in callback function of UART2
void card_test_callback(uart_callback_args_t *p_args)
{
    switch(p_args->event)
    {
        case UART_EVENT_TX_COMPLETE:
            card_test_tx_flag = TRUE;
            break;
        default:
            break;
    }
}

void card_reader_routine(void)
{

    if(card_rcv_flag == TRUE)
    {
        /* Swiping card firstly */
        if((card_reader_buf[9] == 0x0D) && (card_reader_buf[10] == 0x0A) && (card_reader_buf[11] == 0x03))
        {
            /* Store card number */
            memcpy(card_no, &card_reader_buf[1], 8);
        }
        card_rcv_flag = FALSE;
    }


}

void card_reader_callback(uart_callback_args_t *p_args)
{
    fsp_err_t status = FSP_SUCCESS;
    switch(p_args->event)
    {
        case UART_EVENT_RX_COMPLETE:
            card_rcv_flag = 1;
            status = R_SCI_UART_Read(&g_uart_card_reader_ctrl, card_reader_buf, 12);
            if(FSP_SUCCESS != status)
            {
                APP_ERR_PRINT("\r\nCard Reader API Open Failed");
                APP_ERR_TRAP(status);
            }
            break;
        default:
            break;
    }
}
