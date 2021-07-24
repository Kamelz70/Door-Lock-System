#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/*preprocessor macros*/
#define KEYPAD_COLS 4
#define KEYPAD_ROWS 4

#define KEYPAD_OUT PORTA
#define KEYPAD_IN PINA
#define KEYPAD_DIR DDRA

/*function prototypes*/
uint8 Keypad_getPressedKey(void);
#endif