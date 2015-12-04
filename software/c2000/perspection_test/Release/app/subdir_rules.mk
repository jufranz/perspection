################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
app/main.obj: ../app/main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -ml -mt --float_support=softlib -O2 --include_path="C:/Users/boztalay/Documents/GitHub/perspection/software/c2000/motorware_lib" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/Users/boztalay/Documents/GitHub/perspection/software/c2000/perspection_test/app" --advice:performance=all -g --define=FAST_ROM_V1p6 --define=QEP --diag_warning=225 --display_error_number --preproc_with_compile --preproc_dependency="app/main.pp" --obj_directory="app" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


