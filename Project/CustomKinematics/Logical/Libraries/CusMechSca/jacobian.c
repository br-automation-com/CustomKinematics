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

plcbit jacobian(double* jointPos, double toolX, double toolY, double toolZ, struct CusMech_Scara4Ax_Dimensions* dimensions, double* jacobianMatrix)
{	
	/* Created on: May 17, 2017 */
	/* joint positions */
#define q1 jointPos[0]
#define q2 jointPos[1]
#define q3 jointPos[2]
#define q4 jointPos[3]
		
	/* mechanical system dimensions */
#define a0x dimensions->a0x
#define a0y dimensions->a0y
#define a0z dimensions->a0z
#define a1xy dimensions->a1xy
#define a1z dimensions->a1z
#define a2xy dimensions->a2xy
#define a2z dimensions->a2z
#define a3z dimensions->a3z
#define a4x dimensions->a4x
#define a4y dimensions->a4y
#define a4z dimensions->a4z
		
	/* tool */
#define a5x toolX
#define a5y toolY
#define a5z toolZ
		
	/* joint scale */
#define Q1_Scale (180.0 / M_PI)
#define Q2_Scale (180.0 / M_PI)
#define Q3_Scale 1.0
#define Q4_Scale (180.0 / M_PI)
		
	/* length scale */
#define LengthScale  1.0
#define AngleScale   (180.0 / M_PI)
		
	{
		double t1;
		double t2;
		double t3;
		double t4;
		double t5;
		double t6;
		double t7;
		double t8;
		double t9;
		t1 = q1 + q2 + q4;
		t2 = sin(t1);
		t1 = cos(t1);
		t3 = q1 + q2;
		t4 = a4x + a5x;
		t5 = a4y + a5y;
		t6 = t5 * t1;
		t7 = t4 * t2;
		t8 = sin(t3) * a2xy;
		t2 = t5 * t2;
		t1 = t4 * t1;
		t3 = cos(t3) * a2xy;
		t4 = 0.1e1 / Q4_Scale;
		t5 = 0.1e1 / Q2_Scale;
		t9 = 0.1e1 / Q1_Scale;
		jacobianMatrix[0] = -LengthScale * (sin(q1) * a1xy + t6 + t7 + t8) * t9;
		jacobianMatrix[1] = -LengthScale * (t8 + t6 + t7) * t5;
		jacobianMatrix[2] = 0;
		jacobianMatrix[3] = -LengthScale * (t6 + t7) * t4;
		jacobianMatrix[4] = LengthScale * (cos(q1) * a1xy - t2 + t1 + t3) * t9;
		jacobianMatrix[5] = LengthScale * (t1 + t3 - t2) * t5;
		jacobianMatrix[6] = 0;
		jacobianMatrix[7] = LengthScale * (t1 - t2) * t4;
		jacobianMatrix[8] = 0;
		jacobianMatrix[9] = 0;
		jacobianMatrix[10] = LengthScale / Q3_Scale;
		jacobianMatrix[11] = 0;
		jacobianMatrix[12] = AngleScale * t9;
		jacobianMatrix[13] = AngleScale * t5;
		jacobianMatrix[14] = 0;
		jacobianMatrix[15] = AngleScale * t4;
	}
	
#undef q1
#undef q2
#undef q3
#undef q4
		
#undef a0x
#undef a0y
#undef a0z
#undef a1xy
#undef a1z
#undef a2xy
#undef a2z
#undef a3z
#undef a4x
#undef a4y
#undef a4z
		
#undef a5x
#undef a5y
#undef a5z
		
#undef Q_1
#undef Q_2
#undef Q_3
#undef Q_4
		
#undef LengthScale  
#undef AngleScale   
}
