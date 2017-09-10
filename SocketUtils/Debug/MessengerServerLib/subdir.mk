################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../MessengerServerLib/Dispatcher.cpp \
../MessengerServerLib/LoginAndRegister.cpp \
../MessengerServerLib/Room.cpp \
../MessengerServerLib/TCPMessengerServer.cpp \
../MessengerServerLib/User.cpp 

OBJS += \
./MessengerServerLib/Dispatcher.o \
./MessengerServerLib/LoginAndRegister.o \
./MessengerServerLib/Room.o \
./MessengerServerLib/TCPMessengerServer.o \
./MessengerServerLib/User.o 

CPP_DEPS += \
./MessengerServerLib/Dispatcher.d \
./MessengerServerLib/LoginAndRegister.d \
./MessengerServerLib/Room.d \
./MessengerServerLib/TCPMessengerServer.d \
./MessengerServerLib/User.d 


# Each subdirectory must supply rules for building sources it contributes
MessengerServerLib/%.o: ../MessengerServerLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/Desktop/Final_Project_14/SocketUtils/SharedLib" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


