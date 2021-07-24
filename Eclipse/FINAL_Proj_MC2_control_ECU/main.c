#include <string.h>
#include "Mydrivers/timers.h"
#include "Mydrivers/uart.h"
#include "Mydrivers/motor.h"
#include "Mydrivers/external_eeprom.h"
#include "projectConfig.h"

void Timer_1_delaySeconds(uint16 seconds)
{
    Timer_1_ConfigType cfg = {F_CPU_1024, 7812, 0, CTC_OCR1A, NORMAL_OCn_DISCONNECTED, NORMAL_OCn_DISCONNECTED};
    Timer_1_init(&cfg);
    for (uint8 i = 0; i < seconds; i++)
    {
        while (BIT_IS_CLEAR(TIFR, OCF1A))
            ;
        SET_BIT(TIFR, OCF1A);
        Timer_1_setCounterValue(0);
    }

    Timer_1_deInit();
}
void init_APP_MC2()
{
    LCD_init();
    UART_ConfigType cfg = {ASYNCHRONOUS, DISABLE_PARITY, 9600, UART_8_BIT, UART_1_STOP_BIT, TRANSMITTER_RECIEVER, RISING_T_FALLING_R};
    UART_init(&cfg);
    EEPROM_init();
    MOTOR_init();
    SET_BIT(BUZZER_PORT_DIRECTION,BUZZER_PIN);
}

void activate_alarm()
{
    SET_BIT(BUZZER_PORT, BUZZER_PIN);
    Timer_1_delaySeconds(ALARM_ON_PERIOD);
    CLEAR_BIT(BUZZER_PORT, BUZZER_PIN);
}
void openDoor()
{
    MOTOR_rotateClockwise();
    Timer_1_delaySeconds(OPEN_DOOR_PERIOD/2);
    MOTOR_rotateAntiClockwise();
    Timer_1_delaySeconds(OPEN_DOOR_PERIOD/2);
    MOTOR_stop();
}

void main()
{
    uint8 wrong_pass_count = 0;
    uint8 first_time_check = 0;
    uint8 recieveBuffer[12];
    uint8 passwordBuffer[12];
    uint8 key = 0;
    init_APP_MC2();
    while (1)
    {
        UART_recieveString(recieveBuffer);
        EEPROM_readByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, &first_time_check); /*read address of first time check to compare it with original code*/
        _delay_ms(10);
        if (first_time_check != EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE)
        {
            EEPROM_writeByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE);
            EEPROM_writeString(EEPROM_PASSWORD_START_ADDRESS, recieveBuffer);
            UART_sendData(AUTHORIZED);
        }
        else
        {
            EEPROM_readString(EEPROM_PASSWORD_START_ADDRESS, passwordBuffer);
            if (strcmp(passwordBuffer, recieveBuffer) == 0)
            {
                UART_sendData(AUTHORIZED);
            }
            else
            {
                wrong_pass_count++;
                if (wrong_pass_count > 4)
                {
                    wrong_pass_count = 0;
                    UART_sendData(ALARM_ON);
                    activate_alarm();
                }
                UART_sendData(UNAUTHORIZED);
                continue;
            }
        }
        key = UART_recieveData();
        while ((key != '+') && (key != '-'))
        {
            key = UART_recieveData();
        }
        if (key == '+')
        {
            openDoor();
        }
        else if (key == '-')
        {
            /*to change password, pretend it's first time by altering first time check value*/
            _delay_ms(10);
            EEPROM_writeByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, 0x0);
        }
    }
}
