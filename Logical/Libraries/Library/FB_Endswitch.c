
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
void FB_Endswitch(struct FB_Endswitch* inst)
{
	inst->pos_reached = inst->in >= inst->pos_value ? 1 : 0;
	inst->neg_reached = inst->in <= inst->neg_value ? 1 : 0;
}
