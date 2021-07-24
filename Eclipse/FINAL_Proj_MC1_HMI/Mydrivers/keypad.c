#include "keypad.h"

#if (KEYPAD_COLS == 3)

static uint8 Keypad_4x3_adjustSwitchNumber(uint8 num);
#elif (KEYPAD_COLS == 4)

static uint8 Keypad_4x4_adjustSwitchNumber(uint8 num);
#endif

uint8 Keypad_getPressedKey(void)
{
    uint8 row, col;
    while (1)
    {

        for (col = 0; col < KEYPAD_COLS; col++)
        {
            /*config direction in for all ports except column number to be out in our port*/
              KEYPAD_DIR = (1<<4+col);
              /*make output zero on our column and enable internal pullups for all input ports which are rows*/
              KEYPAD_OUT = ~(1 << 4 + col);
              for (row = 0; row < KEYPAD_ROWS; row++)
              {
                  /*
              check if bit of our row is zero which means key is pressed, and return the adjusted key number
              */
                  if (BIT_IS_CLEAR(KEYPAD_IN, row))
                  {
                      while(BIT_IS_CLEAR(KEYPAD_IN, row));
#if (KEYPAD_COLS == 3)
                      return Keypad_4x3_adjustSwitchNumber(row * KEYPAD_COLS + col + 1);
#elif (KEYPAD_COLS == 4)
                      return Keypad_4x4_adjustSwitchNumber(row * KEYPAD_COLS + col + 1);
#endif
                  }
              }
        }
    }
}
#if (KEYPAD_COLS == 3)
static uint8 Keypad_4x3_adjustSwitchNumber(uint8 num)
{
    /*return number except if it's more than 9, return it's key*/
    switch (num)
    {
    case 10:
        return '*';
        break;
    case 11:
        return 0;
        break;
    case 12:
        return '#';
        break;
    default:
        return num;
    }
}
#elif (KEYPAD_COLS == 4)
static uint8 Keypad_4x4_adjustSwitchNumber(uint8 num)
{
    switch (num)
    {
    case 1:
        return 7;
        break;
    case 2:
        return 8;
        break;
    case 3:
        return 9;
        break;
    case 4:
        return '%'; // ASCII Code of %
        break;
    case 5:
        return 4;
        break;
    case 6:
        return 5;
        break;
    case 7:
        return 6;
        break;
    case 8:
        return '*'; /* ASCII Code of '*' */
        break;
    case 9:
        return 1;
        break;
    case 10:
        return 2;
        break;
    case 11:
        return 3;
        break;
    case 12:
        return '-'; /* ASCII Code of '-' */
        break;
    case 13:
        return 13; /* ASCII of Enter */
        break;
    case 14:
        return 0;
        break;
    case 15:
        return '='; /* ASCII Code of '=' */
        break;
    case 16:
        return '+'; /* ASCII Code of '+' */
        break;
    default:
        return num;
    }
}
#endif
