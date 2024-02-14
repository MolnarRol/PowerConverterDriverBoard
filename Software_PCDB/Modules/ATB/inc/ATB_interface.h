#ifndef ATB_IF_H
#define ATB_IF_H

#include "main.h"

/* Defines and macros */
#define 		ATB_TICK__us__dU16				( (uint16_t)10 )								/**< Period of one application time base tick. */

/* Time to ticks macros. */
#define 		ATB_US_TO_TICKS_dM_U32(us)		( (uint32_t)((us) / ATB_TICK__us__dU16) )
#define		ATB_MS_TO_TICKS_dM_U32(ms)		( (uint32_t)((ms) * 1E3 / ATB_TICK__us__dU16) )
#define		ATM_S_TO_TICKS_dM_U32(s)		( (uint32_t)((s) * 1E6 /ATB_TICK__us__dU16) )

/* Ticks to time macros. */
#define		ATB_TICKS_TO_US_dM_F32(ticks)	( (float)((ticks) * ATB_TICK__us__dU16) )
#define		ATB_TICKS_TO_MS_dM_F32(ticks)	( (float)((ticks) * ATB_TICK__us__dU16) / 1.0E3f )
#define		ATB_TICKS_TO_S_dM_F32(ticks)	( (float)((ticks) * ATB_TICK__us__dU16) / 1.0E6f)

/* Interface functions. */
void 		ATB_Init(void);
uint64_t 	ATB_GetTicks_U64(void);
uint32_t	ATB_GetTicks_U32(void);
uint8_t		ATB_CheckTicksPassed_U8(const uint32_t ref_ticks_U32, const uint32_t checked_ticks_passed_U32);

#endif	/* ATB_IF_H */
