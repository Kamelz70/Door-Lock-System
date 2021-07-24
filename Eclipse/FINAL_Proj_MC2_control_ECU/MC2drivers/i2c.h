#ifndef I2C_H_
#define I2C_H_
/*******************************************************************************
 *                      Includes                                  *
 *******************************************************************************/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*******************************************************************************
 *                      Type Definitions                                  *
 *******************************************************************************/
typedef enum
{
    TWI_1_PRESCALER,  /*use prescalar of 1 for TWI TWPS=0*/
    TWI_4_PRESCALER,  /*use prescalar of 4 for TWI TWPS=1 */
    TWI_16_PRESCALER, /*use prescalar of 16 for TWI TWPS=2*/
    TWI_64_PRESCALER  /*use prescalar of 64 for TWI TWPS=3*/
} TWI_PrescalarType;

typedef enum
{
    GENERAL_CALL_OFF, /*turn off recognitions for general calls*/
    GENERAL_CALL_ON,  /*turn on recognitions for general calls*/
} TWI_GeneralCallType;

/************************************************************
 *      SCL frequency= F_CPU/(16+2TWBR*4^TWPS)              *
 *                                                          *
 ***********************************************************/

typedef struct
{
    uint8 bit_rate;                   /*Value to be inserted in TWBR*/
    TWI_PrescalarType prescaler;      /*Prescaler value*/
    uint8 slave_address;              /*slave address to be addressed when any device wants to communicate*/
    TWI_GeneralCallType general_call; /*general call recognition bit*/
} TWI_ConfigType;
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
/* I2C Status Bits in the TWSR Register */
#define TW_START 0x08        // start has been sent
#define TW_REP_START 0x10    // repeated start
#define TW_MT_SLA_W_ACK 0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define TW_MT_SLA_R_ACK 0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define TW_MT_DATA_ACK 0x28  // Master transmit data and ACK has been received from Slave.
#define TW_MR_DATA_ACK 0x50  // Master received data and send ACK to slave
#define TW_MR_DATA_NACK 0x58 // Master received data but doesn't send ACK to slave

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

void TWI_init(TWI_ConfigType *cfg_ptr);        /*Initialize TWI with input configuration*/
void TWI_start(void);                      /*send start condition on TWI*/
void TWI_stop(void);                       /*send Stop condition on TWI*/
void TWI_write(uint8 data);                /*write data on TWI*/
uint8 TWI_readWithAck(void);               /*read data on TWI then send Ack*/
uint8 TWI_readWithNack(void);              /*read data on TWI then stop indicating a Nack*/
uint8 TWI_getStatus(void);                 /*Get current TWI bus status*/
void TWI_enableInterrupt(void);            /*interrupt will activate in case of TWINT flag is high*/
void TWI_disableInterrupt(void);           /*Deactivate TWI interrupt*/
void TWI_setCallback(void (*f_ptr)(void)); /*set callback function pointer to be executed in TWI ISR*/

#endif