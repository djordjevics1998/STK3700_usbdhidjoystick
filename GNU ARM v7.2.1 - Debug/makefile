################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emusb/subdir.mk
-include emlib/subdir.mk
-include Drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include BSP/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: STK3700_usbdhidjoystick.axf

# Tool invocations
STK3700_usbdhidjoystick.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "STK3700_usbdhidjoystick.ld" -Xlinker --gc-sections -Xlinker -Map="STK3700_usbdhidjoystick.map" --specs=nano.specs -o STK3700_usbdhidjoystick.axf "./BSP/bsp_trace.o" "./CMSIS/EFM32GG/startup_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./Drivers/hidkbd.o" "./Drivers/segmentlcd.o" "./emlib/em_adc.o" "./emlib/em_assert.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_ebi.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_i2c.o" "./emlib/em_int.o" "./emlib/em_lcd.o" "./emlib/em_leuart.o" "./emlib/em_prs.o" "./emlib/em_rtc.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./emlib/em_usart.o" "./emlib/em_vcmp.o" "./emusb/em_usbd.o" "./emusb/em_usbdch9.o" "./emusb/em_usbdep.o" "./emusb/em_usbdint.o" "./emusb/em_usbhal.o" "./emusb/em_usbtimer.o" "./src/OLED_I2C.o" "./src/descriptors.o" "./src/lcd.o" "./src/main.o" "./src/retargetvirtual.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: STK3700_usbdhidjoystick.hex'
	arm-none-eabi-objcopy -O ihex "STK3700_usbdhidjoystick.axf" "STK3700_usbdhidjoystick.hex"
	@echo ' '

	@echo 'Building bin file: STK3700_usbdhidjoystick.bin'
	arm-none-eabi-objcopy -O binary "STK3700_usbdhidjoystick.axf" "STK3700_usbdhidjoystick.bin"
	@echo ' '

	@echo 'Building s37 file: STK3700_usbdhidjoystick.s37'
	arm-none-eabi-objcopy -O srec "STK3700_usbdhidjoystick.axf" "STK3700_usbdhidjoystick.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "STK3700_usbdhidjoystick.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) STK3700_usbdhidjoystick.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
