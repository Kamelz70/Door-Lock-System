#include "motor.h"

/*Function Definitions*/
void MOTOR_init(void)
{
	/* configure pin interrupt pin*/
	//SET_BIT (DDRD,PD3);
	/* Motor is stopped at the beginning */
	MOTOR_PORT &= ~((1 << MOTOR_CLOCKWISE_PIN) | (1 << MOTOR_ANTICLOCKWISE_PIN));
	/* configure pins for motor as output pins */
	MOTOR_PORT_DIRECTION |= (1 << MOTOR_CLOCKWISE_PIN) | (1 << MOTOR_ANTICLOCKWISE_PIN);
}
void MOTOR_rotateClockwise(void)
{

	SET_BIT(MOTOR_PORT,MOTOR_CLOCKWISE_PIN);
	CLEAR_BIT(MOTOR_PORT,MOTOR_ANTICLOCKWISE_PIN);
}
void MOTOR_rotateAntiClockwise(void)
{
	
	CLEAR_BIT(MOTOR_PORT,MOTOR_CLOCKWISE_PIN);
	SET_BIT(MOTOR_PORT,MOTOR_ANTICLOCKWISE_PIN);
}
void MOTOR_stop(void)
{
	CLEAR_BIT(MOTOR_PORT,MOTOR_CLOCKWISE_PIN);
	CLEAR_BIT(MOTOR_PORT,MOTOR_ANTICLOCKWISE_PIN);

}
