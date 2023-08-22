################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/algoritmoOrdinamento.c \
../src/cliente.c \
../src/libro.c \
../src/main.c \
../src/menu.c \
../src/ordine.c \
../src/ricerca.c \
../src/util.c 

C_DEPS += \
./src/algoritmoOrdinamento.d \
./src/cliente.d \
./src/libro.d \
./src/main.d \
./src/menu.d \
./src/ordine.d \
./src/ricerca.d \
./src/util.d 

OBJS += \
./src/algoritmoOrdinamento.o \
./src/cliente.o \
./src/libro.o \
./src/main.o \
./src/menu.o \
./src/ordine.o \
./src/ricerca.o \
./src/util.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/algoritmoOrdinamento.d ./src/algoritmoOrdinamento.o ./src/cliente.d ./src/cliente.o ./src/libro.d ./src/libro.o ./src/main.d ./src/main.o ./src/menu.d ./src/menu.o ./src/ordine.d ./src/ordine.o ./src/ricerca.d ./src/ricerca.o ./src/util.d ./src/util.o

.PHONY: clean-src

