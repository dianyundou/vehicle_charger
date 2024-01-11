################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/card_reader.c \
../src/hal_entry.c \
../src/main_acdc_can.c \
../src/timer_pwm.c \
../src/touch_panel.c \
../src/uart_ep.c 

C_DEPS += \
./src/card_reader.d \
./src/hal_entry.d \
./src/main_acdc_can.d \
./src/timer_pwm.d \
./src/touch_panel.d \
./src/uart_ep.d 

OBJS += \
./src/card_reader.o \
./src/hal_entry.o \
./src/main_acdc_can.o \
./src/timer_pwm.o \
./src/touch_panel.o \
./src/uart_ep.o 

SREC += \
EV_Charger_RA6M3_NT_TEST.srec 

MAP += \
EV_Charger_RA6M3_NT_TEST.map 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	$(file > $@.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -D_RENESAS_RA_ -D_RA_CORE=CM4 -D_RA_ORDINAL=1 -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster" -I"." -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc/api" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/fsp/inc/instances" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra/arm/CMSIS_5/CMSIS/Core/Include" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_gen" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_cfg/fsp_cfg/bsp" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/ra_cfg/fsp_cfg" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster/mbmaster/include" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/mbmaster/demo/BARE/port" -I"C:/RenesasWork/vehicle_charger_project_new/EV_Charger_RA6M3_NT_TEST/src/modbus_app" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" -x c "$<")
	@echo Building file: $< && arm-none-eabi-gcc @"$@.in"

