/*
 * perspection_adc.c
 *
 *  Created on: Nov 22, 2015
 *      Author: boztalay
 */

#include "perspection_adc.h"

// Defines

#define ADC_READ_DELAY_USEC 2.0

#define VPROPI1_SOC_FRC_MASK 0x0100
#define VPROPI1_RES_NUM ADC_ResultNumber_8

#define VPROPI2_SOC_FRC_MASK 0x0200
#define VPROPI2_RES_NUM ADC_ResultNumber_9

#define VPROPI3_SOC_FRC_MASK 0x0400
#define VPROPI3_RES_NUM ADC_ResultNumber_10

#define AUX_VPROPI_SOC_FRC_MASK 0x0800
#define AUX_VPROPI_RES_NUM ADC_ResultNumber_11

// Generic functions

uint16_t perspection_adc_read(HAL_Handle halHandle, uint16_t socFrcMask, ADC_ResultNumber_e resNum) {
	HAL_Obj* obj = (HAL_Obj*) halHandle;

	ADC_setSocFrcWord(obj->adcHandle, socFrcMask);
	usDelay(ADC_READ_DELAY_USEC);
	return ADC_readResult(obj->adcHandle, ADC_ResultNumber_8);
}

// Specific functions

void perspection_adc_init(HAL_Handle halHandle) {
	HAL_Obj* obj = (HAL_Obj*) halHandle;

	// VPROPI1
	ADC_setSocChanNumber(obj->adcHandle, ADC_SocNumber_8, ADC_SocChanNumber_B0);
	ADC_setupSocTrigSrc(obj->adcHandle, ADC_SocNumber_8, ADC_NoIntTriggersSOC);
	ADC_setSocTrigSrc(obj->adcHandle, ADC_SocNumber_8, ADC_SocTrigSrc_Sw);
	ADC_setSocSampleDelay(obj->adcHandle, ADC_SocNumber_8, ADC_SocSampleDelay_64_cycles);

	// VPROPI2
	ADC_setSocChanNumber(obj->adcHandle, ADC_SocNumber_9, ADC_SocChanNumber_B1);
	ADC_setupSocTrigSrc(obj->adcHandle, ADC_SocNumber_9, ADC_NoIntTriggersSOC);
	ADC_setSocTrigSrc(obj->adcHandle, ADC_SocNumber_9, ADC_SocTrigSrc_Sw);
	ADC_setSocSampleDelay(obj->adcHandle, ADC_SocNumber_9, ADC_SocSampleDelay_9_cycles);

	// VPROPI2
	ADC_setSocChanNumber(obj->adcHandle, ADC_SocNumber_10,ADC_SocChanNumber_B2);
	ADC_setupSocTrigSrc(obj->adcHandle, ADC_SocNumber_10, ADC_NoIntTriggersSOC);
	ADC_setSocTrigSrc(obj->adcHandle, ADC_SocNumber_10, ADC_SocTrigSrc_Sw);
	ADC_setSocSampleDelay(obj->adcHandle, ADC_SocNumber_10, ADC_SocSampleDelay_9_cycles);

	// AUX_VPROPI
	ADC_setSocChanNumber(obj->adcHandle, ADC_SocNumber_11,ADC_SocChanNumber_A6);
	ADC_setupSocTrigSrc(obj->adcHandle, ADC_SocNumber_11, ADC_NoIntTriggersSOC);
	ADC_setSocTrigSrc(obj->adcHandle, ADC_SocNumber_11, ADC_SocTrigSrc_Sw);
	ADC_setSocSampleDelay(obj->adcHandle, ADC_SocNumber_11, ADC_SocSampleDelay_9_cycles);
}

uint16_t perspection_adc_read_vpropi1(HAL_Handle halHandle) {
	return perspection_adc_read(halHandle, VPROPI1_SOC_FRC_MASK, VPROPI1_RES_NUM);
}

uint16_t perspection_adc_read_vpropi2(HAL_Handle halHandle) {
	return perspection_adc_read(halHandle, VPROPI2_SOC_FRC_MASK, VPROPI2_RES_NUM);
}

uint16_t perspection_adc_read_vpropi3(HAL_Handle halHandle) {
	return perspection_adc_read(halHandle, VPROPI3_SOC_FRC_MASK, VPROPI3_RES_NUM);
}

uint16_t perspection_adc_read_aux_vpropi(HAL_Handle halHandle) {
	return perspection_adc_read(halHandle, AUX_VPROPI_SOC_FRC_MASK, AUX_VPROPI_RES_NUM);
}
