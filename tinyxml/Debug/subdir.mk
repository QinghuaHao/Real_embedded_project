################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../tinystr.cpp \
../tinyxml.cpp \
../tinyxmlerror.cpp \
../tinyxmlparser.cpp 

O_SRCS += \
../tinystr.o \
../tinyxml.o \
../tinyxmlerror.o \
../tinyxmlparser.o 

OBJS += \
./tinystr.o \
./tinyxml.o \
./tinyxmlerror.o \
./tinyxmlparser.o 

CPP_DEPS += \
./tinystr.d \
./tinyxml.d \
./tinyxmlerror.d \
./tinyxmlparser.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


