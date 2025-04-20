################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MCAL/TIMER/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/INTERRUPT/EXTERNAL/subdir.mk
-include MCAL/INTERRUPT/subdir.mk
-include MCAL/EEPROM/subdir.mk
-include MCAL/DIO/subdir.mk
-include LIB/DELAY/subdir.mk
-include HAL/SERVO/subdir.mk
-include HAL/NRF24L01/subdir.mk
-include HAL/LCD/subdir.mk
-include APP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Challenge1.lss \

FLASH_IMAGE += \
Challenge1.hex \

EEPROM_IMAGE += \
Challenge1.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Challenge1.elf secondary-outputs

# Tool invocations
Challenge1.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Challenge1.map -mmcu=atmega32 -o "Challenge1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Challenge1.lss: Challenge1.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Challenge1.elf  >"Challenge1.lss"
	@echo 'Finished building: $@'
	@echo ' '

Challenge1.hex: Challenge1.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Challenge1.elf  "Challenge1.hex"
	@echo 'Finished building: $@'
	@echo ' '

Challenge1.eep: Challenge1.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Challenge1.elf  "Challenge1.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Challenge1.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Challenge1.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Challenge1.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
