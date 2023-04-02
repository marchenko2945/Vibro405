################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/VibroSens/vibro.c 

OBJS += \
./Core/Src/VibroSens/vibro.o 

C_DEPS += \
./Core/Src/VibroSens/vibro.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/VibroSens/%.o Core/Src/VibroSens/%.su Core/Src/VibroSens/%.cyclo: ../Core/Src/VibroSens/%.c Core/Src/VibroSens/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-VibroSens

clean-Core-2f-Src-2f-VibroSens:
	-$(RM) ./Core/Src/VibroSens/vibro.cyclo ./Core/Src/VibroSens/vibro.d ./Core/Src/VibroSens/vibro.o ./Core/Src/VibroSens/vibro.su

.PHONY: clean-Core-2f-Src-2f-VibroSens

