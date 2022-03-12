################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Includes/sds011/Src/sds011.c 

OBJS += \
./Includes/sds011/Src/sds011.o 

C_DEPS += \
./Includes/sds011/Src/sds011.d 


# Each subdirectory must supply rules for building sources it contributes
Includes/sds011/Src/%.o: ../Includes/sds011/Src/%.c Includes/sds011/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/ccs811/Inc" -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/hx710/Inc" -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/mics6814/Inc" -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/ms1100/Inc" -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/nmea/Inc" -I"C:/Users/zaben/STM32CubeIDE/workspace_1.7.0/Meteostation.Hardware/Includes/sds011/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

