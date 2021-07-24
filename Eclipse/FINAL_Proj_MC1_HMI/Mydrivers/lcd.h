#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*data bits mode , 4 or 8*/
#define LCD_DATA_BITS_MODE 8

/*define upper port pins to use upper ports*/

/*
#define LCD_UPPER_PORT_PINS

*/


/*Definitions for ports*/
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DIR DDRC

#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_DIR DDRD
#define RS PD4
#define RW PD5
#define E PD7

/* LCD Commands */
#define CLEAR_COMMAND 0x01 /*command to clear screen*/
#define TWO_LINE_LCD_EIGHT_BIT_MODE 0x38
#define TWO_LINE_LCD_FOUR_BIT_MODE 0x28
#define CURSOR_OFF 0x0C          /*turn off corsor*/
#define CURSOR_ON 0x0E           /*turn on corsor*/
#define SET_CURSOR_LOCATION 0x80 /*set cursor command where we add 0x80 to address*/
#define LCD_FOUR_BITS_DATA_MODE 0x02
#define TWO_LINE_LCD_Four_BIT_MODE 0x28

/*Function Declarations*/
void LCD_init(void);                                                        /*initializes lcd*/
void LCD_sendCommand(uint8 command);                                        /*send commands to lcd*/
void LCD_displayCharacter(uint8 data);                                      /*display charachter*/
void LCD_displayString(const char *string);                                /*send string to lcd*/
void LCD_goToRowColumn(uint8 row, uint8 col);                               /*got to specefic address location*/
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *string); /*got to address and display string*/
void LCD_clearScreen(void);                                                 /*clear lcd*/
void LCD_intgerToString(int num);                                          /*send integer to display on lcd*/

#endif /* LCD_H_ */
