/* generated vector header file - do not edit */
#ifndef VECTOR_DATA_H
#define VECTOR_DATA_H
#ifdef __cplusplus
        extern "C" {
        #endif
/* Number of interrupts allocated */
#ifndef VECTOR_DATA_IRQ_COUNT
#define VECTOR_DATA_IRQ_COUNT    (27)
#endif
/* ISR prototypes */
void can_error_isr(void);
void can_rx_isr(void);
void can_tx_isr(void);
void sci_uart_rxi_isr(void);
void sci_uart_txi_isr(void);
void sci_uart_tei_isr(void);
void sci_uart_eri_isr(void);
void gpt_counter_overflow_isr(void);

/* Vector table allocations */
#define VECTOR_NUMBER_CAN0_ERROR ((IRQn_Type) 0) /* CAN0 ERROR (Error interrupt) */
#define CAN0_ERROR_IRQn          ((IRQn_Type) 0) /* CAN0 ERROR (Error interrupt) */
#define VECTOR_NUMBER_CAN0_MAILBOX_RX ((IRQn_Type) 1) /* CAN0 MAILBOX RX (Reception complete interrupt) */
#define CAN0_MAILBOX_RX_IRQn          ((IRQn_Type) 1) /* CAN0 MAILBOX RX (Reception complete interrupt) */
#define VECTOR_NUMBER_CAN0_MAILBOX_TX ((IRQn_Type) 2) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
#define CAN0_MAILBOX_TX_IRQn          ((IRQn_Type) 2) /* CAN0 MAILBOX TX (Transmission complete interrupt) */
#define VECTOR_NUMBER_CAN0_FIFO_RX ((IRQn_Type) 3) /* CAN0 FIFO RX (Receive FIFO interrupt) */
#define CAN0_FIFO_RX_IRQn          ((IRQn_Type) 3) /* CAN0 FIFO RX (Receive FIFO interrupt) */
#define VECTOR_NUMBER_CAN0_FIFO_TX ((IRQn_Type) 4) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
#define CAN0_FIFO_TX_IRQn          ((IRQn_Type) 4) /* CAN0 FIFO TX (Transmit FIFO interrupt) */
#define VECTOR_NUMBER_CAN1_ERROR ((IRQn_Type) 5) /* CAN1 ERROR (Error interrupt) */
#define CAN1_ERROR_IRQn          ((IRQn_Type) 5) /* CAN1 ERROR (Error interrupt) */
#define VECTOR_NUMBER_CAN1_MAILBOX_RX ((IRQn_Type) 6) /* CAN1 MAILBOX RX (Reception complete interrupt) */
#define CAN1_MAILBOX_RX_IRQn          ((IRQn_Type) 6) /* CAN1 MAILBOX RX (Reception complete interrupt) */
#define VECTOR_NUMBER_CAN1_MAILBOX_TX ((IRQn_Type) 7) /* CAN1 MAILBOX TX (Transmission complete interrupt) */
#define CAN1_MAILBOX_TX_IRQn          ((IRQn_Type) 7) /* CAN1 MAILBOX TX (Transmission complete interrupt) */
#define VECTOR_NUMBER_CAN1_FIFO_RX ((IRQn_Type) 8) /* CAN1 FIFO RX (Receive FIFO interrupt) */
#define CAN1_FIFO_RX_IRQn          ((IRQn_Type) 8) /* CAN1 FIFO RX (Receive FIFO interrupt) */
#define VECTOR_NUMBER_CAN1_FIFO_TX ((IRQn_Type) 9) /* CAN1 FIFO TX (Transmit FIFO interrupt) */
#define CAN1_FIFO_TX_IRQn          ((IRQn_Type) 9) /* CAN1 FIFO TX (Transmit FIFO interrupt) */
#define VECTOR_NUMBER_SCI0_RXI ((IRQn_Type) 10) /* SCI0 RXI (Receive data full) */
#define SCI0_RXI_IRQn          ((IRQn_Type) 10) /* SCI0 RXI (Receive data full) */
#define VECTOR_NUMBER_SCI0_TXI ((IRQn_Type) 11) /* SCI0 TXI (Transmit data empty) */
#define SCI0_TXI_IRQn          ((IRQn_Type) 11) /* SCI0 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI0_TEI ((IRQn_Type) 12) /* SCI0 TEI (Transmit end) */
#define SCI0_TEI_IRQn          ((IRQn_Type) 12) /* SCI0 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI0_ERI ((IRQn_Type) 13) /* SCI0 ERI (Receive error) */
#define SCI0_ERI_IRQn          ((IRQn_Type) 13) /* SCI0 ERI (Receive error) */
#define VECTOR_NUMBER_SCI9_RXI ((IRQn_Type) 14) /* SCI9 RXI (Received data full) */
#define SCI9_RXI_IRQn          ((IRQn_Type) 14) /* SCI9 RXI (Received data full) */
#define VECTOR_NUMBER_SCI9_TXI ((IRQn_Type) 15) /* SCI9 TXI (Transmit data empty) */
#define SCI9_TXI_IRQn          ((IRQn_Type) 15) /* SCI9 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI9_TEI ((IRQn_Type) 16) /* SCI9 TEI (Transmit end) */
#define SCI9_TEI_IRQn          ((IRQn_Type) 16) /* SCI9 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI9_ERI ((IRQn_Type) 17) /* SCI9 ERI (Receive error) */
#define SCI9_ERI_IRQn          ((IRQn_Type) 17) /* SCI9 ERI (Receive error) */
#define VECTOR_NUMBER_SCI2_RXI ((IRQn_Type) 18) /* SCI2 RXI (Received data full) */
#define SCI2_RXI_IRQn          ((IRQn_Type) 18) /* SCI2 RXI (Received data full) */
#define VECTOR_NUMBER_SCI2_TXI ((IRQn_Type) 19) /* SCI2 TXI (Transmit data empty) */
#define SCI2_TXI_IRQn          ((IRQn_Type) 19) /* SCI2 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI2_TEI ((IRQn_Type) 20) /* SCI2 TEI (Transmit end) */
#define SCI2_TEI_IRQn          ((IRQn_Type) 20) /* SCI2 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI2_ERI ((IRQn_Type) 21) /* SCI2 ERI (Receive error) */
#define SCI2_ERI_IRQn          ((IRQn_Type) 21) /* SCI2 ERI (Receive error) */
#define VECTOR_NUMBER_SCI1_RXI ((IRQn_Type) 22) /* SCI1 RXI (Received data full) */
#define SCI1_RXI_IRQn          ((IRQn_Type) 22) /* SCI1 RXI (Received data full) */
#define VECTOR_NUMBER_SCI1_TXI ((IRQn_Type) 23) /* SCI1 TXI (Transmit data empty) */
#define SCI1_TXI_IRQn          ((IRQn_Type) 23) /* SCI1 TXI (Transmit data empty) */
#define VECTOR_NUMBER_SCI1_TEI ((IRQn_Type) 24) /* SCI1 TEI (Transmit end) */
#define SCI1_TEI_IRQn          ((IRQn_Type) 24) /* SCI1 TEI (Transmit end) */
#define VECTOR_NUMBER_SCI1_ERI ((IRQn_Type) 25) /* SCI1 ERI (Receive error) */
#define SCI1_ERI_IRQn          ((IRQn_Type) 25) /* SCI1 ERI (Receive error) */
#define VECTOR_NUMBER_GPT0_COUNTER_OVERFLOW ((IRQn_Type) 26) /* GPT0 COUNTER OVERFLOW (Overflow) */
#define GPT0_COUNTER_OVERFLOW_IRQn          ((IRQn_Type) 26) /* GPT0 COUNTER OVERFLOW (Overflow) */
#ifdef __cplusplus
        }
        #endif
#endif /* VECTOR_DATA_H */
