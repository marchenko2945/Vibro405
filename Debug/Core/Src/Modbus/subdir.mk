################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Modbus/mb_map.c \
../Core/Src/Modbus/modbus.c 

OBJS += \
./Core/Src/Modbus/mb_map.o \
./Core/Src/Modbus/modbus.o 

C_DEPS += \
./Core/Src/Modbus/mb_map.d \
./Core/Src/Modbus/modbus.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Modbus/%.o Core/Src/Modbus/%.su Core/Src/Modbus/%.cyclo: ../Core/Src/Modbus/%.c Core/Src/Modbus/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F405xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Modbus

clean-Core-2f-Src-2f-Modbus:
	-$(RM) ./Core/Src/Modbus/mb_map.cyclo ./Core/Src/Modbus/mb_map.d ./Core/Src/Modbus/mb_map.o ./Core/Src/Modbus/mb_map.su ./Core/Src/Modbus/modbus.cyclo ./Core/Src/Modbus/modbus.d ./Core/Src/Modbus/modbus.o ./Core/Src/Modbus/modbus.su

.PHONY: clean-Core-2f-Src-2f-Modbus

