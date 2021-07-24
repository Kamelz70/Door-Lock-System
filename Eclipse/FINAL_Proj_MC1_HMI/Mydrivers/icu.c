#include "icu.h"

/*                  Global Variables        */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*                  Interrupt Service Routines        */
ISR(TIMER1_CAPT_vect)
{
    if (g_callBackPtr != NULL_PTR)
    {
        (*g_callBackPtr)();
    }
}

/*Initializing icu with timer1 in normal mode*/

void Icu_init(const Icu_ConfigType * cfg_ptr)
{
    /*set PD6 as input*/
	DDRD &= ~(1<<PD6);

    /*Config timer1 in normal mode and set FOC1A/B for 
specifying a non-pwm mode
*/
    TCCR1A = (1 << FOC1A) | (1 << FOC1B);

    /*insert clock prescalar value in first 3 bits and clear all other bits*/
    TCCR1B =(TCCR1B & 0XF8) | (cfg_ptr->clock);

    /*insert edge mode value in 6th bit*/
    TCCR1B = (TCCR1B & 0XBF) | ((cfg_ptr->edge) << 6);


    /*INIT timer counter valuse as 0*/
    TCNT1 = 0;

    /*ICU counter valuse as 0*/
    ICR1 = 0;
    /*Enable interrupt for ICU on PD6*/
    TIMSK |= (1 << TICIE1);
}
void Icu_setCallBack(void(*f_ptr)(void))
{
    g_callBackPtr = f_ptr;
}

void Icu_setEdgeDetectionType(const Icu_EdgeType a_cfg_edge)
{

    /*insert edge mode value in 6th bit*/
    TCCR1B = (TCCR1B & 0XBF) | (a_cfg_edge << 6);
}
uint16 Icu_getInputCaptureValue(void)
{
    return ICR1;
}
void Icu_clearTimerValue(void)
{
    /*Reset timer counter value TO 0*/
    TCNT1 = 0;
}
void Icu_deInit(void)
{
    /*Reset all timer1 registers*/
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;
    ICR1 = 0;

    /*Clear interrupt flag for the icu*/
    CLEAR_BIT(TIMSK, TICIE1);
}
