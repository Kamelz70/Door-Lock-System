################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Mydrivers/adc.c \
../Mydrivers/external_eeprom.c \
../Mydrivers/i2c.c \
../Mydrivers/icu.c \
../Mydrivers/keypad.c \
../Mydrivers/lcd.c \
../Mydrivers/motor.c \
../Mydrivers/spi.c \
../Mydrivers/timers.c \
../Mydrivers/uart.c 

OBJS += \
./Mydrivers/adc.o \
./Mydrivers/external_eeprom.o \
./Mydrivers/i2c.o \
./Mydrivers/icu.o \
./Mydrivers/keypad.o \
./Mydrivers/lcd.o \
./Mydrivers/motor.o \
./Mydrivers/spi.o \
./Mydrivers/timers.o \
./Mydrivers/uart.o 

C_DEPS += \
./Mydrivers/adc.d \
./Mydrivers/external_eeprom.d \
./Mydrivers/i2c.d \
./Mydrivers/icu.d \
./Mydrivers/keypad.d \
./Mydrivers/lcd.d \
./Mydrivers/motor.d \
./Mydrivers/spi.d \
./Mydrivers/timers.d \
./Mydrivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Mydrivers/%.o: ../Mydrivers/%.c Mydrivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


