/***********************************************************************************************************************
 * File Name    : modbus_app.h
 * Description  : Contains function declaration and macros of modbus_app.c.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
 * other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
 * applicable laws, including copyright laws.
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
 * SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the
 * following link:
 * http://www.renesas.com/disclaimer
 *
 * Copyright (C) 2020 Renesas Electronics Corporation. All rights reserved.
 ***********************************************************************************************************************/

#ifndef MODBUS_APP_H_
#define MODBUS_APP_H_


#include "mbport.h"
#include "mbm.h"

/* Board specific macros for conditional compilation */
#define  MODBUS_DATA1_LEN      (12)
#define  MODBUS_DATA2_LEN      (5)

typedef enum
{
    en_read,
    en_write

}read_write_state_t;

typedef struct{

    read_write_state_t read_write_state;
    char name[10];
    uint16_t address;
    uint16_t value;

}modbus_data_t;

typedef struct{

    read_write_state_t read_write_state;
    char name[10];
    uint16_t address;
    uint32_t value;

}modbus_data2_t;


typedef struct {

    uint16_t bus_insulation_resistor;
    uint16_t v_bus;
    uint16_t run_status;
    uint16_t v_bus_plus_resistor;
    uint16_t v_bus_minus_resistor;
    uint16_t v_bus_plus_alarm_threshold;
    uint16_t v_bus_minus_alarm_threshold;
    uint16_t v_bus_alarm_threshold;
    uint16_t insulation_monitor_switch;
    uint16_t v_bus_plus_alarm_threshold_set;
    uint16_t v_bus_minus_alarm_threshold_set;
    uint16_t insulation_monitor_switch_set;

}insulation_detector_t;

typedef struct {

    uint32_t voltage_rms;
    uint32_t current_rms;
    uint32_t power_rms;
    uint32_t plus_active_energy;
    uint32_t minus_active_energy;

}dc_meter_t;

extern modbus_data_t modbus_data1[MODBUS_DATA1_LEN];
extern modbus_data2_t modbus_data2[MODBUS_DATA2_LEN];
extern insulation_detector_t insulation_detector;
extern dc_meter_t dc_meter;
extern xMBHandle  xMBMMaster;

void info_exchange(void);
void modbus_app_run(void);
#endif /* MODBUS_APP_H_ */
