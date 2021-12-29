
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Axis(struct FB_Axis* inst)
{
	/*
	if (inst->pwm_percentage > 100)
	{
		inst->pwm_percentage = 100;
	}
	if (inst->pwm_percentage < -100)
	{
		inst->pwm_percentage = -100;
	}
	REAL raw_percentage = (REAL) inst->pwm_percentage / 100.0 * 32767.0;
	inst->pwm_value = (INT) raw_percentage;
	*/
	inst->speed = inst->counter - inst->last_counter;
	inst->speed = (inst->speed * 3000 / 24.0) / 0.002;
	inst->last_counter = inst->counter;
}
