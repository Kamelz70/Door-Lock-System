#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_

/*includess*/
#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*Preprocessor Macros*/
#define ERROR 0
#define SUCCESS 1
/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
#define EEPROM_TWI_BIT_RATE 0X02
#define EEPROM_TWI_PRE_SCALER TWI_1_PRESCALER

/*Function Prototypes*/
void EEPROM_init(void); /*Initialize eeprom*/
uint8 EEPROM_writeByte(uint16 u16addr, uint8 u8data);/*Write a Byte of data to an address*/
uint8 EEPROM_readByte(uint16 u16addr, uint8 *u8data);/*Read a Byte of data From an address*/
uint8 EEPROM_writeString(uint16 u16addr,uint8* string);/*Write a String of data to an address*/
uint8 EEPROM_readString(uint16 u16addr,uint8* string);/*Read a String of data From an address*/
#endif