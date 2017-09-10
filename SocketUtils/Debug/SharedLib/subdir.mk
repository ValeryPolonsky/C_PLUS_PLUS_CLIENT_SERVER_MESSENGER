################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SharedLib/MThread.cpp \
../SharedLib/MultiThreadLocker.cpp \
../SharedLib/MultipleTCPSocketsListener.cpp \
../SharedLib/TCPSocket.cpp \
../SharedLib/UDPSocket.cpp 

OBJS += \
./SharedLib/MThread.o \
./SharedLib/MultiThreadLocker.o \
./SharedLib/MultipleTCPSocketsListener.o \
./SharedLib/TCPSocket.o \
./SharedLib/UDPSocket.o 

CPP_DEPS += \
./SharedLib/MThread.d \
./SharedLib/MultiThreadLocker.d \
./SharedLib/MultipleTCPSocketsListener.d \
./SharedLib/TCPSocket.d \
./SharedLib/UDPSocket.d 


# Each subdirectory must supply rules for building sources it contributes
SharedLib/%.o: ../SharedLib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


