#include "uart.h"

/*******************************************************************************
 *                               Global Variables                                    *
 *******************************************************************************/

static volatile void (*g_UART_Recieve_Complete_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_UART_Transmit_Complete_callBackPtr)(void) = NULL_PTR;
static volatile void (*g_UART_DataReg_Empty_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                              ISRs                                                    *
 *******************************************************************************/

ISR(USART_RXC_vect)
{
    if (g_UART_Recieve_Complete_callBackPtr != NULL_PTR)
    {
        (*g_UART_Recieve_Complete_callBackPtr)();
    }
}
ISR(USART_TXC_vect)
{
    if (g_UART_Transmit_Complete_callBackPtr != NULL_PTR)
    {
        (*g_UART_Transmit_Complete_callBackPtr)();
    }
}
ISR(USART_UDRE_vect)
{
    if (g_UART_DataReg_Empty_callBackPtr != NULL_PTR)
    {
        (*g_UART_DataReg_Empty_callBackPtr)();
    }
}

/*******************************************************************************
 *                      Function Definitions                                    *
 *******************************************************************************/

void UART_init(UART_ConfigType *cfg_ptr)
{
    uint16 baud = (((F_CPU) / (8UL * cfg_ptr->baud_rate)) - 1);
    /*Description: UCSRA (uart control & status reg.)
        U2x =  1 for double transmission speed (8 Divisor instead of 16)
*/
    UCSRA = (1 << U2X);
    /* Description: UCSRB
RXCIE   = 0 RX COMPLETE INTERRUPT ENABLE BIT (DISABLE)
TXCIE   = 0 TX COMPLETE  INTERRUPT ENABLE BIT (DISABLE)
UDRIE   = 0 DATA REG. EMPTY INTERRUPT ENABLE BIT (DISABLE)
RXEN    = second bit of conn_direction to turn on transmitter
TXEN    = first bit of conn_direction to turn on reciever
UCSZ2   = c_size bit-3 
*/
    UCSRB = (cfg_ptr->conn_direction << 3) | (cfg_ptr->c_size & (0x04));

    /*Description: UCSRC
URSEL   = 1   WRITE TO UCSRC BIT
UMSEL   = mode SELECT
UPM1:0  = 00 DISABLE PARITY CHECKS
USBS    = 0 1-STOP-BIT SELECT
UPCOL   = CLOCK polarity MODE
UCSZ1:0 = first 2-bitts in character size;
*/
    UCSRC = (1 << URSEL) | (cfg_ptr->mode << 6) | ((cfg_ptr->c_size & 0x03) << 1) | cfg_ptr->clock_polarity;

    /*Description: UBBR
URSEL   = 0 TO WRITE TO UBBR
UBBR = BAUD RATE
*/
    UBRRH = (baud >> 8);
    UBRRL = (baud);
}

/*data is uint16 in case of 9-bit mode*/
void UART_sendData(uint16 data)
{
    /*Wait untill data transmit buffer is empty */
    while (BIT_IS_CLEAR(UCSRA, UDRE))
        ;
    /*in case of 9-bit uart insert 9nth bit into ucsrb*/
    if (BIT_IS_SET(UCSRB, UCSZ2))
    {
        UCSRB = (UCSRB & (~0X01)) | (data & 0x100);
    }
    /*insert REST of data into UDR buffer to transmit*/
    UDR = data;
}

uint16 UART_recieveData(void)
{
    /*Wait untill recieve is complete*/
    while (BIT_IS_CLEAR(UCSRA, RXC))
        ;
    /*in case of 9-bit uart */
    if (BIT_IS_SET(UCSRB, UCSZ2))
    {
        /*return recieved data in data register plus 9nth bit*/
        return (UDR | ((UCSRB & 0X02) << 7));
    }
    else
    {
        /*return recieved data in data register*/
        return UDR;
    }
}

void UART_sendString(const uint8 *string)
{
    /*send each character of our string until we reach the null terminator*/
    while (*string != '\0')
    {
        UART_sendData(*string);
        string++;
    }
}
void UART_recieveString(uint8 *string)
{
    /*recieve each character string until we find a '#' 
    then replace it with null terminator*/

    uint16 i = 0;
    string[i] = UART_recieveData();
    while (string[i] != '#')
    {
        i++;
        string[i] = UART_recieveData();
    }
    string[i] = '\0';
}

void UART_setRecieveCompleteCallback(void (*f_ptr)(void))
{
    /*set global pointer of the recieve interrupt functin in isr*/
    g_UART_Recieve_Complete_callBackPtr = f_ptr;
}
void UART_setTransmitCompleteCallback(void (*f_ptr)(void))
{
    /*set global pointer of the transmit interrupt functin in isr*/

    g_UART_Transmit_Complete_callBackPtr = f_ptr;
}
void UART_setDataEmptyCallback(void (*f_ptr)(void))
{

    /*set global pointer of the data empty interrupt functin in isr*/
    g_UART_DataReg_Empty_callBackPtr = f_ptr;
}
void UART_enableRecieveCompleteInterrupt(void)
{
    /*set interrupt enable bit for recieve complete*/
    SET_BIT(UCSRB, RXCIE);
}
void UART_enableTransmitCompleteInterrupt(void)
{

    /*set interrupt enable bit for transfer complete*/
    SET_BIT(UCSRB, TXCIE);
}
void UART_enableDataEmptyInterrupt(void)
{

    /*set interrupt enable bit for data empty*/
    SET_BIT(UCSRB, UDRIE);
}
void UART_disableRecieveCompleteInterrupt(void)
{
    /*clear interrupt enable bit for recieve complete*/
    CLEAR_BIT(UCSRB, RXCIE);
}
void UART_disableTransmitCompleteInterrupt(void)
{

    /*clear interrupt enable bit for transfer complete*/
    CLEAR_BIT(UCSRB, TXCIE);
}
void UART_disableDataEmptyInterrupt(void)
{

    /*clear interrupt enable bit for data empty*/
    CLEAR_BIT(UCSRB, UDRIE);
}