################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/TestMessengerClient.cpp \
../src/main.cpp 

OBJS += \
./src/TestMessengerClient.o \
./src/main.o 

CPP_DEPS += \
./src/TestMessengerClient.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/Final_Project_14/SocketUtils/MessengerClientLib" -I"/home/user/Desktop/Final_Project_14/SocketUtils/MessengerServerLib" -I"/home/user/Desktop/Final_Project_14/SocketUtils/SharedLib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

