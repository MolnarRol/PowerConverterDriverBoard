#include "ATB_interface.h"
#include "ATB_module.h"
#include "TIM_UTIL.h"

#include "stm32g4xx_ll_gpio.h"

static volatile uint64_t s_ATB_ticks_U64;

/**
 * @brief	ATB module initialization function.
 * @param	time_base_period__us__U16 Period in microseconds for s_ATB_ticks_U64 increment.
 */
void ATB_Init(void)
{
	/* Enable clocking. */
	if(__HAL_RCC_TIM17_IS_CLK_ENABLED() == 0) __HAL_RCC_TIM17_CLK_ENABLE();

	/* Basic timer setup. */
	LL_TIM_DisableCounter(TIM17);
	LL_TIM_SetClockSource(TIM17, LL_TIM_CLOCKSOURCE_INTERNAL);
	LL_TIM_SetCounter(TIM17, (uint32_t)0);
	s_ATB_ticks_U64 = 0;

	/* Timer parameter calculations. */
	TIM_UTIL_Param_s timing_s = { .TIM_InputFreq__Hz__F32 = ATB_TIM_CLK__Hz__dU32 };
	const float timer_freq__Hz__F32 = ( 1.0f/((float)(ATB_TICK__us__dU16) * 1.0E-6f) );

	if( TIM_UTIL_CalcSettingsFromFreq(&timing_s, timer_freq__Hz__F32) == TIM_UTIL_OK_e )
	{
		LL_TIM_SetPrescaler(TIM17, (uint32_t)timing_s.PSC_U16);
		LL_TIM_SetAutoReload(TIM17, timing_s.ARR_U32);
	}

	/* Interrupt setup. */
	LL_TIM_EnableIT_UPDATE(TIM17);
	NVIC_ClearPendingIRQ(TIM1_TRG_COM_TIM17_IRQn);
	NVIC_SetPriority(TIM1_TRG_COM_TIM17_IRQn, (uint32_t) 14);
	NVIC_EnableIRQ(TIM1_TRG_COM_TIM17_IRQn);

	/* Enable counter. */
	LL_TIM_EnableCounter(TIM17);
}

/**
 * @brief	Get current application time base ticks.
 * @retval	Unsigned 32-bit integer value of tick counter.
 */
uint64_t ATB_GetTicks_U64(void)
{
	return s_ATB_ticks_U64;
}

/**
 * @brief	Get current application time base ticks.
 * @retval	Unsigned 64-bit integer value of tick counter.
 */
uint32_t ATB_GetTicks_U32(void)
{
	return (uint32_t)s_ATB_ticks_U64;
}

/**
 * @brief 	Check if requested ticks (time) have passed.
 * @param 	ref_ticks_U32 Ticks reference for check.
 * @param   checked_ticks_passed_U32 Required number of ticks elapsed.
 * @retval 	Returns 1 if requested number of ticks have passed, else returns 0.
 */
uint8_t	ATB_CheckTicksPassed_U8(const uint32_t ref_ticks_U32, const uint32_t checked_ticks_passed_U32)
{
	const uint32_t ticks_timestamp_U32 = (uint32_t)s_ATB_ticks_U64;				/* Saving current time stamp. */
	uint32_t ticks_delta_U32 = ticks_timestamp_U32 - ref_ticks_U32;				/* Calculation of delta of ticks. */
	uint8_t status_U8 = (uint8_t)0;												/* Return value */

	if(ticks_delta_U32 >= checked_ticks_passed_U32)
	{
		status_U8 = (uint8_t)1;
	}

	return status_U8;
}

/**
 * @brief	Interrupt service routine for incrementing the s_ATB_ticks_U64 variable.
 */
void ATB_ISR(void)
{
	if(LL_TIM_IsActiveFlag_UPDATE(TIM17))
	{
		LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_4);
		s_ATB_ticks_U64++;
		LL_TIM_ClearFlag_UPDATE(TIM17);
	}
}
