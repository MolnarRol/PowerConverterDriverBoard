/*******************************************************************************
  * @file    TIM_UTIL.h
  * @author Roland Molnar
  * @brief  Timer utils header module.
  *******************************************************************************/

#ifndef INC_TIM_UTIL_H_
#define INC_TIM_UTIL_H_

#include <stdint.h>
#include <limits.h>

typedef enum
{
	TIM_UTIL_OK_e 	= 0,
	TIM_UTIL_ERR_e
} TIM_UTIL_Status_enum;

typedef struct
{
	float	 						TIM_InputFreq__Hz__F32;
	uint32_t 						ARR_U32;
	uint32_t 						PSC_U16;
} TIM_UTIL_Param_s;

/**
  * @brief Calculates timer ARR and PSC value based on target frequency.
  * @param 	out_params_s Input/output configuration structure.
  * @param 	target_freq__Hz__F32 Target timer output frequency.
  * @retval	Operation success status.
  */
TIM_UTIL_Status_enum TIM_UTIL_CalcSettingsFromFreq(TIM_UTIL_Param_s* out_params_s, float target_freq__Hz__F32)
{
	/* Check if target_freq__Hz__F32 is positive. */
	if(target_freq__Hz__F32 <= 0.0f)
	{
		return (TIM_UTIL_ERR_e);
	}

	uint32_t tmp_psc_U32;
	float in_div_target__Hz__F32;

	in_div_target__Hz__F32 = out_params_s->TIM_InputFreq__Hz__F32 / target_freq__Hz__F32;
	tmp_psc_U32 = (uint32_t)(in_div_target__Hz__F32 / (float)((uint16_t)0xFFFF));

	/* Check if calculated prescaler value is within 16 bit value range. */
	if(tmp_psc_U32 > (uint32_t)0xFFFF)
	{
		return (TIM_UTIL_ERR_e);
	}

	out_params_s->PSC_U16 = (uint16_t)tmp_psc_U32;
	out_params_s->ARR_U32 = (uint16_t)(in_div_target__Hz__F32 / (float)(tmp_psc_U32 + 1));

	return (TIM_UTIL_OK_e);
}

uint32_t TIM_UTIL_CalcCompareValue_U32(uint32_t ARR_U32, float duty_F32 )
{
	return (uint32_t)((float)ARR_U32 * duty_F32);
}


#endif /* INC_TIM_UTIL_H_ */
