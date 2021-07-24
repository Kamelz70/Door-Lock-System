#include "lcd.h"


void LCD_init(void)
{
    LCD_CTRL_DIR |= (1 << RS) | (1 << RW) | (1 << E);
#if (LCD_DATA_BITS_MODE == 8)
    LCD_DATA_DIR = 0XFF; /*enable all data pins as output*/

    LCD_sendCommand(TWO_LINE_LCD_EIGHT_BIT_MODE); /*enable 2 line 8 bit mode*/
#elif (LCD_DATA_BITS_MODE == 4)
#ifdef LCD_UPPER_PORT_PINS
    LCD_DATA_DIR = 0XF0;
#else
    LCD_DATA_DIR = 0X0F;
#endif
    LCD_sendCommand(LCD_FOUR_BITS_DATA_MODE);
    LCD_sendCommand(TWO_LINE_LCD_FOUR_BIT_MODE);
#endif

    LCD_sendCommand(CURSOR_OFF);
    LCD_clearScreen();
}
void LCD_sendCommand(uint8 command)
{
    CLEAR_BIT(LCD_CTRL_PORT, RS); /*command mode*/
    CLEAR_BIT(LCD_CTRL_PORT, RW); /*write mode*/
    _delay_ms(1);                 /*tas processing*/
    SET_BIT(LCD_CTRL_PORT, E);    /*ENABLE DATA*/
    _delay_ms(1);                 /*processing*/

#if (LCD_DATA_BITS_MODE == 8)
    LCD_DATA_PORT = command; /*output command on the 8 pins*/
#elif (LCD_DATA_BITS_MODE == 4)
    /*on 4 data bits*/
#ifdef LCD_UPPER_PORT_PINS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0X0F) | (command & 0xF0); /*output first (most significant) half of command on upper pins*/
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | ((command & 0xF0) >> 4); /*output first (most significant) half of command on lower pins*/
#endif

    _delay_ms(1);                                                     /*processing*/
    CLEAR_BIT(LCD_CTRL_PORT, E);                                      /*ENABLE DATA*/
    _delay_ms(1);                                                     /*processing*/
    SET_BIT(LCD_CTRL_PORT, E);                                        /*ENABLE DATA*/
    _delay_ms(1);                                                     /*processing*/

#ifdef LCD_UPPER_PORT_PINS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0X0F) | ((command & 0x0F) << 4); /*output second (least significant) half of command on upper pins*/
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | (command & 0x0F);        /*output second (least significant) half of command on lower pins*/
#endif

#endif

    _delay_ms(1);                /*processing*/
    CLEAR_BIT(LCD_CTRL_PORT, E); /*ENABLE DATA*/
    _delay_ms(1);                /*processing*/
}

void LCD_displayCharacter(uint8 data)
{
    SET_BIT(LCD_CTRL_PORT, RS);   /*data mode*/
    CLEAR_BIT(LCD_CTRL_PORT, RW); /*write mode*/
    _delay_ms(1);                 /*tas processing*/
    SET_BIT(LCD_CTRL_PORT, E);    /*ENABLE DATA*/
    _delay_ms(1);                 /*processing*/

#if (LCD_DATA_BITS_MODE == 8)
    LCD_DATA_PORT = data; /*output character on all 8 pins*/

#elif (LCD_DATA_BITS_MODE == 4)
    /*on 4 data bits*/
#ifdef LCD_UPPER_PORT_PINS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0X0F) | (data & 0xF0); /*output first (most significant) half of character on upper pins*/
#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | ((data & 0xF0) >> 4);    /*output second (least significant) half of character on lower pins*/
#endif

    _delay_ms(1);                /*processing*/
    CLEAR_BIT(LCD_CTRL_PORT, E); /*ENABLE DATA*/
    _delay_ms(1);                /*processing*/
    SET_BIT(LCD_CTRL_PORT, E);   /*ENABLE DATA*/
    _delay_ms(1);                /*processing*/

#ifdef LCD_UPPER_PORT_PINS
    LCD_DATA_PORT = (LCD_DATA_PORT & 0X0F) | ((data & 0x0F) << 4);

#else
    LCD_DATA_PORT = (LCD_DATA_PORT & 0XF0) | (data & 0x0F);
#endif
#endif
    _delay_ms(1);                /*processing*/
    CLEAR_BIT(LCD_CTRL_PORT, E); /*ENABLE DATA*/
    _delay_ms(1);                /*processing*/
}

void LCD_displayString(const char *string)
{
    while ((*string) != '\0')
    {
        LCD_displayCharacter(*string); /*display character untill strinf is null terminated*/
        string++;
    }
}
void LCD_goToRowColumn(uint8 row, uint8 col)
{
    uint8 address = 0; /*initialize address*/
    switch (row)
    {
    case 0:
        address = col; /*add base address of first line*/
        break;

    case 1:
        address = 0x40 + col; /*add base address of second line*/
        break;

    case 2:
        address = 010 + col; /*add base address of third line*/
        break;

    case 3:
        address = 0x50 + col; /*add base address of fourth line*/
        break;

    default:
        address = 0;
    }
    LCD_sendCommand((SET_CURSOR_LOCATION | address)); /*add a 1 to the most signifigant bit so the lcd goes to address*/
}
void LCD_displayStringRowColumn(uint8 row, uint8 col, const char *string)
{
    LCD_goToRowColumn(row, col);
    LCD_displayString(string);
}
void LCD_clearScreen(void)
{
    LCD_sendCommand(CLEAR_COMMAND); /*send ckear screen command*/
}
void LCD_intgerToString(int num)
{
    char buff[16];       /*buffer String to hold the ascii result */
    itoa(num, buff, 10); /* 10 for decimal */
    LCD_displayString(buff);
}
