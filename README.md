# AVR-Door-lock-system
![image](https://user-images.githubusercontent.com/56312212/196010477-b35d5639-25ce-4811-a3a9-59d76c91ab49.png)

-initial password is "3336"

-The system doesn't count a try unless more than 3 digits are entered, entering the password multiple times wrong will trigger the alarm.

-if you wish to reset system to set first time password, go into 
Eclipse\FINAL_Proj_MC2_control_ECU\MC2projectConfig.h
and change EEPROM_PASSWORD_CHECK_FIRST_TIME_CODE to any uint8 value then rebuild

-in eclipse folder, there a file containing all drivers named Mydrivers

- ALARM_ON_PERIOD in both MCUs projectConfig files set The time that the alarm will be on*/
- OPEN_DOOR_PERIOD in both MCUs projectConfig files set The time that the door will open in

The Eclipse file has both of the MCs' codes, 

the first microcontroller (HMI) controls the keypad, lcd,and uses UART to communicate with the other MC.

The second MC controls the eeprom, the door motor, the alarm when entering the wrong password for the limit.
