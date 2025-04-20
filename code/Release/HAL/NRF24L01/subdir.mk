################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/NRF24L01/NRF24L01.c 

OBJS += \
./HAL/NRF24L01/NRF24L01.o 

C_DEPS += \
./HAL/NRF24L01/NRF24L01.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/NRF24L01/%.o: ../HAL/NRF24L01/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


