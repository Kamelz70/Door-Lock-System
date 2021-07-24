#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

/*Authorization codes to indicate if password is authorized or not*/
#define AUTHORIZED 234
#define UNAUTHORIZED 86
/*password start address in EEPROM*/
#define EEPROM_PASSWORD_START_ADDRESS 0X300

/*number saved in a specefic EEPROM location to check if its first time password*/
#define EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE 115
/*address for check if first time number*/
#define EEPROM_PASSWORD_CHECK_FIRST_TIME_ADDRESS 0X200

/*code for alarm start and bazzer activation for a minute*/
#define ALARM_ON 42
#define ALARM_ON_PERIOD 10 /*The time that the alarm will be on*/

#define OPEN_DOOR_PERIOD 10 /*The time that the door will take to open*/

#define BUZZER_PORT_DIRECTION DDRC /*port direction of connected buzzer*/
#define BUZZER_PORT PORTC          /*port of connected buzzer*/
#define BUZZER_PIN PC4             /*pin f connected buzzer*/

#endif