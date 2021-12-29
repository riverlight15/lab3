
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

void FB_Controller(struct FB_Controller* inst)
{
	REAL a = inst->in * inst->k_p;
	REAL b = inst->in * inst->k_i;
	inst->integrator.dt = inst->dt;
	inst->integrator.in = b;
	FB_Integrator(&inst->integrator);
	a = a > inst->max_abs_value ? inst->max_abs_value : a;
	a = a < -inst->max_abs_value ? -inst->max_abs_value : a;
	inst->sum = a + inst->integrator.out;
	inst->out = inst->sum;
	inst->out = inst->out > inst->max_abs_value ? inst->max_abs_value : inst->out;
	inst->out = inst->out < -inst->max_abs_value ? -inst->max_abs_value : inst->out;
	inst->last_sum = (inst->out - inst->sum);
	inst->integrator.state = inst->integrator.state + inst->last_sum;
}
