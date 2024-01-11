/* 
 * MODBUS Library: Skeleton port
 * Copyright (c) 2008 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * $Id: mbportserial.c,v 1.1 2008-04-06 07:47:26 cwalter Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include <stdlib.h>

/* ----------------------- Platform includes --------------------------------*/
#include "mbport.h"
#include "uart_ep.h"
#include "hal_data.h"
#include "user.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "common/mbtypes.h"
#include "common/mbportlayer.h"
#include "common/mbframe.h"
#include "common/mbutils.h"

/* ----------------------- Defines ------------------------------------------*/
#define IDX_INVALID				( 255 )
#define UART_BAUDRATE_MIN		( 300 )
#define UART_BAUDRATE_MAX		( 115200 )

#define HDL_RESET( x ) do { \
	( x )->ubIdx = IDX_INVALID; \
	( x )->pbMBPTransmitterEmptyFN = NULL; \
	( x )->pvMBPReceiveFN = NULL; \
	( x )->xMBMHdl = MB_HDL_INVALID; \
} while( 0 );

/* ----------------------- Type definitions ---------------------------------*/
typedef struct
{
    UBYTE           ubIdx;
    pbMBPSerialTransmitterEmptyAPIV1CB pbMBPTransmitterEmptyFN;
    pvMBPSerialReceiverAPIV1CB pvMBPReceiveFN;
    xMBHandle       xMBMHdl;
} xSerialHandle;

/* ----------------------- Static variables ---------------------------------*/
STATIC xSerialHandle xSerialHdls[1];
STATIC BOOL     bIsInitalized = FALSE;

/* ----------------------- Static functions ---------------------------------*/

/* ----------------------- Start implementation -----------------------------*/

eMBErrorCode
eMBPSerialInit( xMBPSerialHandle * pxSerialHdl, UCHAR ucPort, ULONG ulBaudRate,
                UCHAR ucDataBits, eMBSerialParity eParity, UCHAR ucStopBits, xMBHandle xMBMHdl )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    UBYTE           ubIdx;

    MBP_ENTER_CRITICAL_SECTION(  );
    if( !bIsInitalized )
    {
        for( ubIdx = 0; ubIdx < MB_UTILS_NARRSIZE( xSerialHdls ); ubIdx++ )
        {
            HDL_RESET( &xSerialHdls[ubIdx] );
        }
    }

    if( NULL == pxSerialHdl )
    {
        eStatus = MB_EINVAL;
    }
    else if( ( 0 == ucPort ) && ( IDX_INVALID == xSerialHdls[0].ubIdx ) )
    {
        *pxSerialHdl = NULL;

        if( ( ulBaudRate >= UART_BAUDRATE_MIN ) && ( ulBaudRate <= UART_BAUDRATE_MAX ) && ( MB_HDL_INVALID != xMBMHdl ) )
        {
            /* TODO: Initialize the serial port here. */

            uart_config_set(eParity);
            uart_initialize();
            baud_setting_t uart_baud_setting;
            R_SCI_UART_BaudCalculate(ulBaudRate, true, 5000,  &uart_baud_setting);
            R_SCI_UART_BaudSet(&g_uart_485_ctrl, &uart_baud_setting);
            xSerialHdls[0].ubIdx = 0;
            xSerialHdls[0].xMBMHdl = xMBMHdl;
			*pxSerialHdl = &xSerialHdls[0];
            eStatus = MB_ENOERR;
        }
        else
        {
            eStatus = MB_EINVAL;
        }
    }
    else
    {
        eStatus = MB_ENORES;
    }
    MBP_EXIT_CRITICAL_SECTION(  );
    return eStatus;
}

eMBErrorCode
eMBPSerialClose( xMBPSerialHandle xSerialHdl )
{
    eMBErrorCode    eStatus = MB_EINVAL;
    xSerialHandle  *pxSerialIntHdl = xSerialHdl;

    MBP_ENTER_CRITICAL_SECTION(  );
    if( MB_IS_VALID_HDL( pxSerialIntHdl, xSerialHdls ) )
    {
        if( ( pxSerialIntHdl->pbMBPTransmitterEmptyFN == NULL ) && ( pxSerialIntHdl->pvMBPReceiveFN == NULL ) )
        {
            /* TODO: Close the serial port here. */
            deinit_uart();
            eStatus = MB_ENOERR;
        }
        else
        {
            eStatus = MB_EAGAIN;
        }
    }
    MBP_EXIT_CRITICAL_SECTION(  );
    return eStatus;
}

eMBErrorCode
eMBPSerialTxEnable( xMBPSerialHandle xSerialHdl, pbMBPSerialTransmitterEmptyCB pbMBPTransmitterEmptyFN )
{
    eMBErrorCode    eStatus = MB_EINVAL;
    xSerialHandle  *pxSerialIntHdl = xSerialHdl;

    MBP_ENTER_CRITICAL_SECTION(  );
    if( MB_IS_VALID_HDL( pxSerialIntHdl, xSerialHdls ) )
    {
        eStatus = MB_ENOERR;
        if( NULL != pbMBPTransmitterEmptyFN )
        {
            MBP_ASSERT( NULL == pxSerialIntHdl->pbMBPTransmitterEmptyFN );
            pxSerialIntHdl->pbMBPTransmitterEmptyFN = pbMBPTransmitterEmptyFN;
            BOOL            bHasMoreData = TRUE;
            UBYTE           ubTxByte;
            if( NULL != xSerialHdls[0].pbMBPTransmitterEmptyFN )
            {
                bHasMoreData = xSerialHdls[0].pbMBPTransmitterEmptyFN( xSerialHdls[0].xMBMHdl, &ubTxByte );
            }
            if( !bHasMoreData )
            {
                xSerialHdls[0].pbMBPTransmitterEmptyFN = NULL;
                uart_te_disable();
                /* TODO: Disable the transmitter. */
            }
            else
            {
                /* TODO: Place byte ubTxByte in the UART data register. */
                R_SCI_UART_Write(&g_uart_485_ctrl, &ubTxByte, 1);
            }
            //uart_te_enable();
            /* TODO: Enable the transmitter. */
        }
        else
        {
            pxSerialIntHdl->pbMBPTransmitterEmptyFN = NULL;
            uart_te_disable();
            /* TODO: Disable the transmitter. Make sure that all characters have been
             * transmitted in case you do any buffering internally.
             */
        }
    }
    MBP_EXIT_CRITICAL_SECTION(  );
    return eStatus;
}

eMBErrorCode
eMBPSerialRxEnable( xMBPSerialHandle xSerialHdl, pvMBPSerialReceiverCB pvMBPReceiveFN )
{
    eMBErrorCode    eStatus = MB_EINVAL;
    xSerialHandle  *pxSerialIntHdl = xSerialHdl;

    MBP_ENTER_CRITICAL_SECTION(  );
    if( MB_IS_VALID_HDL( pxSerialIntHdl, xSerialHdls ) )
    {
        eStatus = MB_ENOERR;
        if( NULL != pvMBPReceiveFN )
        {
            MBP_ASSERT( NULL == pxSerialIntHdl->pvMBPReceiveFN );
            pxSerialIntHdl->pvMBPReceiveFN = pvMBPReceiveFN;
            uart_re_enable();
            /* TODO: Enable the receiver. */
        }
        else
        {
            pxSerialIntHdl->pvMBPReceiveFN = NULL;
            uart_re_disable();
            /* TODO: Disable the receiver. */
        }
    }
    MBP_EXIT_CRITICAL_SECTION(  );
    return eStatus;
}

STATIC void 
prrvUSARTTxISR( void )
{
    BOOL            bHasMoreData = TRUE;
    UBYTE           ubTxByte;

    if( NULL != xSerialHdls[0].pbMBPTransmitterEmptyFN )
    {
        bHasMoreData = xSerialHdls[0].pbMBPTransmitterEmptyFN( xSerialHdls[0].xMBMHdl, &ubTxByte );
    }
    if( !bHasMoreData )
    {
        xSerialHdls[0].pbMBPTransmitterEmptyFN = NULL;
        /* TODO: Disable the transmitter. */
    }
    else
    {
        /* TODO: Place byte ubTxByte in the UART data register. */
        R_SCI_UART_Write(&g_uart_485_ctrl, &ubTxByte, 1);
    }
}

STATIC void 
prrvUSARTRxISR( void )
{
    UBYTE           ubUDR = 0; /* TODO: Get byte from UART. */;

    MBP_ASSERT( IDX_INVALID != xSerialHdls[0].ubIdx );
    if( NULL != xSerialHdls[0].pvMBPReceiveFN )
    {
        xSerialHdls[0].pvMBPReceiveFN( xSerialHdls[0].xMBMHdl, ubUDR );
    }
}

/*****************************************************************************************************************
 *  @brief      UART user callback
 *  @param[in]  p_args
 *  @retval     None
 ****************************************************************************************************************/
void user_uart485_callback(uart_callback_args_t *p_args)
{
    /* Logged the event in global variable */
    if(UART_EVENT_RX_CHAR == p_args->event)
    {
        UBYTE           ubUDR = 0; /* TODO: Get byte from UART. */;
        ubUDR = p_args->data;
        MBP_ASSERT( IDX_INVALID != xSerialHdls[0].ubIdx );
        if( NULL != xSerialHdls[0].pvMBPReceiveFN )
        {
            xSerialHdls[0].pvMBPReceiveFN( xSerialHdls[0].xMBMHdl, ubUDR );
        }
    }
    else if(UART_EVENT_TX_DATA_EMPTY == p_args->event)
    {


    }
    else if(UART_EVENT_TX_COMPLETE == p_args->event)
    {
        BOOL            bHasMoreData = TRUE;
        UBYTE           ubTxByte;

        if( NULL != xSerialHdls[0].pbMBPTransmitterEmptyFN )
        {
            bHasMoreData = xSerialHdls[0].pbMBPTransmitterEmptyFN( xSerialHdls[0].xMBMHdl, &ubTxByte );
        }
        if( !bHasMoreData )
        {
            xSerialHdls[0].pbMBPTransmitterEmptyFN = NULL;
            uart_te_disable();
            /* TODO: Disable the transmitter. */
        }
        else
        {
            /* TODO: Place byte ubTxByte in the UART data register. */
            //SCI_UART_Write (&g_uart_485_ctrl, &ubTxByte);
            R_SCI_UART_Write(&g_uart_485_ctrl, &ubTxByte, 1);
        }
    }

}
