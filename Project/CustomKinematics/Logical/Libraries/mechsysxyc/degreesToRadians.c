#include <McPathGen.h>
#include <bur/plctypes.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "MechSysXYC.h"
#ifdef __cplusplus
	};
#endif

double degreesToRadians(double valueInDegrees)
{
	return valueInDegrees / 180 * M_PI;
}
