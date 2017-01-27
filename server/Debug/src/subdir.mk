################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/OBB.cpp \
../src/bullet.cpp \
../src/checkObjectHit.cpp \
../src/fps.cpp \
../src/get_data.cpp \
../src/glm.cpp \
../src/map.cpp \
../src/mob.cpp \
../src/object.cpp \
../src/player.cpp \
../src/server.cpp \
../src/server_main.cpp 

OBJS += \
./src/OBB.o \
./src/bullet.o \
./src/checkObjectHit.o \
./src/fps.o \
./src/get_data.o \
./src/glm.o \
./src/map.o \
./src/mob.o \
./src/object.o \
./src/player.o \
./src/server.o \
./src/server_main.o 

CPP_DEPS += \
./src/OBB.d \
./src/bullet.d \
./src/checkObjectHit.d \
./src/fps.d \
./src/get_data.d \
./src/glm.d \
./src/map.d \
./src/mob.d \
./src/object.d \
./src/player.d \
./src/server.d \
./src/server_main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


