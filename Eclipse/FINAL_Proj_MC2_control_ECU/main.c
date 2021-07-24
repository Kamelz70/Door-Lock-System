#include <string.h>
#include "MC2drivers/timers.h"
#include "MC2drivers/uart.h"
#include "MC2drivers/motor.h"
#include "MC2drivers/external_eeprom.h"
#include "MC2projectConfig.h"

void Timer_1_delaySeconds(uint16 seconds); /*use timer1 to delay seconds*/
void init_APP_MC2();                       /*initialize MC2 app*/
void activate_alarm();                     /*activate alarm for Specified time in MC2projectConfig ALARM_ON_PERIOD*/
void openDoor();                           /*OPEN door by rotating motor for Specified time in MC2projectConfig OPEN_DOOR_PERIOD*/

void main()
{
    uint8 wrong_pass_count = 0;
    uint8 first_time_check = 0;
    uint8 recieveBuffer[12];
    uint8 passwordBuffer[12];
    uint8 key = 0;
    init_APP_MC2(); /*INITIALIZE MCU2*/
    while (1)
    {
        UART_recieveData();

        /*recieve dummy data so this mcu starts when the other mcu is ready*/
        EEPROM_readByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, &first_time_check); /*read address of first time check to compare it with original code*/
        if (first_time_check != EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE)                /*if code is not equal to the first time check code, then set password*/
        {
            UART_sendData(FIRST_TIME_TRUE);                                                                    /*indicate first time to other mcu*/
            UART_recieveString(recieveBuffer);                                                                 /*recieve password to save*/
            _delay_ms(10);                                                                                     /*delay for processing eeprom*/
            EEPROM_writeByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE); /*write first time code indicating the next time that its not the first anymore*/
            EEPROM_writeString(EEPROM_PASSWORD_START_ADDRESS, recieveBuffer);                                  /*save password in its base address Specified in MC2projectConfig EEPROM_PASSWORD_START_ADDRESS*/
                                                                                                               //UART_sendData(AUTHORIZED);/*send to othe mcu that it's authorized*/
            continue;                                                                                          /*continue looping*/
        }
        else
        {
            UART_sendData(FIRST_TIME_FALSE);                                  /*send code indicating its not first time*/
            UART_recieveString(recieveBuffer);                                /*recieve input password*/
            EEPROM_readString(EEPROM_PASSWORD_START_ADDRESS, passwordBuffer); /*get original password from eeprom*/
            if (strcmp(passwordBuffer, recieveBuffer) == 0)                   /*compare original password with eeprom one*/
            {
                UART_sendData(AUTHORIZED); /*send code for authorized access*/
            }
            else
            {
                wrong_pass_count++; /*in case password is wrong, give other tries utill it reaches 5*/
                if (wrong_pass_count > 4)
                {
                    wrong_pass_count = 0;
                    UART_sendData(ALARM_ON); /*send alarm on code*/
                    activate_alarm();        /*activate buzzer alarm*/
                    continue;
                    continue looping
                }
                UART_sendData(UNAUTHORIZED);
                continue;
            }
        }
        key = UART_recieveData(); /*when access authorized, get option key*/
        while ((key != '+') && (key != '-'))
        {
            key = UART_recieveData(); /*get key and make sure key is either + or -*/
        }
        if (key == '+')
        {
            openDoor();
        }
        else if (key == '-')
        {
            /*to change password, pretend it's first time by altering first time check value*/
            _delay_ms(10);
            EEPROM_writeByte(EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS, 0x3);
        }
    }
}

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
    UART_ConfigType cfg = {ASYNCHRONOUS, DISABLE_PARITY, 9600, UART_8_BIT, UART_1_STOP_BIT, TRANSMITTER_RECIEVER, RISING_T_FALLING_R};
    UART_init(&cfg);
    EEPROM_init();
    MOTOR_init();
    SET_BIT(BUZZER_PORT_DIRECTION, BUZZER_PIN);
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
    Timer_1_delaySeconds(OPEN_DOOR_PERIOD / 2);
    MOTOR_rotateAntiClockwise();
    Timer_1_delaySeconds(OPEN_DOOR_PERIOD / 2);
    MOTOR_stop();
}