################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/MoveControl/movecontrol.c 

OBJS += \
./Core/Src/MoveControl/movecontrol.o 

C_DEPS += \
./Core/Src/MoveControl/movecontrol.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/MoveControl/%.o Core/Src/MoveControl/%.su Core/Src/MoveControl/%.cyclo: ../Core/Src/MoveControl/%.c Core/Src/MoveControl/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-MoveControl

clean-Core-2f-Src-2f-MoveControl:
	-$(RM) ./Core/Src/MoveControl/movecontrol.cyclo ./Core/Src/MoveControl/movecontrol.d ./Core/Src/MoveControl/movecontrol.o ./Core/Src/MoveControl/movecontrol.su

.PHONY: clean-Core-2f-Src-2f-MoveControl

