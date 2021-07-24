#ifndef UART_H_
#define UART_H_

/*******************************************************************************
 *                      Includes                                  *
 *******************************************************************************/

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                      Type Definitions                                  *
 *******************************************************************************/

/*Prescalar clock config*/
typedef enum
{
   ASYNCHRONOUS, /*USE UART Asynchronous mode*/
   SYNCHRONOUS   /*USE UART synchronous mode*/
} UART_ModeType;

typedef enum
{
   DISABLE_PARITY, /*disable Parity Checks*/
   RESERVED_UART,  /*RESERVED*/
   EVEN_PARITY,    /*Enable Even Parity Checks*/
   ODD_PARITY,     /*Enabke odd Parity Checks*/

} UART_ParityModeType;

typedef enum
{
   UART_5_BIT,     /*uart 5-bit data transfer mode*/
   UART_6_BIT,     /*uart 6-bit data transfer mode*/
   UART_7_BIT,     /*uart 7-bit data transfer mode*/
   UART_8_BIT,     /*uart 8-bit data transfer mode*/
   RESERVED_UART1, /*Reserved*/
   RESERVED_UART2, /*Reserved*/
   RESERVED_UART3, /*Reserved*/
   UART_9_BIT,     /*uart 9-bit data transfer mode*/
} UART_CharacterSizeType;
typedef enum
{
   UART_1_STOP_BIT, /*use 1 stop-bit in connection*/
   UART_2_STOP_BIT  /*use 2 stop-bits in connection*/
} UART_StopBitType;
typedef enum
{
   RISING_T_FALLING_R, /*use RISING clock edge on transmit and FALLING on recieve (sunchronous mode only)*/
   FALLING_R_RISING_T  /*use FALLING clock edge on transmit and RISING on recieve (sunchronous mode only)*/
} UART_ClockPolarityType;

typedef enum
{
   UART_NO_CONNECTION,  /*Disable Both Transmitter And Reciever*/
   TRANSMITTER,         /*WORK as a uart transmitter only*/
   RECIEVER,            /*WORK as a uart reciever only*/
   TRANSMITTER_RECIEVER /*WORK as both reciever and transmitter*/
} UART_connectionDirectionType;
typedef struct
{
   UART_ModeType mode;                          /*Syncronous/Async. uart select*/
   UART_ParityModeType parity;                  /*party check select*/
   uint16 baud_rate;                            /*desired baud rate*/
   UART_CharacterSizeType c_size;               /*character size*/
   UART_StopBitType s_bit;                      /*config number of stop bits*/
   UART_connectionDirectionType conn_direction; /*work as transmitter, reciever, or both*/
   UART_ClockPolarityType clock_polarity;       /*choose clock polarity in case of synch. mode*/
} UART_ConfigType;

/*******************************************************************************
 *                      Function Declarations                                  *
 *******************************************************************************/

void UART_init(UART_ConfigType *cfg_ptr);
void UART_sendData(uint16 data);
uint16 UART_recieveData(void);
void UART_sendString(const uint8 *string);
void UART_recieveString(uint8 *string);

void UART_setRecieveCompleteCallback(void (*f_ptr)(void));
void UART_setTransmitCompleteCallback(void (*f_ptr)(void));
void UART_setDataEmptyCallback(void (*f_ptr)(void));

void UART_enableRecieveCompleteInterrupt(void);
void UART_enableTransmitCompleteInterrupt(void);
void UART_enableDataEmptyInterrupt(void);

void UART_disableRecieveCompleteInterrupt(void);
void UART_disableTransmitCompleteInterrupt(void);
void UART_disableDataEmptyInterrupt(void);
#endif /*UART_H_*/