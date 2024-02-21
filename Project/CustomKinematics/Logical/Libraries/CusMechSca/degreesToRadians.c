#include <McPathGen.h>
#include <bur/plctypes.h>
#include <math.h>

#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CusMechSca.h"
#ifdef __cplusplus
	};
#endif

double degreesToRadiansScara(double valueInDegrees)
{
	return valueInDegrees / 180 * M_PI;
}
