#include "timers.h"

/*******************************************************************************
 *                               Global Variables                                    *
 *******************************************************************************/
#ifdef TIMER_0
static volatile void (*g_Timer_0_Overflow_callBackPtr)(void) = NULL_PTR; /*pointer to  function to be executed in isr of timer0 overflow interrupt*/
static volatile void (*g_Timer_0_Compare_callBackPtr)(void) = NULL_PTR;  /*pointer to  function to be executed in isr of timer0 compare interrupt*/
#endif

#ifdef TIMER_2
static volatile void (*g_Timer_2_Overflow_callBackPtr)(void) = NULL_PTR; /*pointer to  function to be executed in isr of timer2 overflow interrupt*/
static volatile void (*g_Timer_2_Compare_callBackPtr)(void) = NULL_PTR;  /*pointer to  function to be executed in isr of timer2 compare interrupt*/
#endif

#ifdef TIMER_1
static volatile void (*g_Timer_1_Overflow_callBackPtr)(void) = NULL_PTR; /*pointer to  function to be executed in isr of timer1 overflow interrupt*/
static volatile void (*g_Timer_1_CompareA_callBackPtr)(void) = NULL_PTR; /*pointer to  function to be executed in isr of timer1 compare A interrupt*/
static volatile void (*g_Timer_1_CompareB_callBackPtr)(void) = NULL_PTR; /*pointer to  function to be executed in isr of timer1 compare B interrupt*/
#endif

/*******************************************************************************
 *                              ISRs                                                    *
 *******************************************************************************/
#ifdef TIMER_0
ISR(TIMER0_COMP_vect)
{
    if (g_Timer_0_Compare_callBackPtr != NULL_PTR)
    {
        (*g_Timer_0_Compare_callBackPtr)();
    }
}


ISR(TIMER0_OVF_vect)
{
    if (g_Timer_0_Overflow_callBackPtr != NULL_PTR)
    {
        (*g_Timer_0_Overflow_callBackPtr)();
    }
}
#endif

#ifdef TIMER_2
ISR(TIMER2_COMP_vect)
{
    if (g_Timer_2_Compare_callBackPtr != NULL_PTR)
    {
        (*g_Timer_2_Compare_callBackPtr)();
    }
}

ISR(TIMER2_OVF_vect)
{
    if (g_Timer_2_Overflow_callBackPtr != NULL_PTR)
    {
        (*g_Timer_2_Overflow_callBackPtr)();
    }
}
#endif

#ifdef TIMER_1
ISR(TIMER1_COMPA_vect)
{
    if (g_Timer_1_CompareA_callBackPtr != NULL_PTR)
    {
        (*g_Timer_1_CompareA_callBackPtr)();
    }
}

ISR(TIMER1_COMPB_vect)
{
    if (g_Timer_1_CompareB_callBackPtr != NULL_PTR)
    {
        (*g_Timer_1_CompareB_callBackPtr)();
    }
}

ISR(TIMER1_OVF_vect)
{
    if (g_Timer_1_Overflow_callBackPtr != NULL_PTR)
    {
        (*g_Timer_1_Overflow_callBackPtr)();
    }
}
#endif

/*******************************************************************************
 *                      Function Definitions                                    *
 *******************************************************************************/
#ifdef TIMER_0
/*Initialize timer 0 configuration*/
void Timer_0_init(const Timer_0_2_ConfigType *const cfg_ptr)
{
    /*insert all configuration settings in the control register*/
    TCCR0 = ((((~cfg_ptr->mode) & 0b01)) << 7) | ((cfg_ptr->mode & 0b01) << 6) | (cfg_ptr->com_mode << 4) | ((cfg_ptr->mode & 0b10) << 2) | cfg_ptr->clock;

    /*insert compare value to compare register*/
    OCR0 = cfg_ptr->compare_value;

    /*Initialize current counter value to 0*/
    TCNT0 = 0;
}

/*Set output compare value for timer0*/
void Timer_0_setCompareValue(const uint8 compare_val)
{
    /*insertcompare value to compare register*/
    OCR0 = compare_val;
}

/*Set current counter value for timer0*/
void Timer_0_setCounterValue(const uint8 counter_val)
{
    /*insert current counter value*/
    TCNT0 = counter_val;
}

/*Set compare mode isr callback*/
void Timer_0_setCompareCallBack(void (*f_ptr)(void))
{

    g_Timer_0_Compare_callBackPtr = f_ptr;
}

/*Set overflow mode isr callback*/
void Timer_0_setOverflowCallBack(void (*f_ptr)(void))
{
    g_Timer_0_Overflow_callBackPtr = f_ptr;
}

/*Enable compare mode Interrupt*/
void Timer_0_EnableCompareInterrupt(void)
{
    SET_BIT(TIMSK, OCIE0);
}

/*Enable compare mode Interrupt*/
void Timer_0_EnableOverflowInterrupt(void)
{
    SET_BIT(TIMSK, TOIE0);
}
/*Disable compare mode Interrupt*/

void Timer_0_DisableCompareInterrupt(void)
{
    CLEAR_BIT(TIMSK, OCIE0);
}
/*Disable overflow mode Interrupt*/

void Timer_0_DisableOverflowInterrupt(void)
{
    CLEAR_BIT(TIMSK, TOIE0);
}

void Timer_0_deInit(void)
{
    /*reset all registers and disable all interrupts*/
    TCCR0 = 0;
    OCR0 = 0;
    TCNT0 = 0;
    CLEAR_BIT(TIMSK, OCIE0);
    CLEAR_BIT(TIMSK, TOIE0);
}

void Timer_0_setPrescalar(const Timer_ClockType clock)
{
    /*insert clock prescalar*/
    TCCR0 = (TCCR0 & (~0X07)) | clock;
}
#endif
/*                           Timer 2                 */
#ifdef TIMER_2
void Timer_2_init(const Timer_0_2_ConfigType *const cfg_ptr)
{
    /*insert all configuration settings in the control register*/
    TCCR2 = ((((~cfg_ptr->mode) & 0b01)) << 7) | ((cfg_ptr->mode & 0b01) << 6) | (cfg_ptr->com_mode << 4) | ((cfg_ptr->mode & 0b10) << 2) | cfg_ptr->clock;

    /*insert compare value to compare register*/
    OCR2 = cfg_ptr->compare_value;

    /*Initialize current counter value to 0*/
    TCNT2 = 0;
}

/*Set output compare value for timer0*/
void Timer_2_setCompareValue(const uint8 compare_val)
{
    /*insertcompare value to compare register*/
    OCR2 = compare_val;
}

/*Set current counter value for timer0*/
void Timer_2_setCounterValue(const uint8 counter_val)
{
    /*insert current counter value*/
    TCNT2 = counter_val;
}

/*Set compare mode isr callback*/
void Timer_2_setCompareCallBack(void (*f_ptr)(void))
{

    g_Timer_2_Compare_callBackPtr = f_ptr;
}

/*Set overflow mode isr callback*/
void Timer_2_setOverflowCallBack(void (*f_ptr)(void))
{
    g_Timer_2_Overflow_callBackPtr = f_ptr;
}

/*Enable compare mode Interrupt*/
void Timer_2_EnableCompareInterrupt(void)
{
    SET_BIT(TIMSK, OCIE2);
}

/*Enable compare mode Interrupt*/
void Timer_2_EnableOverflowInterrupt(void)
{
    SET_BIT(TIMSK, TOIE2);
}
/*Disable compare mode Interrupt*/

void Timer_2_DisableCompareInterrupt(void)
{
    CLEAR_BIT(TIMSK, OCIE2);
}
/*Disable overflow mode Interrupt*/

void Timer_2_DisableOverflowInterrupt(void)
{
    CLEAR_BIT(TIMSK, TOIE2);
}

void Timer_2_deInit(void)
{
    /*reset all registers and disable all interrupts*/
    TCCR2 = 0;
    OCR2 = 0;
    TCNT2 = 0;
    CLEAR_BIT(TIMSK, OCIE2);
    CLEAR_BIT(TIMSK, TOIE2);
}

void Timer_2_setPrescalar(const Timer_ClockType clock)
{
    /*insert clock prescalar*/
    TCCR2 = (TCCR2 & (~0X07)) | clock;
}
#endif
/*                       Timer 1               */
#ifdef TIMER_1
void Timer_1_init(const Timer_1_ConfigType *const cfg_ptr)
{
    /*insert all configuration settings in the control register A*/
    TCCR1A = (cfg_ptr->com_modeA << 6) | (cfg_ptr->com_modeB << 4) | (cfg_ptr->mode & 0x03);

    if ((cfg_ptr->mode == 0) || (cfg_ptr->mode == 4) || (cfg_ptr->mode == 12))
    {
        /*SET FOC  bits on non-PWM modes*/
        TCCR1A |= (0b11 << 2);
    }
    /*insert all configuration settings in the control register B*/
    TCCR1B = ((cfg_ptr->mode & 0xC0) << 1) | (cfg_ptr->clock);
    /*insert compare value to its compare register*/
    OCR1A = cfg_ptr->compare_valueA;
    OCR1B = cfg_ptr->compare_valueB;

    /*Initialize current counter value to 0*/
    TCNT1 = 0;
}
void Timer_1_deInit(void)
{
    /*reset all registers and disable all interrupts*/
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 0;
    OCR1B = 0;
    TCNT1 = 0;
    CLEAR_BIT(TIMSK, OCIE1A);
    CLEAR_BIT(TIMSK, OCIE1B);
    CLEAR_BIT(TIMSK, TOIE1);
}
void Timer_1_setCompareValueA(const uint16 compare_val)
{
    /*insertcompare value to compare register*/
    OCR1A = compare_val;
}
void Timer_1_setCompareValueB(const uint16 compare_val)
{
    /*insertcompare value to compare register*/
    OCR1B = compare_val;
}
/*Set current counter value for timer0*/
void Timer_1_setCounterValue(const uint16 counter_val)
{
    /*insert current counter value*/
    TCNT1 = counter_val;
}

/*Set compare mode isr callback*/
void Timer_1_setCompareACallBack(void (*f_ptr)(void))
{

    g_Timer_1_CompareA_callBackPtr = f_ptr;
}
/*Set compare mode isr callback*/
void Timer_1_setCompareBCallBack(void (*f_ptr)(void))
{

    g_Timer_1_CompareB_callBackPtr = f_ptr;
}

/*Set overflow mode isr callback*/
void Timer_1_setOverflowCallBack(void (*f_ptr)(void))
{
    g_Timer_1_Overflow_callBackPtr = f_ptr;
}

/*Enable compare mode Interrupt*/
void Timer_1_EnableCompareAInterrupt(void)
{
    SET_BIT(TIMSK, OCIE1A);
}
/*Enable compare mode Interrupt*/
void Timer_1_EnableCompareBInterrupt(void)
{
    SET_BIT(TIMSK, OCIE1B);
}

/*Enable compare mode Interrupt*/
void Timer_1_EnableOverflowInterrupt(void)
{
    SET_BIT(TIMSK, TOIE1);
}

/*Disable compare mode Interrupt*/
void Timer_1_DisableCompareAInterrupt(void)
{
    CLEAR_BIT(TIMSK, OCIE1A);
}

/*Disable compare mode Interrupt*/
void Timer_1_DisableCompareBInterrupt(void)
{
    CLEAR_BIT(TIMSK, OCIE1A);
}

/*Disable overflow mode Interrupt*/
void Timer_1_DisableOverflowInterrupt(void)
{
    CLEAR_BIT(TIMSK, TOIE1);
}

void Timer_1_setPrescalar(const Timer_ClockType clock)
{
    /*insert clock prescalar*/
    TCCR1B = (TCCR1B & (~0X07)) | clock;
}
#endif