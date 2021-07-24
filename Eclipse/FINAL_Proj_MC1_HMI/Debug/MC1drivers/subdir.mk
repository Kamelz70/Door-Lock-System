################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MC1drivers/keypad.c \
../MC1drivers/lcd.c \
../MC1drivers/timers.c \
../MC1drivers/uart.c 

OBJS += \
./MC1drivers/keypad.o \
./MC1drivers/lcd.o \
./MC1drivers/timers.o \
./MC1drivers/uart.o 

C_DEPS += \
./MC1drivers/keypad.d \
./MC1drivers/lcd.d \
./MC1drivers/timers.d \
./MC1drivers/uart.d 


# Each subdirectory must supply rules for building sources it contributes
MC1drivers/%.o: ../MC1drivers/%.c MC1drivers/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


