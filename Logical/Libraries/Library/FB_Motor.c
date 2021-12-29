
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
void FB_Motor(struct FB_Motor* inst)
{
	REAL a = inst->in / inst->k_e - inst->out_w;
	REAL b = a / inst->T_m;
	inst->integrator.dt = inst->dt;
	inst->integrator_phi.dt = inst->dt;
	inst->integrator.in = b;
	FB_Integrator(&inst->integrator);
	inst->out_w = inst->integrator.out;
	inst->integrator_phi.in = inst->out_w;
	FB_Integrator(&inst->integrator_phi);
	inst->out_phi = inst->integrator_phi.out;
}
