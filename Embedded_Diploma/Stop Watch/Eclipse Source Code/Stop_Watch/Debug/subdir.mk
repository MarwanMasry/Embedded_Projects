################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Functions.c \
../Global_variables.c \
../Main.c \
../Timer1_External_Interrupts_IO.c 

OBJS += \
./Functions.o \
./Global_variables.o \
./Main.o \
./Timer1_External_Interrupts_IO.o 

C_DEPS += \
./Functions.d \
./Global_variables.d \
./Main.d \
./Timer1_External_Interrupts_IO.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


