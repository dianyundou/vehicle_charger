/*
 * secc_can.c
 *
 *  Created on: Oct 30, 2023
 *      Author: a5059731
 */

#include <main_acdc_can.h>
#include "common_utils.h"
#include "user.h"

/* Flags, set from Callback function */
static volatile _Bool b_can_tx[CHAN_NUM] = {FALSE};        //CAN transmission status
static volatile _Bool b_can_rx[CHAN_NUM] = {FALSE};        //CAN receive status
static volatile _Bool b_can_err[CHAN_NUM] = {FALSE};       //CAN error status

static can_frame_t g_can_rx_frame[CHAN_NUM] = {RESET_VALUE};      //CAN receive frame
static can_frame_t g_can_tx_frame[CHAN_NUM] = {RESET_VALUE};      //CAN transmit frame
static can_id g_can_rx_pgn[CHAN_NUM] = {RESET_VALUE};

/* PGNs includes EDP, DP, PF, and PS. For PF < 240, PS means destination address
 * The four bytes of can_id are listed below
 * first: PDU-DATA(total 32-bit), Data length, Repeat timer */
static can_data_t g_can_data[4] =
{   {0x1826F456, 3, 250},       // CHM
    {0x182756F4, 2, 250},       // BHM
    {0x1801F456, 8, 250},       // CRM
    {0x1C0256F4, 49, 250},      // BRM
};
static uint8_t can_pgn_chm[3] = {1, 1, 0};     // CHM:PGN9728 (SPN=2600, 3 bytes)
static uint8_t can_pgn_bhm[2] = {2, 13};
static uint8_t can_pgn_rcv[8] = {0};
static uint8_t can_acdc_rcv_buf[8] = {0};
/*enum Cmd{
    CHM,
    BHM,
    CRM,
}command_list;
*/

uint16_t    total_voltage;

can_acdc_id g_can_acdc_tx_id;
can_acdc_id g_can_acdc_rx_id;

can_cmd4_dat g_can_cmd4_data;
can_cmd6_dat g_can_cmd6_data;
can_cmd8_dat g_can_cmd8_data;
can_cmd9_dat g_can_cmd9_data;
can_cmdA_dat g_can_cmdA_data;
can_cmdC_dat g_can_cmdC_data;
can_cmd1C_dat g_can_cmd1C_data;

uint8_t mod_group_no;
uint8_t mod_temperature;
uint8_t mod_stat_table_2;
uint8_t mod_stat_table_1;
uint8_t mod_stat_table_0;
float ac_vab, ac_vbc, ac_vca;
uint32_t system_total_v;
uint32_t system_total_i;
uint32_t module_n_v;
uint32_t module_n_i;
uint16_t maximal_v;
uint16_t minimal_v;
float maximal_i;
uint32_t rated_power;
float ext_v, permit_i;
uint8_t open_close_flag;
float module_v, module_i;


uint16_t hcm;
float test;

void can_secc_evcc_init(void)
{
    fsp_err_t status = FSP_SUCCESS;

    /* Initialize CAN module */
    status = R_CAN_Open(&g_can_main_acdc_ctrl, &g_can_main_acdc_cfg);
    /* Error trap */
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nCAN Open API from SECC to EVCC failed");
        APP_ERR_TRAP(status);
    }

//    g_can_tx_pgn[CHAN_ZERO].can_id_bit.PS = CAN_EVCC_ID;
//    g_can_tx_frame[CHAN_ZERO].id = g_can_tx_pgn[CHAN_ZERO].can_id_all;
    g_can_tx_frame[CHAN_ZERO].id_mode = CAN_ID_MODE_EXTENDED;
    g_can_tx_frame[CHAN_ZERO].type = CAN_FRAME_TYPE_DATA;
    g_can_rx_frame[CHAN_ZERO].id_mode = CAN_ID_MODE_EXTENDED;
    g_can_rx_frame[CHAN_ZERO].type = CAN_FRAME_TYPE_DATA;
//    g_can_tx_frame[CHAN_ZERO].data_length_code = 8;

    /* Initialize CAN module */
    status = R_CAN_Open(&g_can_acdc_main_ctrl, &g_can_acdc_main_cfg);
    /* Error trap */
    if(FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\nCAN Open API from EVCC to SECC failed");
        APP_ERR_TRAP(status);
    }

//    g_can_rx_pgn[CHAN_ONE].can_id_bit.PS = CAN_SECC_ID;
//    g_can_rx_frame[CHAN_ONE].id = g_can_rx_pgn[CHAN_ONE].can_id_all;
    g_can_tx_frame[CHAN_ONE].id_mode = CAN_ID_MODE_EXTENDED;
    g_can_tx_frame[CHAN_ONE].type = CAN_FRAME_TYPE_DATA;
    g_can_rx_frame[CHAN_ONE].id_mode = CAN_ID_MODE_EXTENDED;
    g_can_rx_frame[CHAN_ONE].type = CAN_FRAME_TYPE_DATA;
//    g_can_rx_frame[CHAN_ONE].data_length_code = 8;

}

void can_snd(_Bool chan, uint8_t cmd_no, uint8_t * snd_buf, can_instance_t const* p_can)
{
    fsp_err_t status = FSP_SUCCESS;
    uint32_t time_out = WAIT_TIME;                                      // time out

    g_can_tx_frame[chan].id = g_can_data[cmd_no].can_id;
    if((g_can_data[cmd_no].can_dlc < 8) || (g_can_data[cmd_no].can_dlc == 8))
    {
        g_can_tx_frame[chan].data_length_code = g_can_data[cmd_no].can_dlc;
        memcpy((uint8_t*)&g_can_tx_frame[chan].data[0], snd_buf, g_can_data[cmd_no].can_dlc);
    }
    /* transmit the data from mail box #0 with tx_frame */
    status = R_CAN_Write(p_can->p_ctrl, CAN_MAILBOX_NUMBER_4, &g_can_tx_frame[chan]);
    /* Error trap */
    if (FSP_SUCCESS != status)
    {
        APP_ERR_PRINT("\r\n CAN Write API FAILED");
        can_deinit();
        APP_ERR_TRAP(status);
    }

    /* wait for transmit flag bit to set */
    while ((TRUE != b_can_tx[chan]) && (--time_out));
    if (RESET_VALUE == time_out)
    {
        APP_ERR_PRINT("CAN transmission failed due to timeout");
        APP_ERR_TRAP(TRUE);
    }
    /* Reset flag bit */
    b_can_tx[chan] = FALSE;
}

void can_rcv(_Bool chan, uint8_t * rcv_buf)
{
    /* check if receive flag is set */
    if (TRUE == b_can_rx[chan])
    {
        /* Reset flag bit */
        b_can_rx[chan] = FALSE;
        APP_PRINT("\r\n CAN received the data : %s\r\n", &g_can_rx_frame[chan].data);
        memcpy(rcv_buf, (uint8_t*)&g_can_rx_frame[chan].data[0], g_can_rx_frame[chan].data_length_code);
        g_can_rx_pgn[chan].can_id_bit.PF = (g_can_rx_frame[chan].id & 0x0FF0000) >> 16;
    }
}

/*******************************************************************************************************************//**
 * This function is called when an CAN event is occurred and SET the respective flags.
 **********************************************************************************************************************/
void can_main_callback(can_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_TX_COMPLETE:
        {
            b_can_tx[p_args->channel] = TRUE;
            break;
        }

        case CAN_EVENT_RX_COMPLETE:
        {
            b_can_rx[p_args->channel] = TRUE;
            memcpy(&g_can_rx_frame[p_args->channel], &p_args->frame, sizeof(can_frame_t));  //copy the received data to rx_frame
            break;
        }

        case CAN_EVENT_MAILBOX_MESSAGE_LOST:    //overwrite/overrun error event
        case CAN_EVENT_BUS_RECOVERY:            //Bus recovery error event
        case CAN_EVENT_ERR_BUS_OFF:             //error Bus Off event
        case CAN_EVENT_ERR_PASSIVE:             //error passive event
        case CAN_EVENT_ERR_WARNING:             //error warning event
        case CAN_EVENT_ERR_BUS_LOCK:            //error bus lock
        case CAN_EVENT_ERR_CHANNEL:             //error channel
        case CAN_EVENT_ERR_GLOBAL:              //error global
        case CAN_EVENT_TX_ABORTED:              //error transmit abort
        case CAN_EVENT_TX_FIFO_EMPTY:           //error transmit FIFO is empty
        case CAN_EVENT_FIFO_MESSAGE_LOST:       //error FIFO message lost
        {
            b_can_err[p_args->channel] = TRUE;                   //set flag bit
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * This function is called when an CAN event is occurred and SET the respective flags.
 **********************************************************************************************************************/
void can_acdc_callback(can_callback_args_t *p_args)
{
    switch (p_args->event)
    {
        case CAN_EVENT_TX_COMPLETE:
        {
            b_can_tx[p_args->channel] = TRUE;
            break;
        }

        case CAN_EVENT_RX_COMPLETE:
        {
            b_can_rx[p_args->channel] = TRUE;
            memcpy(&g_can_rx_frame[p_args->channel], &p_args->frame, sizeof(can_frame_t));  //copy the received data to rx_frame
            break;
        }

        case CAN_EVENT_MAILBOX_MESSAGE_LOST:    //overwrite/overrun error event
        case CAN_EVENT_BUS_RECOVERY:            //Bus recovery error event
        case CAN_EVENT_ERR_BUS_OFF:             //error Bus Off event
        case CAN_EVENT_ERR_PASSIVE:             //error passive event
        case CAN_EVENT_ERR_WARNING:             //error warning event
        case CAN_EVENT_ERR_BUS_LOCK:            //error bus lock
        case CAN_EVENT_ERR_CHANNEL:             //error channel
        case CAN_EVENT_ERR_GLOBAL:              //error global
        case CAN_EVENT_TX_ABORTED:              //error transmit abort
        case CAN_EVENT_TX_FIFO_EMPTY:           //error transmit FIFO is empty
        case CAN_EVENT_FIFO_MESSAGE_LOST:       //error FIFO message lost
        {
            b_can_err[p_args->channel] = TRUE;                   //set flag bit
            break;
        }
    }
}

/*******************************************************************************************************************//**
 * @brief       This function is to de-initializes the CAN module
 * @param[in]   None
 * @return      None
 **********************************************************************************************************************/
void can_deinit(void)
{
    fsp_err_t err = FSP_SUCCESS;
    err = R_CAN_Close(&g_can_main_acdc_ctrl);
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n **CAN Close API failed**");
    }
}

/* There are totally steps for charging overall process.
    step 1: Physical connection
    step 2: Low-voltage auxiliary power-on
    step 3: Charging handshake phase
*/
void can_secc_evcc_connect(void)
{
    /* The charger should send the first CHM command within 1s after the low voltage auxiliary power supply loop is closed */
    /* ? How to judge low-voltage auxiliary power supply loop is close? */
    can_snd(CHAN_ZERO, CHM, can_pgn_chm, &g_can_main_acdc);
    can_rcv(CHAN_ONE, can_pgn_rcv);
    if(g_can_rx_pgn[CHAN_ONE].can_id_bit.PF == 0x26)
    {
        if((can_pgn_rcv[0] == 0x01) && (can_pgn_rcv[1] == 0x01) && (can_pgn_rcv[2] == 0))
        {
            can_snd(CHAN_ONE, BHM, can_pgn_bhm, &g_can_acdc_main);
        }
    }
    can_rcv(CHAN_ZERO, can_pgn_rcv);
    if(g_can_rx_pgn[CHAN_ONE].can_id_bit.PF == 0x26)
    {
        total_voltage = (uint16_t)(can_pgn_rcv[0] + (uint16_t)(can_pgn_rcv[1] << 8) / 10);
    }
}

/* Can operation between main controller and ACDC module */
void can_main_acdc_init(void)
{
    can_secc_evcc_init();
}

void can_main_acdc_routine(void)
{
    uint8_t snd_buf_temp[8] = {0};

    // cmd = 0x04, master send command, slave receive command and feedback data, the master store data
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, MOD_G_STAT_R, MONITOR_ADDR, MOD0_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x06
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, VAB_BC_CA_R, MONITOR_ADDR, MOD0_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x08
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, SYS_ALL_V_I_R, MONITOR_ADDR, BROADCAST_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x09
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, MOD_N_V_I_R, MONITOR_ADDR, MOD0_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x0A
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, V_I_P_R, MONITOR_ADDR, MOD0_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x0C
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, E_V_I_R, MONITOR_ADDR, MOD0_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    can_main_rcv(CHAN_ZERO, can_acdc_rcv_buf);
    // cmd = 0x1A, open device
    snd_buf_temp[0] = 0;
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, OPEN_CLOSE_W, MONITOR_ADDR, BROADCAST_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    // cmd = 0x1A, close device
    snd_buf_temp[0] = 1;
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, OPEN_CLOSE_W, MONITOR_ADDR, BROADCAST_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
    // cmd = 0x1C
    g_can_cmd1C_data.can_cmd9_data_bit.MOD_N_V_S = 300000;//0xC9930400;
    g_can_cmd1C_data.can_cmd9_data_bit.MOD_N_I_S = 10000;//0x10270000;
    swap_endian(g_can_cmd1C_data.can_cmd9_data_bit.MOD_N_V_S, 4, &snd_buf_temp[0]);
    swap_endian(g_can_cmd1C_data.can_cmd9_data_bit.MOD_N_I_S, 4, &snd_buf_temp[4]);
    can_main_acdc_snd(CHAN_ZERO, SINGLE_MOD, MOD_V_I_W, MONITOR_ADDR, BROADCAST_ADDR, snd_buf_temp, &g_can_main_acdc);
    can_acdc_rcv(CHAN_ONE, can_acdc_rcv_buf);
}

void swap_endian(uint64_t src_data, uint8_t size, uint8_t* snd_buf)
{
    uint8_t i;
    uint8_t* ptr;

    ptr = (uint8_t*)&src_data;
    for(i = 1; i <= size; i++)
    {
        *(snd_buf + i - 1) = *(ptr + size - i);
    }
}

/* Slave Reception Data Handling */
void can_acdc_rcv(_Bool chan, uint8_t * rcv_buf)
{
    /* check if receive flag is set */
    if (TRUE == b_can_rx[chan])
    {
        /* Reset flag bit */
        b_can_rx[chan] = FALSE;
        APP_PRINT("\r\n CAN received the data : %s\r\n", &g_can_rx_frame[chan].data);
        memcpy(rcv_buf, (uint8_t*)&g_can_rx_frame[chan].data[0], g_can_rx_frame[chan].data_length_code);
        g_can_acdc_tx_id.can_acdc_id_bit.Dev_No = (g_can_rx_frame[chan].id >> 22) & 0x0F;
        g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No = (g_can_rx_frame[chan].id >> 16) & 0x3F;
        g_can_acdc_tx_id.can_acdc_id_bit.Dst_Addr = (g_can_rx_frame[chan].id >> 8) & 0xFF;
        g_can_acdc_tx_id.can_acdc_id_bit.Src_Addr = g_can_rx_frame[chan].id & 0xFF;

        // broadcast command
        if(g_can_acdc_tx_id.can_acdc_id_bit.Dst_Addr == BROADCAST_ADDR)
        {
            if(g_can_acdc_tx_id.can_acdc_id_bit.Dev_No == SINGLE_MOD)
            {
                switch(g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No){
                    case SYS_V_I_R:
                        break;
                    case MODULE_NO_R:
                        break;
                    case SYS_ALL_V_I_R:
                        g_can_cmd8_data.can_cmd8_data_bit.SYS_ALL_V = 0x400D0300;
                        g_can_cmd8_data.can_cmd8_data_bit.SYS_ALL_I = 0x88130000;
                        can_main_acdc_snd(chan, SINGLE_MOD, SYS_ALL_V_I_R, BROADCAST_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmd8_data.cmd_8_all, &g_can_acdc_main);
                        break;
                    case OPEN_CLOSE_W:
                        open_close_flag = g_can_rx_frame[chan].data[0];
                        break;
                    case MOD_V_I_W:
                        module_v = (float)((uint32_t)(g_can_rx_frame[chan].data[0] << 24) | (uint32_t)(g_can_rx_frame[chan].data[1] << 16) |
                                           (uint32_t)(g_can_rx_frame[chan].data[2] << 8) | g_can_rx_frame[chan].data[3]) / 1000;
                        module_i = (float)((uint32_t)(g_can_rx_frame[chan].data[4] << 24) | (uint32_t)(g_can_rx_frame[chan].data[5] << 16) |
                                           (uint32_t)(g_can_rx_frame[chan].data[6] << 8) | g_can_rx_frame[chan].data[7]) / 1000;
                        break;
                    default:
                        break;
                }
            }
            else if(g_can_acdc_tx_id.can_acdc_id_bit.Dev_No == GROUP_MOD)
            {
                switch(g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No){
                    case SYS_V_I_R:
                        break;
                    case MODULE_NO_R:
                        break;
                    default:
                        break;
                }
            }
        }
        else
        {
            // When device number is 0x0A, the destination address sent by monitor is the module address
            if((g_can_acdc_tx_id.can_acdc_id_bit.Dev_No == SINGLE_MOD) && (g_can_acdc_tx_id.can_acdc_id_bit.Dst_Addr == CUR_MOD_ADDR))
            {
                switch(g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No){
                    case MOD_G_STAT_R:
                        g_can_cmd4_data.can_cmd4_data_bit.mod_grp_no = 0;
                        g_can_cmd4_data.can_cmd4_data_bit.temperature = 0x10;
                        g_can_cmd4_data.can_cmd4_data_bit.mod_stat_2 = 0x80;
                        g_can_cmd4_data.can_cmd4_data_bit.mod_stat_1 = 0x41;
                        g_can_cmd4_data.can_cmd4_data_bit.mod_stat_0 = 0;
                        can_main_acdc_snd(chan, SINGLE_MOD, MOD_G_STAT_R, MOD0_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmd4_data.cmd_4_all, &g_can_acdc_main);
                        break;
                    case VAB_BC_CA_R:
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VAB_H = 0x0F;
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VAB_L = 0xB4;
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VBC_H = 0x0F;
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VBC_L = 0xA5;
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VCA_H = 0x0F;
                        g_can_cmd6_data.can_cmd6_data_bit.AC_VCA_L = 0xA0;
                        can_main_acdc_snd(chan, SINGLE_MOD, VAB_BC_CA_R, MOD0_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmd6_data.cmd_6_all, &g_can_acdc_main);
                        break;
                    case SYS_ALL_V_I_R:
                        break;
                    case MOD_N_V_I_R:
                        g_can_cmd9_data.can_cmd9_data_bit.MOD_N_V = 0x400D0300;
                        g_can_cmd9_data.can_cmd9_data_bit.MOD_N_I = 0x88130000;
                        can_main_acdc_snd(chan, SINGLE_MOD, MOD_N_V_I_R, MOD0_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmd9_data.cmd_9_all, &g_can_acdc_main);
                        break;
                    case V_I_P_R:
                        g_can_cmdA_data.can_cmdA_data_bit.MAX_V = 0xEE02;
                        g_can_cmdA_data.can_cmdA_data_bit.MIN_V = 0x6400;
                        g_can_cmdA_data.can_cmdA_data_bit.MAX_I = 0x0001;
                        g_can_cmdA_data.can_cmdA_data_bit.RATED_P = 0xDC05;
                        can_main_acdc_snd(chan, SINGLE_MOD, V_I_P_R, MOD0_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmdA_data.cmd_A_all, &g_can_acdc_main);
                        break;
                    case E_V_I_R:
                        g_can_cmdC_data.can_cmdC_data_bit.EXT_V = 0x5813;
                        g_can_cmdC_data.can_cmdC_data_bit.PERMIT_I = 0x6601;
                        can_main_acdc_snd(chan, SINGLE_MOD, E_V_I_R, MOD0_ADDR, MONITOR_ADDR, (uint8_t *)&g_can_cmdC_data.cmd_C_all, &g_can_acdc_main);
                        break;
                    default:
                        break;
                }
            }
            // When device number is 0x0B, the destination address sent by monitor is the group address
            else if((g_can_acdc_tx_id.can_acdc_id_bit.Dev_No == GROUP_MOD) && (g_can_acdc_tx_id.can_acdc_id_bit.Dst_Addr == CUR_GROUP_ADDR))
            {

            }
        }
    }
}

void can_main_rcv(_Bool chan, uint8_t * rcv_buf)
{
    /* check if receive flag is set */
    if (TRUE == b_can_rx[chan])
    {
        /* Reset flag bit */
        b_can_rx[chan] = FALSE;
        APP_PRINT("\r\n CAN received the data : %s\r\n", &g_can_rx_frame[chan].data);
        memcpy(rcv_buf, (uint8_t*)&g_can_rx_frame[chan].data[0], g_can_rx_frame[chan].data_length_code);
        g_can_acdc_rx_id.can_acdc_id_bit.Dev_No = (g_can_rx_frame[chan].id >> 22) & 0x0F;
        g_can_acdc_rx_id.can_acdc_id_bit.Cmd_No = (g_can_rx_frame[chan].id >> 16) & 0x3F;
        g_can_acdc_rx_id.can_acdc_id_bit.Dst_Addr = (g_can_rx_frame[chan].id >> 8) & 0xFF;
        g_can_acdc_rx_id.can_acdc_id_bit.Src_Addr = g_can_rx_frame[chan].id & 0xFF;

        if(g_can_acdc_rx_id.can_acdc_id_bit.Dst_Addr == MONITOR_ADDR)       // For this module
        {
            if(g_can_acdc_rx_id.can_acdc_id_bit.Dev_No == SINGLE_MOD)
            {
                switch(g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No){
                    case MOD_G_STAT_R:
                        mod_group_no = g_can_rx_frame[chan].data[2];
                        mod_temperature = g_can_rx_frame[chan].data[4];
                        mod_stat_table_2 = g_can_rx_frame[chan].data[5];
                        mod_stat_table_1 = g_can_rx_frame[chan].data[6];
                        mod_stat_table_0 = g_can_rx_frame[chan].data[7];
                        break;
                    case VAB_BC_CA_R:
                        ac_vab = (float)((uint16_t)(g_can_rx_frame[chan].data[0] << 8) | g_can_rx_frame[chan].data[1]) / 10;
                        ac_vbc = (float)((uint16_t)(g_can_rx_frame[chan].data[2] << 8) | g_can_rx_frame[chan].data[3]) / 10;
                        ac_vca = (float)((uint16_t)(g_can_rx_frame[chan].data[4] << 8) | g_can_rx_frame[chan].data[5]) / 10;
                        break;
                    case SYS_ALL_V_I_R:
                        system_total_v = ((uint32_t)g_can_rx_frame[chan].data[0] << 24 | (uint32_t)g_can_rx_frame[chan].data[1] << 16 |
                                    (uint32_t)g_can_rx_frame[chan].data[2] << 8 | (uint32_t)g_can_rx_frame[chan].data[3]) / 1000;
                        system_total_i = ((uint32_t)g_can_rx_frame[chan].data[4] << 24 | (uint32_t)g_can_rx_frame[chan].data[5] << 16 |
                                    (uint32_t)g_can_rx_frame[chan].data[6] << 8 | (uint32_t)g_can_rx_frame[chan].data[7]) / 1000;
                        break;
                    case MOD_N_V_I_R:
                        module_n_v = ((uint32_t)g_can_rx_frame[chan].data[0] << 24 | (uint32_t)g_can_rx_frame[chan].data[1] << 16 |
                                    (uint32_t)g_can_rx_frame[chan].data[2] << 8 | (uint32_t)g_can_rx_frame[chan].data[3]) / 1000;
                        module_n_i = ((uint32_t)g_can_rx_frame[chan].data[4] << 24 | (uint32_t)g_can_rx_frame[chan].data[5] << 16 |
                                    (uint32_t)g_can_rx_frame[chan].data[6] << 8 | (uint32_t)g_can_rx_frame[chan].data[7]) / 1000;
                        break;
                    case V_I_P_R:
                        maximal_v = (uint16_t)((uint16_t)g_can_rx_frame[chan].data[0] << 8 | g_can_rx_frame[chan].data[1]);
                        minimal_v = (uint16_t)((uint16_t)g_can_rx_frame[chan].data[2] << 8 | g_can_rx_frame[chan].data[3]);
                        maximal_i = (float)((uint16_t)g_can_rx_frame[chan].data[4] << 8 | g_can_rx_frame[chan].data[5]) / 10;
                        rated_power = ((uint32_t)g_can_rx_frame[chan].data[6] << 8 | g_can_rx_frame[chan].data[7]) * 10;
                        break;
                    case E_V_I_R:
                        ext_v = (float)((uint16_t)g_can_rx_frame[chan].data[0] << 8 | g_can_rx_frame[chan].data[1]) / 10;
                        permit_i = (float)((uint16_t)g_can_rx_frame[chan].data[2] << 8 | g_can_rx_frame[chan].data[3]) / 10;
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void can_main_acdc_snd(_Bool chan, uint8_t dev_no, uint8_t cmd_no, uint8_t src_addr, uint8_t dst_addr, uint8_t * snd_buf, can_instance_t const* p_can)
{
    fsp_err_t err = FSP_SUCCESS;
    uint32_t time_out = WAIT_TIME;                                      // time out

    g_can_acdc_tx_id.can_acdc_id_bit.Dev_No = dev_no;
    g_can_acdc_tx_id.can_acdc_id_bit.Cmd_No = cmd_no;
    g_can_acdc_tx_id.can_acdc_id_bit.Src_Addr = src_addr;
    g_can_acdc_tx_id.can_acdc_id_bit.Dst_Addr = dst_addr;
    g_can_tx_frame[chan].id = g_can_acdc_tx_id.can_acdc_id_all;
    g_can_tx_frame[chan].data_length_code = 8;
    memcpy((uint8_t*)&g_can_tx_frame[chan].data[0], snd_buf, 8);
    /* transmit the data from mail box #0 with tx_frame */
    err = R_CAN_Write(p_can->p_ctrl, CAN_MAILBOX_NUMBER_4, &g_can_tx_frame[chan]);
    /* Error trap */
    if (FSP_SUCCESS != err)
    {
        APP_ERR_PRINT("\r\n CAN Write API FAILED");
        can_deinit();
        APP_ERR_TRAP(err);
    }

    /* wait for transmit flag bit to set */
    while ((TRUE != b_can_tx[chan]) && (--time_out));
    if (RESET_VALUE == time_out)
    {
        APP_ERR_PRINT("CAN transmission failed due to timeout");
        APP_ERR_TRAP(TRUE);
    }
    /* Reset flag bit */
    b_can_tx[chan] = FALSE;
}
