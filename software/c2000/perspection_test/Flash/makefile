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
"./motorware/CodeStartBranch.obj" \
"./motorware/SPIB.obj" \
"./motorware/adc.obj" \
"./motorware/clarke.obj" \
"./motorware/clk.obj" \
"./motorware/cpu.obj" \
"./motorware/cpu_usage.obj" \
"./motorware/ctrlQEP.obj" \
"./motorware/dlog4ch.obj" \
"./motorware/dlog4chc.obj" \
"./motorware/drv8301.obj" \
"./motorware/enc.obj" \
"./motorware/fem.obj" \
"./motorware/filter_fo.obj" \
"./motorware/flash.obj" \
"./motorware/fw.obj" \
"./motorware/gpio.obj" \
"./motorware/hal.obj" \
"./motorware/ipark.obj" \
"./motorware/memCopy.obj" \
"./motorware/offset.obj" \
"./motorware/osc.obj" \
"./motorware/park.obj" \
"./motorware/pid.obj" \
"./motorware/pie.obj" \
"./motorware/pll.obj" \
"./motorware/pwm.obj" \
"./motorware/pwr.obj" \
"./motorware/qep.obj" \
"./motorware/slip.obj" \
"./motorware/spi.obj" \
"./motorware/spi_slave.obj" \
"./motorware/svgen.obj" \
"./motorware/svgen_current.obj" \
"./motorware/timer.obj" \
"./motorware/traj.obj" \
"./motorware/usDelay.obj" \
"./motorware/user.obj" \
"./motorware/wdog.obj" \
"./app/main.obj" \
"C:/ti/motorware/motorware_1_01_00_15/sw/ide/ccs/cmd/f2806x/F28069F.cmd" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/iqmath/lib/f28x/32b/IQmathLog.lib" \
"C:/ti/motorware/motorware_1_01_00_15/sw/modules/spintac/lib/32b/SpinTAC.lib" \
$(GEN_CMDS__FLAG) \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include motorware/subdir_vars.mk
-include app/subdir_vars.mk
-include subdir_rules.mk
-include motorware/subdir_rules.mk
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
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml -O2 -g --define=FAST_ROM_V1p6 --define=QEP --define=FLASH --diag_warning=225 --display_error_number -z -m"perspection_test.map" --stack_size=0x3B0 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --reread_libs --priority --disable_auto_rts --diag_suppress=16002 --xml_link_info="perspection_test_linkInfo.xml" --rom_model -o "perspection_test.out" $(ORDERED_OBJS)
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
	-$(RM) "motorware\SPIB.pp" "motorware\adc.pp" "motorware\clarke.pp" "motorware\clk.pp" "motorware\cpu.pp" "motorware\cpu_usage.pp" "motorware\ctrlQEP.pp" "motorware\dlog4ch.pp" "motorware\drv8301.pp" "motorware\enc.pp" "motorware\fem.pp" "motorware\filter_fo.pp" "motorware\flash.pp" "motorware\fw.pp" "motorware\gpio.pp" "motorware\hal.pp" "motorware\ipark.pp" "motorware\memCopy.pp" "motorware\offset.pp" "motorware\osc.pp" "motorware\park.pp" "motorware\pid.pp" "motorware\pie.pp" "motorware\pll.pp" "motorware\pwm.pp" "motorware\pwr.pp" "motorware\qep.pp" "motorware\slip.pp" "motorware\spi.pp" "motorware\spi_slave.pp" "motorware\svgen.pp" "motorware\svgen_current.pp" "motorware\timer.pp" "motorware\traj.pp" "motorware\user.pp" "motorware\wdog.pp" "app\main.pp" 
	-$(RM) "motorware\CodeStartBranch.obj" "motorware\SPIB.obj" "motorware\adc.obj" "motorware\clarke.obj" "motorware\clk.obj" "motorware\cpu.obj" "motorware\cpu_usage.obj" "motorware\ctrlQEP.obj" "motorware\dlog4ch.obj" "motorware\dlog4chc.obj" "motorware\drv8301.obj" "motorware\enc.obj" "motorware\fem.obj" "motorware\filter_fo.obj" "motorware\flash.obj" "motorware\fw.obj" "motorware\gpio.obj" "motorware\hal.obj" "motorware\ipark.obj" "motorware\memCopy.obj" "motorware\offset.obj" "motorware\osc.obj" "motorware\park.obj" "motorware\pid.obj" "motorware\pie.obj" "motorware\pll.obj" "motorware\pwm.obj" "motorware\pwr.obj" "motorware\qep.obj" "motorware\slip.obj" "motorware\spi.obj" "motorware\spi_slave.obj" "motorware\svgen.obj" "motorware\svgen_current.obj" "motorware\timer.obj" "motorware\traj.obj" "motorware\usDelay.obj" "motorware\user.obj" "motorware\wdog.obj" "app\main.obj" 
	-$(RM) "motorware\CodeStartBranch.pp" "motorware\dlog4chc.pp" "motorware\usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

