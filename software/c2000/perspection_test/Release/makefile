################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
-l"rts2800_ml.lib" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/fast/lib/32b/f28x/f2806x/2806xRevB_FastSpinROMSymbols.lib" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/iqmath/lib/f28x/32b/IQmath.lib" \
"./lib/CodeStartBranch.obj" \
"./lib/SPIB.obj" \
"./lib/adc.obj" \
"./lib/clarke.obj" \
"./lib/clk.obj" \
"./lib/cpu.obj" \
"./lib/cpu_usage.obj" \
"./lib/ctrlQEP.obj" \
"./lib/dlog4ch.obj" \
"./lib/dlog4chc.obj" \
"./lib/drv8301.obj" \
"./lib/enc.obj" \
"./lib/fem.obj" \
"./lib/filter_fo.obj" \
"./lib/flash.obj" \
"./lib/fw.obj" \
"./lib/gpio.obj" \
"./lib/hal.obj" \
"./lib/ipark.obj" \
"./lib/memCopy.obj" \
"./lib/offset.obj" \
"./lib/osc.obj" \
"./lib/park.obj" \
"./lib/pid.obj" \
"./lib/pie.obj" \
"./lib/pll.obj" \
"./lib/pwm.obj" \
"./lib/pwr.obj" \
"./lib/qep.obj" \
"./lib/slip.obj" \
"./lib/spi.obj" \
"./lib/spi_slave.obj" \
"./lib/svgen.obj" \
"./lib/svgen_current.obj" \
"./lib/timer.obj" \
"./lib/traj.obj" \
"./lib/usDelay.obj" \
"./lib/user.obj" \
"./lib/wdog.obj" \
"./app/main.obj" \
"C:/ti/motorware/motorware_1_01_00_15/sw/ide/ccs/cmd/f2806x/f28069M_ram_lnk.cmd" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/iqmath/lib/f28x/32b/IQmathLog.lib" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/spintac/lib/32b/SpinTAC.lib" \
$(GEN_CMDS__FLAG) \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include lib/subdir_vars.mk
-include app/subdir_vars.mk
-include subdir_rules.mk
-include lib/subdir_rules.mk
-include app/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
perspection_test.out \

EXE_OUTPUTS__QUOTED += \
"perspection_test.out" \

BIN_OUTPUTS += \
perspection_test.hex \

BIN_OUTPUTS__QUOTED += \
"perspection_test.hex" \


# All Target
all: perspection_test.out

# Tool invocations
perspection_test.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml -O2 -g --define=FAST_ROM_V1p6 --define=QEP --diag_warning=225 --display_error_number -z -m"perspection_test.map" --stack_size=0x3B0 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --reread_libs --priority --disable_auto_rts --diag_suppress=16002 --xml_link_info="perspection_test_linkInfo.xml" --rom_model -o "perspection_test.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

perspection_test.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/hex2000"  -o "perspection_test.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "lib\SPIB.pp" "lib\adc.pp" "lib\clarke.pp" "lib\clk.pp" "lib\cpu.pp" "lib\cpu_usage.pp" "lib\ctrlQEP.pp" "lib\dlog4ch.pp" "lib\drv8301.pp" "lib\enc.pp" "lib\fem.pp" "lib\filter_fo.pp" "lib\flash.pp" "lib\fw.pp" "lib\gpio.pp" "lib\hal.pp" "lib\ipark.pp" "lib\memCopy.pp" "lib\offset.pp" "lib\osc.pp" "lib\park.pp" "lib\pid.pp" "lib\pie.pp" "lib\pll.pp" "lib\pwm.pp" "lib\pwr.pp" "lib\qep.pp" "lib\slip.pp" "lib\spi.pp" "lib\spi_slave.pp" "lib\svgen.pp" "lib\svgen_current.pp" "lib\timer.pp" "lib\traj.pp" "lib\user.pp" "lib\wdog.pp" "app\main.pp" 
	-$(RM) "lib\CodeStartBranch.obj" "lib\SPIB.obj" "lib\adc.obj" "lib\clarke.obj" "lib\clk.obj" "lib\cpu.obj" "lib\cpu_usage.obj" "lib\ctrlQEP.obj" "lib\dlog4ch.obj" "lib\dlog4chc.obj" "lib\drv8301.obj" "lib\enc.obj" "lib\fem.obj" "lib\filter_fo.obj" "lib\flash.obj" "lib\fw.obj" "lib\gpio.obj" "lib\hal.obj" "lib\ipark.obj" "lib\memCopy.obj" "lib\offset.obj" "lib\osc.obj" "lib\park.obj" "lib\pid.obj" "lib\pie.obj" "lib\pll.obj" "lib\pwm.obj" "lib\pwr.obj" "lib\qep.obj" "lib\slip.obj" "lib\spi.obj" "lib\spi_slave.obj" "lib\svgen.obj" "lib\svgen_current.obj" "lib\timer.obj" "lib\traj.obj" "lib\usDelay.obj" "lib\user.obj" "lib\wdog.obj" "app\main.obj" 
	-$(RM) "lib\CodeStartBranch.pp" "lib\dlog4chc.pp" "lib\usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

