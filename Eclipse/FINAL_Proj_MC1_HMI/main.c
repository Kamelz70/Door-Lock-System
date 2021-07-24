#include "MC1drivers/timers.h"
#include "MC1drivers/keypad.h"
#include "MC1drivers/lcd.h"
#include "MC1drivers/uart.h"
#include "MC1projectConfig.h"

/*Function prototypes*/
void Timer_1_delaySeconds(uint16 seconds);
void init_APP_MC1();
void send_Password(uint8 *pass);
void opening_door();
void set_password(uint8 *Buffer);

void main()
{
    uint8 sendBuffer[12] = {0};
    uint8 code; /*returned code by the other MCU Each time passwod is sent*/
    uint8 key = 0;
    init_APP_MC1();
    while (1)
    {
        _delay_ms(50);
        UART_sendData(3);                          /*sen_delay_ms(30);d dummy data so other mcu waits until this one is ready*/
        if (UART_recieveData() == FIRST_TIME_TRUE) /*check if first time use to set password*/
        {
            set_password(sendBuffer);
            continue;
        }
        send_Password(sendBuffer); /*send password input*/

        code = UART_recieveData(); /*get access code*/
        if (code == AUTHORIZED)    /*if authorized acess, display options*/
        {
            LCD_clearScreen();
            LCD_displayStringRowColumn(0, 0, "+: Open Door");
            LCD_displayStringRowColumn(1, 0, "-: Change Password");
            key = Keypad_getPressedKey(); /*Get selected option to send*/
            while ((key != '+') && (key != '-'))
            {
                key = Keypad_getPressedKey(); /*get key and make sure key is either + or -*/
            }

            UART_sendData(key); /*send pressed selection by uart*/
            if (key == '-')
            {
                continue; /*continue looping afeter key is sent*/
            }
            else if (key == '+')
            {
                opening_door(); /*indicate door opening when key is plus and wait for it to open*/
                continue;
            }
        }
        else if (code == ALARM_ON) /*when recieved code alarm on wait for alarm to finish and display alarm on on screen*/
        {
            LCD_clearScreen();
            LCD_displayStringRowColumn(0, 0, "ALARM OM");
            Timer_1_delaySeconds(ALARM_ON_PERIOD);
        }
    }
}

void init_APP_MC1()
{
    LCD_init();
    UART_ConfigType cfg = {ASYNCHRONOUS, DISABLE_PARITY, 9600, UART_8_BIT, UART_1_STOP_BIT, TRANSMITTER_RECIEVER, RISING_T_FALLING_R};
    UART_init(&cfg);

    LCD_displayStringRowColumn(0, 0, "MAX password");
    LCD_displayStringRowColumn(1, 2, "is 10 Digits");
    Timer_1_delaySeconds(1);
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Enter Password");
    LCD_displayStringRowColumn(1, 2, " then '='");
    Timer_1_delaySeconds(1);
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

void send_Password(uint8 *pass)
{
    uint8 passDigits = 0;

    while (passDigits < 4) /*Make sure password is more than 3 digits*/
    {
        LCD_clearScreen();
        LCD_displayStringRowColumn(0, 0, "Enter PASS:");
        LCD_goToRowColumn(1, 0);
        for (passDigits = 0; passDigits < 10; passDigits++)
        {
            /*Save each digit untill limit of 10 reached or '=' is pressed*/
            pass[passDigits] = Keypad_getPressedKey();
            if (pass[passDigits] == '=')
            {
                break;
            }
            LCD_displayCharacter('*');
        }
    }
    pass[passDigits] = '#';
    pass[passDigits + 1] = '\0';
    UART_sendString(pass);
}

void opening_door()
{
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Opening Door");
    Timer_1_delaySeconds(OPEN_DOOR_PERIOD);
}

void set_password(uint8 *Buffer)
{
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Setting Password");
    Timer_1_delaySeconds(1);
    send_Password(Buffer);
    LCD_displayStringRowColumn(0, 0, "Password Set");
    Timer_1_delaySeconds(1);
}
