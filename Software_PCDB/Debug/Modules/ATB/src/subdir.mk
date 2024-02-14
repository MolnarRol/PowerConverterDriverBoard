################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Modules/ATB/src/ATB_module.c 

OBJS += \
./Modules/ATB/src/ATB_module.o 

C_DEPS += \
./Modules/ATB/src/ATB_module.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/ATB/src/%.o Modules/ATB/src/%.su Modules/ATB/src/%.cyclo: ../Modules/ATB/src/%.c Modules/ATB/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G474xx -DUSE_FULL_LL_DRIVER -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I"/home/roland/STM32CubeIDE/workspace_1.14.0/PowerConverterDriverBoard/Software_PCDB/Modules/ATB/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Modules-2f-ATB-2f-src

clean-Modules-2f-ATB-2f-src:
	-$(RM) ./Modules/ATB/src/ATB_module.cyclo ./Modules/ATB/src/ATB_module.d ./Modules/ATB/src/ATB_module.o ./Modules/ATB/src/ATB_module.su

.PHONY: clean-Modules-2f-ATB-2f-src

