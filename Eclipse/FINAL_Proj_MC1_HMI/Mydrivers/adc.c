#include "adc.h"

/*******************************************************************************
 *                          Global Variables                                   *
 *******************************************************************************/

volatile uint16 g_adcResult;
/*******************************************************************************
 *                          ISR's Definitions                                  *
 *******************************************************************************/
ISR(ADC_vect)
{
    g_adcResult = ADC;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/
void ADC_init(void)
{
    /*  Description: ADMUX REGISTER
REFS1:0 =00 ->USE VOLTAGE AT AREF PIN
ADLAR =0 -> RIGHT ADJUST RESULT
MUX4:0 = 000000 USE CHANNEL 0 AS INITIALIZATION
*/
    ADMUX = 0;
    /*  Description: ADCSRA REGISTER
ADPS2:0 = 011 (8 PRESCALER)
ADIE = 1 INTERRUPT ENABLE (ENABLE)
ADATE = 0 AUTO TRIGER BIT (DISABLE)
ADEN = 1 ADC ENABLE BIT (ENABLE)
ADSC = 0 START CONVERSION BIT (DISABLE)
*/
    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS1) | (1 << ADPS0);
}
void ADC_readChannel(uint8 channel)
{

    /*  Description: ADMUX REGISTER
REFS1:0 =00 ->USE VOLTAGE AT AREF PIN
ADLAR =0 -> RIGHT ADJUST RESULT
MUX4:0 = channel num
(Safely insert channel number)
*/
    ADMUX = (ADMUX & 0b11100000) | (channel & 0b00000111);
    
/*  ADSC = 1 START CONVERSION BIT (ENABLE)
*/
    SET_BIT(ADCSRA,ADSC);
}
