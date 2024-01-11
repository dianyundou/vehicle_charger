/* generated vector source file - do not edit */
#include "bsp_api.h"
/* Do not build these data structures if no interrupts are currently allocated because IAR will have build errors. */
#if VECTOR_DATA_IRQ_COUNT > 0
        BSP_DONT_REMOVE const fsp_vector_t g_vector_table[BSP_ICU_VECTOR_MAX_ENTRIES] BSP_PLACE_IN_SECTION(BSP_SECTION_APPLICATION_VECTORS) =
        {
                        [0] = can_error_isr, /* CAN0 ERROR (Error interrupt) */
            [1] = can_rx_isr, /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [2] = can_tx_isr, /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [3] = can_rx_isr, /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [4] = can_tx_isr, /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [5] = can_error_isr, /* CAN1 ERROR (Error interrupt) */
            [6] = can_rx_isr, /* CAN1 MAILBOX RX (Reception complete interrupt) */
            [7] = can_tx_isr, /* CAN1 MAILBOX TX (Transmission complete interrupt) */
            [8] = can_rx_isr, /* CAN1 FIFO RX (Receive FIFO interrupt) */
            [9] = can_tx_isr, /* CAN1 FIFO TX (Transmit FIFO interrupt) */
            [10] = sci_uart_rxi_isr, /* SCI0 RXI (Receive data full) */
            [11] = sci_uart_txi_isr, /* SCI0 TXI (Transmit data empty) */
            [12] = sci_uart_tei_isr, /* SCI0 TEI (Transmit end) */
            [13] = sci_uart_eri_isr, /* SCI0 ERI (Receive error) */
            [14] = sci_uart_rxi_isr, /* SCI9 RXI (Received data full) */
            [15] = sci_uart_txi_isr, /* SCI9 TXI (Transmit data empty) */
            [16] = sci_uart_tei_isr, /* SCI9 TEI (Transmit end) */
            [17] = sci_uart_eri_isr, /* SCI9 ERI (Receive error) */
            [18] = sci_uart_rxi_isr, /* SCI2 RXI (Received data full) */
            [19] = sci_uart_txi_isr, /* SCI2 TXI (Transmit data empty) */
            [20] = sci_uart_tei_isr, /* SCI2 TEI (Transmit end) */
            [21] = sci_uart_eri_isr, /* SCI2 ERI (Receive error) */
            [22] = sci_uart_rxi_isr, /* SCI1 RXI (Received data full) */
            [23] = sci_uart_txi_isr, /* SCI1 TXI (Transmit data empty) */
            [24] = sci_uart_tei_isr, /* SCI1 TEI (Transmit end) */
            [25] = sci_uart_eri_isr, /* SCI1 ERI (Receive error) */
            [26] = gpt_counter_overflow_isr, /* GPT0 COUNTER OVERFLOW (Overflow) */
        };
        const bsp_interrupt_event_t g_interrupt_event_link_select[BSP_ICU_VECTOR_MAX_ENTRIES] =
        {
            [0] = BSP_PRV_IELS_ENUM(EVENT_CAN0_ERROR), /* CAN0 ERROR (Error interrupt) */
            [1] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_RX), /* CAN0 MAILBOX RX (Reception complete interrupt) */
            [2] = BSP_PRV_IELS_ENUM(EVENT_CAN0_MAILBOX_TX), /* CAN0 MAILBOX TX (Transmission complete interrupt) */
            [3] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_RX), /* CAN0 FIFO RX (Receive FIFO interrupt) */
            [4] = BSP_PRV_IELS_ENUM(EVENT_CAN0_FIFO_TX), /* CAN0 FIFO TX (Transmit FIFO interrupt) */
            [5] = BSP_PRV_IELS_ENUM(EVENT_CAN1_ERROR), /* CAN1 ERROR (Error interrupt) */
            [6] = BSP_PRV_IELS_ENUM(EVENT_CAN1_MAILBOX_RX), /* CAN1 MAILBOX RX (Reception complete interrupt) */
            [7] = BSP_PRV_IELS_ENUM(EVENT_CAN1_MAILBOX_TX), /* CAN1 MAILBOX TX (Transmission complete interrupt) */
            [8] = BSP_PRV_IELS_ENUM(EVENT_CAN1_FIFO_RX), /* CAN1 FIFO RX (Receive FIFO interrupt) */
            [9] = BSP_PRV_IELS_ENUM(EVENT_CAN1_FIFO_TX), /* CAN1 FIFO TX (Transmit FIFO interrupt) */
            [10] = BSP_PRV_IELS_ENUM(EVENT_SCI0_RXI), /* SCI0 RXI (Receive data full) */
            [11] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TXI), /* SCI0 TXI (Transmit data empty) */
            [12] = BSP_PRV_IELS_ENUM(EVENT_SCI0_TEI), /* SCI0 TEI (Transmit end) */
            [13] = BSP_PRV_IELS_ENUM(EVENT_SCI0_ERI), /* SCI0 ERI (Receive error) */
            [14] = BSP_PRV_IELS_ENUM(EVENT_SCI9_RXI), /* SCI9 RXI (Received data full) */
            [15] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TXI), /* SCI9 TXI (Transmit data empty) */
            [16] = BSP_PRV_IELS_ENUM(EVENT_SCI9_TEI), /* SCI9 TEI (Transmit end) */
            [17] = BSP_PRV_IELS_ENUM(EVENT_SCI9_ERI), /* SCI9 ERI (Receive error) */
            [18] = BSP_PRV_IELS_ENUM(EVENT_SCI2_RXI), /* SCI2 RXI (Received data full) */
            [19] = BSP_PRV_IELS_ENUM(EVENT_SCI2_TXI), /* SCI2 TXI (Transmit data empty) */
            [20] = BSP_PRV_IELS_ENUM(EVENT_SCI2_TEI), /* SCI2 TEI (Transmit end) */
            [21] = BSP_PRV_IELS_ENUM(EVENT_SCI2_ERI), /* SCI2 ERI (Receive error) */
            [22] = BSP_PRV_IELS_ENUM(EVENT_SCI1_RXI), /* SCI1 RXI (Received data full) */
            [23] = BSP_PRV_IELS_ENUM(EVENT_SCI1_TXI), /* SCI1 TXI (Transmit data empty) */
            [24] = BSP_PRV_IELS_ENUM(EVENT_SCI1_TEI), /* SCI1 TEI (Transmit end) */
            [25] = BSP_PRV_IELS_ENUM(EVENT_SCI1_ERI), /* SCI1 ERI (Receive error) */
            [26] = BSP_PRV_IELS_ENUM(EVENT_GPT0_COUNTER_OVERFLOW), /* GPT0 COUNTER OVERFLOW (Overflow) */
        };
        #endif
