################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../emusb/em_usbd.c \
../emusb/em_usbdch9.c \
../emusb/em_usbdep.c \
../emusb/em_usbdint.c \
../emusb/em_usbhal.c \
../emusb/em_usbtimer.c 

OBJS += \
./emusb/em_usbd.o \
./emusb/em_usbdch9.o \
./emusb/em_usbdep.o \
./emusb/em_usbdint.o \
./emusb/em_usbhal.o \
./emusb/em_usbtimer.o 

C_DEPS += \
./emusb/em_usbd.d \
./emusb/em_usbdch9.d \
./emusb/em_usbdep.d \
./emusb/em_usbdint.d \
./emusb/em_usbhal.d \
./emusb/em_usbtimer.d 


# Each subdirectory must supply rules for building sources it contributes
emusb/em_usbd.o: ../emusb/em_usbd.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbd.d" -MT"emusb/em_usbd.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emusb/em_usbdch9.o: ../emusb/em_usbdch9.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbdch9.d" -MT"emusb/em_usbdch9.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emusb/em_usbdep.o: ../emusb/em_usbdep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbdep.d" -MT"emusb/em_usbdep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emusb/em_usbdint.o: ../emusb/em_usbdint.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbdint.d" -MT"emusb/em_usbdint.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emusb/em_usbhal.o: ../emusb/em_usbhal.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbhal.d" -MT"emusb/em_usbhal.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

emusb/em_usbtimer.o: ../emusb/em_usbtimer.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -std=c99 '-DDEBUG_EFM_USER=1' '-DEFM32GG990F1024=1' -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\Drivers_inc" -I"C:\Users\fanst\SimplicityStudio\v4_workspace\STK3700_usbdhidjoystick\external_copied_files" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//app/mcu_example/EFM32GG_STK3700/usbdhidkbd" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/middleware/usb_gecko/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/drivers" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/common/bsp" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/Device/SiliconLabs/EFM32GG/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/CMSIS/Include" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//platform/emlib/inc" -I"C:/SiliconLabs/SimplicityStudio/v4/developer/sdks/gecko_sdk_suite/v2.7//hardware/kit/EFM32GG_STK3700/config" -O0 -Wall -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP -MF"emusb/em_usbtimer.d" -MT"emusb/em_usbtimer.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


