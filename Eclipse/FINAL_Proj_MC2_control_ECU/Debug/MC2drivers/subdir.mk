################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC2drivers/external_eeprom.c \
../MC2drivers/i2c.c \
../MC2drivers/motor.c \
../MC2drivers/timers.c \
../MC2drivers/uart.c 

OBJS += \
./MC2drivers/external_eeprom.o \
./MC2drivers/i2c.o \
./MC2drivers/motor.o \
./MC2drivers/timers.o \
./MC2drivers/uart.o 

C_DEPS += \
./MC2drivers/external_eeprom.d \
./MC2drivers/i2c.d \
./MC2drivers/motor.d \
./MC2drivers/timers.d \
./MC2drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MC2drivers/%.o: ../MC2drivers/%.c MC2drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


