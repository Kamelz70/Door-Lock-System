#include "i2c.h"


/*******************************************************************************
 *                      Global Variables                                  *
 *******************************************************************************/

static volatile void (*g_TWI_callBackPtr)(void) = NULL_PTR;

/*******************************************************************************
 *                      ISR                                  *
 *******************************************************************************/

ISR(TWI_vect)
{
    if (g_TWI_callBackPtr != NULL_PTR)
    {
        (*g_TWI_callBackPtr)();
    }
}

/*******************************************************************************
 *                      Function Definitions                                  *
 *******************************************************************************/

/*Initialize TWI with input config.*/
void TWI_init(TWI_ConfigType * cfg_ptr)
{
  /*insert bit-rate value into twr
    */
  TWBR = cfg_ptr->bit_rate;

  /*set prescaler in the first 2-bits of twsr*/
  TWSR = cfg_ptr->prescaler;

  /*
    set slave address in case of slave mode
    and set general call recognition value
    */
  TWAR = (cfg_ptr->slave_address << 1) | cfg_ptr->general_call;

  /* enable TWI  */
  TWCR = (1 << TWEN);
}
void TWI_start(void)
{
  /*
    Clear interrupt flag (TWINT=1)
    Enable start bit condotion (TWSTA=1)
    Enable TWI (TWEN=1)
    */
  TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
  /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
  while (BIT_IS_CLEAR(TWCR, TWINT))
    ;
}
void TWI_stop(void)
{
  /*
    Clear interrupt flag (TWINT=1)
    Enable stop bit condition (TWSTO=1)
    Enable TWI (TWEN=1)
    */
  TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
void TWI_write(uint8 data)
{
  /*insert data in data register to be sent */
  TWDR = data;
  /*
    Clear interrupt flag (TWINT=1)
    Enable TWI (TWEN=1)
    */
  TWCR = (1 << TWINT) | (1 << TWEN);
  /*wait untill interrupt flag is set
    indicating data is successfully sent*/
  while (BIT_IS_CLEAR(TWCR, TWINT))
    ;
}
uint8 TWI_readWithAck()
{
  /*
    Clear interrupt flag (TWINT=1)
    Enable TWI (TWEN=1)
    Enable Acknowledgement bit (TWEA=1)
    */
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  /*wait untill interrupt flag is set
    indicating data is uccessfully recieved*/
  while (BIT_IS_CLEAR(TWCR, TWINT))
    ;
  return TWDR;
}
uint8 TWI_readWithNack(void)
{
  /*
    Clear interrupt flag (TWINT=1)
    Enable TWI (TWEN=1)
    This time we disable Acknowledgement bit (TWEA=0)
    */
  TWCR = (1 << TWINT) | (1 << TWEN);
  /*wait untill interrupt flag is set
    indicating data is uccessfully recieved*/
  while (BIT_IS_CLEAR(TWCR, TWINT))
    ;
  return TWDR;
}
uint8 TWI_getStatus()
{
  /*RETURN MASKED STATUS REG.*/
  return (TWSR & 0XF8);
}

void TWI_enableInterrupt(void)
 /*interrupt will activate in case of TWINT flag is high*/
{
  /*set TWI interrupt enable bit*/
SET_BIT(TWCR,TWIE);
}
void TWI_disableInterrupt(void)
{

  /*clear TWI interrupt enable bit*/
CLEAR_BIT(TWCR,TWIE);
}

void TWI_setCallback(void (*f_ptr)(void))
{
  
}
