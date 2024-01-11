################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

-include makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/modbus_app/subdir.mk
-include src/mbmaster/mbmaster/udp/subdir.mk
-include src/mbmaster/mbmaster/tcp/subdir.mk
-include src/mbmaster/mbmaster/rtu/subdir.mk
-include src/mbmaster/mbmaster/functions/subdir.mk
-include src/mbmaster/mbmaster/common/subdir.mk
-include src/mbmaster/mbmaster/ascii/subdir.mk
-include src/mbmaster/mbmaster/subdir.mk
-include src/mbmaster/demo/BARE/port/subdir.mk
-include src/mbmaster/demo/BARE/subdir.mk
-include src/SEGGER_RTT/subdir.mk
-include src/subdir.mk
-include ra_gen/subdir.mk
-include ra/fsp/src/r_sci_uart/subdir.mk
-include ra/fsp/src/r_ioport/subdir.mk
-include ra/fsp/src/r_gpt/subdir.mk
-include ra/fsp/src/r_can/subdir.mk
-include ra/fsp/src/bsp/mcu/all/subdir.mk
-include ra/fsp/src/bsp/cmsis/Device/RENESAS/Source/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(JMP_DEPS)),)
-include $(JMP_DEPS)
endif
ifneq ($(strip $(FSY_DEPS)),)
-include $(FSY_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(SRC_UPPER_DEPS)),)
-include $(SRC_UPPER_DEPS)
endif
ifneq ($(strip $(P_UPPER_DEPS)),)
-include $(P_UPPER_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(PP_UPPER_DEPS)),)
-include $(PP_UPPER_DEPS)
endif
ifneq ($(strip $(P_DEPS)),)
-include $(P_DEPS)
endif
ifneq ($(strip $(FSY_UPPER_DEPS)),)
-include $(FSY_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SRC_DEPS)),)
-include $(SRC_DEPS)
endif
ifneq ($(strip $(JMP_UPPER_DEPS)),)
-include $(JMP_UPPER_DEPS)
endif
ifneq ($(strip $(PP_DEPS)),)
-include $(PP_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(SX_DEPS)),)
-include $(SX_DEPS)
endif
ifneq ($(strip $(SX_UPPER_DEPS)),)
-include $(SX_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
EV_Charger_RA6M3_NT_TEST.srec \

SECONDARY_SIZE += \
EV_Charger_RA6M3_NT_TEST.siz \


# All Target
all: EV_Charger_RA6M3_NT_TEST.elf secondary-outputs

# Tool invocations
EV_Charger_RA6M3_NT_TEST.elf: $(OBJS) $(USER_OBJS) $(LINKER_SCRIPT)
	$(file > EV_Charger_RA6M3_NT_TEST.elf.in,-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op -Waggregate-return -Wfloat-equal -g -gdwarf-4 -T "fsp.ld" -Xlinker --gc-sections -L "C:\\RenesasWork\\vehicle_charger_project_new\\EV_Charger_RA6M3_NT_TEST/script" -Wl,-Map,"EV_Charger_RA6M3_NT_TEST.map" --specs=nano.specs -o "EV_Charger_RA6M3_NT_TEST.elf" -Wl,--start-group $(OBJS) $(USER_OBJS) $(LIBS) -Wl,--end-group)
	@echo Building target: $@ && arm-none-eabi-gcc @"EV_Charger_RA6M3_NT_TEST.elf.in"

EV_Charger_RA6M3_NT_TEST.srec: EV_Charger_RA6M3_NT_TEST.elf
	arm-none-eabi-objcopy -O srec "EV_Charger_RA6M3_NT_TEST.elf"  "EV_Charger_RA6M3_NT_TEST.srec"

EV_Charger_RA6M3_NT_TEST.siz: EV_Charger_RA6M3_NT_TEST.elf
	arm-none-eabi-size --format=berkeley "EV_Charger_RA6M3_NT_TEST.elf"

# Other Targets
clean:
	-$(file > clean_file.tmp,  $(JMP_DEPS)  $(FSY_DEPS)  $(C_UPPER_DEPS)  $(SECONDARY_SIZE)  $(SRC_UPPER_DEPS)  $(P_UPPER_DEPS)  $(S_DEPS)  $(PP_UPPER_DEPS)  $(P_DEPS)  $(FSY_UPPER_DEPS)  $(C_DEPS)  $(SRC_DEPS)  $(JMP_UPPER_DEPS)  $(PP_DEPS)  $(ASM_UPPER_DEPS)  $(SX_DEPS)  $(SX_UPPER_DEPS)  $(OBJS)  $(SECONDARY_FLASH)  $(ASM_DEPS)  $(SREC)  $(S_UPPER_DEPS)  $(MAP) )
	-@ xargs -P 2 -s 32000 -t -a clean_file.tmp $(RM)
	-@$(RM) clean_file.tmp
	-$(RM)  EV_Charger_RA6M3_NT_TEST.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
