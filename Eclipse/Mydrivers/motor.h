#ifndef MOTOR_H_
#define MOTOR_H_

#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*Preprocessor Macros*/
#define MOTOR_CLOCKWISE_PIN PB0     /*Input2 for motor */
#define MOTOR_ANTICLOCKWISE_PIN PB1 /*Input1 for motor */

#define MOTOR_PORT_DIRECTION DDRB
#define MOTOR_PORT PORTB

/*Function Declarations*/

void MOTOR_init(void);                /*initialize motor ports*/
void MOTOR_rotateClockwise(void);     /*rotate motor in clockwise direction*/
void MOTOR_rotateAntiClockwise(void); /*rotate motor in anti clockwise direction*/
void MOTOR_stop(void);                /*stop motor*/

#endif /* MOTOR_H_ */
