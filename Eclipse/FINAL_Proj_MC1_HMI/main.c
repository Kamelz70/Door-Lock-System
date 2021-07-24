#include "Mydrivers/timers.h"
#include "Mydrivers/keypad.h"
#include "Mydrivers/lcd.h"
#include "Mydrivers/uart.h"
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
void init_APP_MC1()
{
    LCD_init();
    UART_ConfigType cfg = {ASYNCHRONOUS, DISABLE_PARITY, 9600, UART_8_BIT, UART_1_STOP_BIT, TRANSMITTER_RECIEVER, RISING_T_FALLING_R};
    UART_init(&cfg);

    LCD_displayStringRowColumn(0, 0, "MAX password");
    LCD_displayStringRowColumn(1, 2, "is 10 Digits");
    //Timer_1_delaySeconds(1);
    LCD_clearScreen();
    LCD_displayStringRowColumn(0, 0, "Enter Password");
    LCD_displayStringRowColumn(1, 2, " then '='");
    //Timer_1_delaySeconds(1);
}

void send_Password(uint8 *pass)
{
    uint8 passDigits=0;
 
    while(passDigits<3) /*Make sure password is more than 3 digits*/
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
void main()
{
    uint8 sendBuffer[12] = {0};
    // uint8 recieveBuffer[12] = {0};
    uint8 code; /*returned code by the other MCU Each time passwod is sent*/
    uint8 key = 0;
    init_APP_MC1();
    while (1)
    {

        send_Password(sendBuffer);

        code = UART_recieveData();
        if (code == AUTHORIZED)
        {
            LCD_clearScreen();
            LCD_displayStringRowColumn(0, 0, "+: Open Door");
            LCD_displayStringRowColumn(1, 0, "-: Change Password");
            key = Keypad_getPressedKey();
            /*Get selected option to send*/
            while ((key != '+') && (key != '-'))
            {
                key = Keypad_getPressedKey();
            }
            /*send pressed selection by uart*/
            UART_sendData(key);
            if (key == '-')
            {
                LCD_clearScreen();
                LCD_displayStringRowColumn(0, 0, "Changing Password");
                Timer_1_delaySeconds(1);
                send_Password(sendBuffer);
                LCD_displayStringRowColumn(0, 0, "Password Changed");
                Timer_1_delaySeconds(1);
            }
            else if (key == '+')
            {
                opening_door();
            }
        }
        else if (code == ALARM_ON)
        {
            LCD_clearScreen();
            LCD_displayStringRowColumn(0, 0, "ALARM OM");
            Timer_1_delaySeconds(ALARM_ON_PERIOD);
        }
    }
}
