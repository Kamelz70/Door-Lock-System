#ifndef ICU_H_
#define ICU_H_

/*includes*/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*******************************************************************************
 *                               Type Definitions                                    *
 *******************************************************************************/

/*Prescalar clock config*/
typedef enum{
NO_CLOCK,
F_CPU_1,
F_CPU_8,
F_CPU_64,
F_CPU_256,
F_CPU_1024,
EXTERNAL_T1_FALLING,
EXTERNAL_T1_RISING
}Icu_Clock;

/*ICU Edge detection mode*/
typedef enum{
    FALLING,
    RISING
}Icu_EdgeType;

/*struct for configuring icu*/
typedef struct{
Icu_Clock clock;
Icu_EdgeType edge;    
}Icu_ConfigType;

/*******************************************************************************
 *                               Function Prototypes                                    *
 *******************************************************************************/

void Icu_init(const Icu_ConfigType * cfg_ptr);
void Icu_setCallBack(void(*f_ptr)(void));
void Icu_setEdgeDetectionType(const Icu_EdgeType cfg_edge);
uint16 Icu_getInputCaptureValue(void);
void Icu_clearTimerValue(void);
void Icu_deInit(void);



#endif
