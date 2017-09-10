################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessengerClientLib/TCPMessengerClient.cpp \
../MessengerClientLib/UdpMessenger.cpp 

OBJS += \
./MessengerClientLib/TCPMessengerClient.o \
./MessengerClientLib/UdpMessenger.o 

CPP_DEPS += \
./MessengerClientLib/TCPMessengerClient.d \
./MessengerClientLib/UdpMessenger.d 


# Each subdirectory must supply rules for building sources it contributes
MessengerClientLib/%.o: ../MessengerClientLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/Final_Project_14/SocketUtils/SharedLib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


