################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/30010_io.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32f30x.c 

OBJS += \
./Src/30010_io.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32f30x.o 

C_DEPS += \
./Src/30010_io.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Src/30010_io.o: ../Src/30010_io.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG '-DUSE_STDPERIPH_DRIVER=1' -c -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/SPL/inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/Inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/30010_io.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/main.o: ../Src/main.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG '-DUSE_STDPERIPH_DRIVER=1' -c -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/SPL/inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/Inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG '-DUSE_STDPERIPH_DRIVER=1' -c -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/SPL/inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/Inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG '-DUSE_STDPERIPH_DRIVER=1' -c -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/SPL/inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/Inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/system_stm32f30x.o: ../Src/system_stm32f30x.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DSTM32 -DSTM32F302R8Tx -DSTM32F3 -DNUCLEO_F302R8 -DDEBUG '-DUSE_STDPERIPH_DRIVER=1' -c -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/SPL/inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/Inc" -I"C:/Users/matth/Documents/DTU/30021 - Digital Instrumentation/Assignment1Project/cmsis" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/system_stm32f30x.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

