################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Settings/Settings.c 

OBJS += \
./Core/Src/Settings/Settings.o 

C_DEPS += \
./Core/Src/Settings/Settings.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Settings/%.o Core/Src/Settings/%.su Core/Src/Settings/%.cyclo: ../Core/Src/Settings/%.c Core/Src/Settings/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Settings

clean-Core-2f-Src-2f-Settings:
	-$(RM) ./Core/Src/Settings/Settings.cyclo ./Core/Src/Settings/Settings.d ./Core/Src/Settings/Settings.o ./Core/Src/Settings/Settings.su

.PHONY: clean-Core-2f-Src-2f-Settings

