################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/hidkbd.c \
C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7/hardware/kit/common/drivers/segmentlcd.c 

OBJS += \
./Drivers/hidkbd.o \
./Drivers/segmentlcd.o 

C_DEPS += \
./Drivers/hidkbd.d \
./Drivers/segmentlcd.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/hidkbd.o: ../Drivers/hidkbd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/hidkbd.d" -MT"Drivers/hidkbd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Drivers/segmentlcd.o: C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7/hardware/kit/common/drivers/segmentlcd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"Drivers/segmentlcd.d" -MT"Drivers/segmentlcd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


