#ifndef SPI_H_
#define SPI_H_
/*includes*/
#include "micro_config.h"
#include "common_macros.h"
#include "std_types.h"

/*Function Declarations*/
void SPI_initMaster(void);
void SPI_initSlave(void);
void SPI_sendByte(uint8 data);
void SPI_sendString(const uint8 * str);
uint8 SPI_recieveByte(void);
void SPI_recieveString(uint8 * const str);


#endif