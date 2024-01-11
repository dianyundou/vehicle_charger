/*
 * secc_can.h
 *
 *  Created on: Oct 30, 2023
 *      Author: a5059731
 */

#ifndef MAIN_ACDC_CAN_H_
#define MAIN_ACDC_CAN_H_

#include "hal_data.h"

//#define SECC_EVCC

#define CAN_MAILBOX_NUMBER_0            (0U)               //mail box number
#define CAN_MAILBOX_NUMBER_4            (4U)

#define WAIT_TIME                       (500000U)            //wait time value

#define CHAN_NUM        (2U)
#define CHAN_ZERO       (0U)
#define CHAN_ONE        (1U)

/* Address of SECC and EVCC */
#define CAN_SECC_ID     (0x56)      // SECC address
#define CAN_EVCC_ID     (0xF4)      // EVCC address

/* PGN Command */
#define CHM     0
#define BHM     1

typedef union st_can_id
{
    uint32_t    can_id_all;
    struct
    {
        unsigned char : 3;
        unsigned char Pri_Bit: 3;
        _Bool EDP: 1;
        _Bool DP: 1;
        unsigned char PF: 8;
        unsigned char PS: 8;
        unsigned char SA: 8;
    }can_id_bit;
}can_id;

typedef struct st_can_data
{
    uint32_t    can_id;
    uint8_t     can_dlc;
    uint16_t    wait_time;
}can_data_t;

/* ACDC control definition */
// Error Code
#define NORMAL          0x00
#define CMD_NO_ERR      0x02
#define DAT_INFO_ERR    0x03
#define ADDR_INVALID    0x04
#define DURING_STARTUP  0x07

// Device Number
#define SINGLE_MOD      0x0A
#define GROUP_MOD       0x0B

// Command Number
#define SYS_V_I_R       0x01
#define MODULE_NO_R     0x02
#define MOD_V_I_R       0x03
#define MOD_G_STAT_R    0x04
#define VAB_BC_CA_R     0x06
#define SYS_ALL_V_I_R   0x08
#define MOD_N_V_I_R     0x09
#define V_I_P_R         0x0A
#define BAR_CODE_R      0x0B
#define E_V_I_R         0x0C
#define WALKIN_W        0x13
#define GREEN_LIGHT_W   0x14
#define GROUP_NO_W      0x16
#define HIBERNATE_W     0x19
#define OPEN_CLOSE_W    0x1A
#define MOD_V_IALL_W    0x1B
#define MOD_V_I_W       0x1C
#define ADDR_MODE       0x1F

// Address
#define MONITOR_ADDR    0xF0
#define MOD0_ADDR       0x00
#define BROADCAST_ADDR  0x3F
#define CUR_MOD_ADDR    0x00
#define CUR_GROUP_ADDR  0x00

// Module N Status Table 2
#define PFC_CLOSE       0x80
#define IN_OV_W         0x40
#define IN_UV_W         0x20
#define TRI_IN_UNB_W    0x10
#define TRI_IN_MIS_W    0x08
#define MOD_UNEVEN_FLOW 0x04
#define REP_MOD_ID      0x02
#define MOD_LIMIT_P     0x01
// Module N Status Table 1
#define MOD_COM_INT_W   0x80
#define WALK_IN_EN      0x40
#define OUT_OV_W        0x20
#define OT_W            0x10
#define FAN_FAULT_W     0x08
#define MOD_PROT_W      0x04
#define MOD_FAULT_W     0x02
#define MOD_DC_OFF      0x01
// Module N Status Table 0
#define MOD_DISCHG_E    0x20
#define MOD_HIBERNATE   0x10
#define IN_OR_BUS_E     0x08
#define MOD_COMM_E      0x04
#define OUT_SHORT       0x01

typedef union st_can_acdc_id
{
    uint32_t    can_acdc_id_all;
    struct
    {
        uint32_t Src_Addr:  8;
        uint32_t Dst_Addr:  8;
        uint32_t Cmd_No:    6;
        uint32_t Dev_No:    4;
        uint32_t Err_Bit:   3;
        uint32_t :          3;
    }can_acdc_id_bit;
}can_acdc_id;

typedef union st_cmd4_dat
{
    uint64_t    cmd_4_all;
    struct{
        uint64_t :              8;
        uint64_t :              8;
        uint64_t mod_grp_no:    8;
        uint64_t :              8;
        uint64_t temperature:   8;
        uint64_t mod_stat_2:    8;
        uint64_t mod_stat_1:    8;
        uint64_t mod_stat_0:    8;
    }can_cmd4_data_bit;
}can_cmd4_dat;

typedef union st_cmd6_dat
{
    uint64_t    cmd_6_all;
    struct{
        uint64_t AC_VAB_H:      8;
        uint64_t AC_VAB_L:      8;
        uint64_t AC_VBC_H:      8;
        uint64_t AC_VBC_L:      8;
        uint64_t AC_VCA_H:      8;
        uint64_t AC_VCA_L:      8;
        uint64_t :              16;
    }can_cmd6_data_bit;
}can_cmd6_dat;

typedef union st_cmd8_dat
{
    uint64_t    cmd_8_all;
    struct{
        uint64_t SYS_ALL_V:     32;
        uint64_t SYS_ALL_I:     32;
    }can_cmd8_data_bit;
}can_cmd8_dat;

typedef union st_cmd9_dat
{
    uint64_t    cmd_9_all;
    struct{
        uint64_t MOD_N_V:       32;
        uint64_t MOD_N_I:       32;
    }can_cmd9_data_bit;
}can_cmd9_dat;

typedef union st_cmdA_dat
{
    uint64_t    cmd_A_all;
    struct{
        uint64_t MAX_V:         16;
        uint64_t MIN_V:         16;
        uint64_t MAX_I:         16;
        uint64_t RATED_P:       16;
    }can_cmdA_data_bit;
}can_cmdA_dat;

typedef union st_cmdC_dat
{
    uint64_t    cmd_C_all;
    struct{
        uint64_t EXT_V:         16;
        uint64_t PERMIT_I:      16;
        uint64_t :              32;
    }can_cmdC_data_bit;
}can_cmdC_dat;

typedef union st_cmd1C_dat
{
    uint64_t    cmd_1C_all;
    struct{
        uint64_t MOD_N_V_S:     32;
        uint64_t MOD_N_I_S:     32;
    }can_cmd9_data_bit;
}can_cmd1C_dat;

void can_secc_evcc_init(void);
void can_secc_evcc_connect(void);
void can_deinit(void);
void can_snd(_Bool chan, uint8_t cmd_no, uint8_t * snd_buf, can_instance_t const* p_can);
void can_rcv(_Bool chan, uint8_t * rcv_buf);
/* Can communication between main controller and acdc module  */
void can_main_acdc_init(void);
void can_main_acdc_routine(void);
void can_main_acdc_snd(_Bool chan, uint8_t dev_no, uint8_t cmd_no, uint8_t src_addr, uint8_t dst_addr, uint8_t * snd_buf, can_instance_t const* p_can);
void can_acdc_rcv(_Bool chan, uint8_t * rcv_buf);
void can_main_rcv(_Bool chan, uint8_t * rcv_buf);
void swap_endian(uint64_t src_buf, uint8_t size, uint8_t* snd_buf);

#endif /* MAIN_ACDC_CAN_H_ */
