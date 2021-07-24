
#ifndef TIMERS_H_
#define TIMERS_H_

/*includes*/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
/*******************************************************************************
 *                      PreProcessor Macros                                    *
 *******************************************************************************/
/*define the timer you would use, other undefined timers codes will not flash to save code size*/
#define TIMER_0
#define TIMER_1
#define TIMER_2
/*******************************************************************************
 *                      Type Declarations                                    *
 *******************************************************************************/
/*Prescalar clock config*/
typedef enum
{
    NO_CLOCK,
    F_CPU_1,
    F_CPU_8,
    F_CPU_64,
    F_CPU_256,
    F_CPU_1024,
    EXTERNAL_Tn_FALLING, /*external clock on T0/1/2 falling edge*/
    EXTERNAL_Tn_RISING   /*external clock on T0/1/2 rising edge*/
} Timer_ClockType;

/*Timers Compare match output Mode config*/
typedef enum
{
    NORMAL_OCn_DISCONNECTED, /*   OC0/1A-B/2 disconnected*/
    TOGGLE_OCn_ON_COMPARE,   /*   OC0/1A-B/2 toggles on compare match*/
    CLEAR_OCn_ON_COMPARE,    /*   OC0/1A-B/2 clears on compare match*/
    SET_OCn_ON_COMPARE       /*   OC0/1A-B/2 sets on compare match*/
} Timer_COMType;


/*Timer0/2 Mode config*/
#if defined(TIMER_0) || defined(TIMER_2)
typedef enum
{
    NORMAL,            /*normal (Overflow) mode*/
    PWM_PHASE_CORRECT, /*PWM Phase Correct mode*/
    CTC,               /*compare mode*/
    FAST_PWM           /*normal PWM mode*/
} Timer_0_2_ModeType;

/*struct for configuring timer0 and 2*/
typedef struct
{
    Timer_ClockType clock;
    uint8 compare_value;
    Timer_0_2_ModeType mode;
    Timer_COMType com_mode;
} Timer_0_2_ConfigType;
#endif

#ifdef TIMER_1
/*          Type configs for timer 1       */
typedef enum
{
    NORMAL_OVF,                   /*normal (Overflow) mode*/
    PWM_PHASE_CORRECT_8_BIT,      /*TOP IS 0XFF*/
    PWM_PHASE_CORRECT_9_BIT,      /*TOP IS 0X1FF*/
    PWM_PHASE_CORRECT_10_BIT,     /*TOP IS 0X3FF*/
    CTC_OCR1A,                    /*TOP IS OCR1A*/
    FAST_PWM_8_BIT,               /*TOP IS 0XFF*/
    FAST_PWM_9_BIT,               /*TOP IS 0X1FF*/
    FAST_PWM_10_BIT,              /*TOP IS 0X3FF*/
    PWM_PHASE_FREQ_CORRECT_ICR1,  /*TOP IS ICR1*/
    PWM_PHASE_FREQ_CORRECT_OCR1A, /*TOP IS OCR1A*/
    PWM_PHASE_CORRECT_ICR1,       /*TOP IS ICR1*/
    PWM_PHASE_CORRECT_OCR1A,      /*TOP IS OCR1A*/
    CTC_ICR1,                     /*TOP IS ICR1*/
    T1_RESERVED,                  /*RESERVED*/
    FAST_PWM_ICR1,                /*TOP IS ICR1*/
    FAST_PWM_OCR1A                /*TOP IS OCR1A*/
} Timer_1_ModeType;

/*Function Prototypes*/
typedef struct
{
    Timer_ClockType clock;   /*clock value for prescalar*/
    uint16 compare_valueA;   /*Value to be set in OCR1A (output compare register A)*/
    uint16 compare_valueB;   /*Value to be set in OCR1B (output compare register A)*/
    Timer_1_ModeType mode;   /*timer 1 mode*/
    Timer_COMType com_modeA; /*OC1A mode*/
    Timer_COMType com_modeB; /*OC1B mode*/
} Timer_1_ConfigType;
#endif
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/*                      Timer 0                  */
#ifdef TIMER_0
void Timer_0_init(const Timer_0_2_ConfigType *const cfg_ptr); /*Initialize timer 0 configuration*/
void Timer_0_deInit(void);                                    /*clear all timer registers*/
void Timer_0_setCompareValue(const uint8 compare_val);        /*Set output compare value for timer0*/
void Timer_0_setCounterValue(const uint8 counter_val);        /*Set current counter value for timer0*/

void Timer_0_setCompareCallBack(void (*f_ptr)(void));  /*Set compare mode isr callback*/
void Timer_0_setOverflowCallBack(void (*f_ptr)(void)); /*Set overflow mode isr callback*/

void Timer_0_EnableCompareInterrupt(void);   /*Enable compare mode Interrupt*/
void Timer_0_EnableOverflowInterrupt(void);  /*Enable OverFlow mode Interrupt*/
void Timer_0_DisableCompareInterrupt(void);  /*Disable compare mode Interrupt*/
void Timer_0_DisableOverflowInterrupt(void); /*Disable OverFlow mode Interrupt*/

void Timer_0_setPrescalar(const Timer_ClockType clock);
#endif
/*                      Timer 1                  */

#ifdef TIMER_1
void Timer_1_init(const Timer_1_ConfigType *const cfg_ptr); /*Initialize timer 0 configuration*/
void Timer_1_deInit(void);                                  /*clear all timer registers*/
void Timer_1_setCompareValueA(const uint16 compare_val);    /*Set output compare value for timer0*/
void Timer_1_setCompareValueB(const uint16 compare_val);    /*Set output compare value for timer0*/
void Timer_1_setCounterValue(const uint16 counter_val);     /*Set current counter value for timer0*/

void Timer_1_setCompareACallBack(void (*f_ptr)(void)); /*Set compare mode isr callback*/
void Timer_1_setCompareBCallBack(void (*f_ptr)(void)); /*Set compare mode isr callback*/
void Timer_1_setOverflowCallBack(void (*f_ptr)(void)); /*Set overflow mode isr callback*/

void Timer_1_EnableCompareAInterrupt(void); /*Enable compare mode Interrupt*/
void Timer_1_EnableCompareBInterrupt(void); /*Enable compare mode Interrupt*/
void Timer_1_EnableOverflowInterrupt(void); /*Enable OverFlow mode Interrupt*/

void Timer_1_DisableCompareAInterrupt(void); /*Disable compare mode Interrupt*/
void Timer_1_DisableCompareBInterrupt(void); /*Disable compare mode Interrupt*/
void Timer_1_DisableOverflowInterrupt(void); /*Disable OverFlow mode Interrupt*/

void Timer_1_setPrescalar(const Timer_ClockType clock);
#endif
/*                      Timer 2                 */
#ifdef TIMER_2
void Timer_2_init(const Timer_0_2_ConfigType *const cfg_ptr); /*Initialize timer 0 configuration*/
void Timer_2_deInit(void);                                    /*clear all timer registers*/
void Timer_2_setCompareValue(const uint8 compare_val);        /*Set output compare value for timer0*/
void Timer_2_setCounterValue(const uint8 counter_val);        /*Set current counter value for timer0*/

void Timer_2_setCompareCallBack(void (*f_ptr)(void));  /*Set compare mode isr callback*/
void Timer_2_setCompareCallBack(void (*f_ptr)(void));  /*Set compare mode isr callback*/
void Timer_2_setOverflowCallBack(void (*f_ptr)(void)); /*Set overflow mode isr callback*/

void Timer_2_EnableCompareInterrupt(void);   /*Enable compare mode Interrupt*/
void Timer_2_EnableOverflowInterrupt(void);  /*Enable OverFlow mode Interrupt*/
void Timer_2_DisableCompareInterrupt(void);  /*Disable compare mode Interrupt*/
void Timer_2_DisableOverflowInterrupt(void); /*Disable OverFlow mode Interrupt*/

void Timer_2_setPrescalar(const Timer_ClockType clock);
#endif
#endif
