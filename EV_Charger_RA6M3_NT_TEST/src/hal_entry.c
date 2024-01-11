#include "hal_data.h"
#include "main_acdc_can.h"
#include "user.h"
#include "modbus_app.h"
#include "mbport.h"
#include "mbm.h"
#include "common/mbportlayer.h"

FSP_CPP_HEADER
void R_BSP_WarmStart(bsp_warm_start_event_t event);
FSP_CPP_FOOTER

#define MBM_SERIAL_PORT           ( 0 )
#define MBM_SERIAL_BAUDRATE       ( 9600 )
#define MBM_PARITY                ( MB_PAR_NONE )


/*******************************************************************************************************************//**
 * main() is generated by the RA Configuration editor and is used to generate threads if an RTOS is used.  This function
 * is called by main() when no RTOS is used.
 **********************************************************************************************************************/
void hal_entry(void)
{
    /* TODO: add your own code here */
    // Initial all modules
    eMBErrorCode    eStatus;

    //R_IOPORT_PinWrite(&g_ioport_ctrl, BSP_IO_PORT_11_PIN_01, BSP_IO_LEVEL_HIGH); // Set RS-485 DE/RE control pin to high for transmission
    //Set RS-485 DE/RA control pin to low for reception

    if( MB_ENOERR ==
    ( eStatus = eMBMSerialInit( &xMBMMaster, MB_RTU, MBM_SERIAL_PORT, MBM_SERIAL_BAUDRATE, MBM_PARITY ) ) )
    {
        eStatus = MB_ENOERR;
    }

    touch_panel_init();
    card_reader_init();
    can_main_acdc_init();

    while(1)
    {
        can_main_acdc_routine();
        touch_panel_routine();
        card_swiping_test();            // Used for simulating swiping card test
        card_reader_routine();
        modbus_app_run();
        info_exchange();
    }

#if BSP_TZ_SECURE_BUILD
    /* Enter non-secure code */
    R_BSP_NonSecureEnter();
#endif
}

/*******************************************************************************************************************//**
 * This function is called at various points during the startup process.  This implementation uses the event that is
 * called right before main() to set up the pins.
 *
 * @param[in]  event    Where at in the start up process the code is currently at
 **********************************************************************************************************************/
void R_BSP_WarmStart(bsp_warm_start_event_t event)
{
    if (BSP_WARM_START_RESET == event)
    {
#if BSP_FEATURE_FLASH_LP_VERSION != 0

        /* Enable reading from data flash. */
        R_FACI_LP->DFLCTL = 1U;

        /* Would normally have to wait tDSTOP(6us) for data flash recovery. Placing the enable here, before clock and
         * C runtime initialization, should negate the need for a delay since the initialization will typically take more than 6us. */
#endif
    }

    if (BSP_WARM_START_POST_C == event)
    {
        /* C runtime environment and system clocks are setup. */

        /* Configure pins. */
        R_IOPORT_Open (&g_ioport_ctrl, &IOPORT_CFG_NAME);
    }
}

#if BSP_TZ_SECURE_BUILD

FSP_CPP_HEADER
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ();

/* Trustzone Secure Projects require at least one nonsecure callable function in order to build (Remove this if it is not required to build). */
BSP_CMSE_NONSECURE_ENTRY void template_nonsecure_callable ()
{

}
FSP_CPP_FOOTER

#endif
