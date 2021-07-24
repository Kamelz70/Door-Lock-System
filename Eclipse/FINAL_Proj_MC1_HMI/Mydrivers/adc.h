#ifndef ADC_H_
#define ADC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"



extern volatile uint16 g_adcResult;

void ADC_init(void);
void ADC_readChannel(uint8 channel);



#endif