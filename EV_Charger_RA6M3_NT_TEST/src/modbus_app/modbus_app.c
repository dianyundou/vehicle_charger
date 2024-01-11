/***********************************************************************************************************************
 * File Name    : modbus_app.c
 * Description  : Contains modbus functions definition.
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

#include "common_utils.h"
#include "modbus_app.h"
#include "uart_ep.h"

modbus_data_t modbus_data1[MODBUS_DATA1_LEN] = \
{

    {en_read,  "", 0x0011, 0},
    {en_read,  "", 0x0012, 0},
    {en_read,  "", 0x0013, 0},
    {en_read,  "", 0x0014, 0},
    {en_read,  "", 0x0015, 0},
    {en_read,  "", 0x0016, 0},
    {en_read,  "", 0x0017, 0},
    {en_read,  "", 0x0018, 0},
    {en_read,  "", 0x0019, 0},
    {en_write, "", 0x0102, 0x01},
    {en_write, "", 0x0103, 0x02},
    {en_write, "", 0x0105, 0x03},

};

modbus_data2_t modbus_data2[MODBUS_DATA2_LEN] = \
{

    {en_read,  "", 0x03E9, 0},
    {en_read,  "", 0x03EB, 0},
    {en_read,  "", 0x03ED, 0},
    {en_read,  "", 0x03EF, 0},
    {en_read,  "", 0x03F1, 0},

};

insulation_detector_t insulation_detector;
dc_meter_t dc_meter;
xMBHandle       xMBMMaster;

void info_exchange(void)
{
    insulation_detector.bus_insulation_resistor = modbus_data1[0].value;
    insulation_detector.v_bus = modbus_data1[1].value;
    insulation_detector.run_status = modbus_data1[2].value;
    insulation_detector.v_bus_plus_resistor = modbus_data1[3].value;
    insulation_detector.v_bus_minus_resistor = modbus_data1[4].value;
    insulation_detector.v_bus_plus_alarm_threshold = modbus_data1[5].value;
    insulation_detector.v_bus_minus_alarm_threshold = modbus_data1[6].value;
    insulation_detector.v_bus_alarm_threshold = modbus_data1[7].value;
    insulation_detector.insulation_monitor_switch = modbus_data1[8].value;

    modbus_data1[9].value = insulation_detector.v_bus_plus_alarm_threshold_set;
    modbus_data1[10].value = insulation_detector.v_bus_minus_alarm_threshold_set;
    modbus_data1[11].value = insulation_detector.insulation_monitor_switch_set;

    dc_meter.voltage_rms = modbus_data2[0].value;
    dc_meter.current_rms = modbus_data2[1].value;
    dc_meter.power_rms = modbus_data2[2].value;
    dc_meter.plus_active_energy = modbus_data2[3].value;
    dc_meter.minus_active_energy = modbus_data2[4].value;

}

void modbus_app_run(void)
{
    eMBErrorCode    eStatus;
    eMBErrorCode    eStatus2;
    UBYTE           ubIdx;
    for( ubIdx = 9; ubIdx < 12; ubIdx++ )
    {
        /* Write an incrementing counter to register address 0. */
        if( MB_ENOERR != ( eStatus2 = eMBMWriteSingleRegister( xMBMMaster, 1, modbus_data1[ubIdx].address, modbus_data1[ubIdx].value) ) )
        {
            R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_11_PIN_03, BSP_IO_LEVEL_HIGH);
            eStatus = eStatus2;
        }
    }

    for( ubIdx = 0; ubIdx < 9; ubIdx++ )
    {
        if( MB_ENOERR != ( eStatus2 = eMBMReadHoldingRegisters( xMBMMaster, 1, modbus_data1[ubIdx].address, 1, &modbus_data1[ubIdx].value ) ) )
        {
            eStatus = eStatus2;
        }
    }


    for( ubIdx = 0; ubIdx < 5; ubIdx++ )
    {
        if( MB_ENOERR != ( eStatus2 = eMBMReadHoldingRegisters( xMBMMaster, 2, modbus_data2[ubIdx].address, 2, (uint16_t *)&modbus_data2[ubIdx].value ) ) )
        {
            eStatus = eStatus2;
        }
    }
}

