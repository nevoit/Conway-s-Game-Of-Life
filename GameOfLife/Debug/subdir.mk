################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../defs.o \
../gameIO.o \
../main.o \
../twoPlayer.o \
../zeroPlayer.o 

C_SRCS += \
../defs.c \
../gameIO.c \
../main.c \
../twoPlayer.c \
../zeroPlayer.c 

OBJS += \
./defs.o \
./gameIO.o \
./main.o \
./twoPlayer.o \
./zeroPlayer.o 

C_DEPS += \
./defs.d \
./gameIO.d \
./main.d \
./twoPlayer.d \
./zeroPlayer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


