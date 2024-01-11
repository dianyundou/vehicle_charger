################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ra_gen/common_data.c \
../ra_gen/hal_data.c \
../ra_gen/main.c \
../ra_gen/pin_data.c \
../ra_gen/vector_data.c 

C_DEPS += \
./ra_gen/common_data.d \
./ra_gen/hal_data.d \
./ra_gen/main.d \
./ra_gen/pin_data.d \
./ra_gen/vector_data.d 

OBJS += \
./ra_gen/common_data.o \
./ra_gen/hal_data.o \
./ra_gen/main.o \
./ra_gen/pin_data.o \
./ra_gen/vector_data.o 

SREC += \
EV_Charger_RA6M3_NT_TEST.srec 

MAP += \
EV_Charger_RA6M3_NT_TEST.map 


# Each subdirectory must supply rules for building sources it contributes
ra_gen/%.o: ../ra_gen/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster" -I"." -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc/api" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc/instances" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_gen" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_cfg/fsp_cfg/bsp" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_cfg/fsp_cfg" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster/mbmaster/include" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster/demo/BARE/port" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/modbus_app" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

