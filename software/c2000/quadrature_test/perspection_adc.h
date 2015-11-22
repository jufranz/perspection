/*
 * perspection_adc.h
 *
 *  Created on: Nov 22, 2015
 *      Author: boztalay
 */

#ifndef PERSPECTION_ADC_H_
#define PERSPECTION_ADC_H_

#include "hal.h"

void perspection_adc_init(HAL_Handle halHandle);
uint16_t perspection_adc_read_vpropi1(HAL_Handle halHandle);
uint16_t perspection_adc_read_vpropi2(HAL_Handle halHandle);
uint16_t perspection_adc_read_vpropi3(HAL_Handle halHandle);
uint16_t perspection_adc_read_aux_vpropi(HAL_Handle halHandle);

#endif /* PERSPECTION_ADC_H_ */
