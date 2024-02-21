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

#ifndef DBL_EPSILON
#define DBL_EPSILON 2.2204460492503131E-16      /* precision of double */
#endif

/* comparisons to precision of double */
#define IS_DBL_ZERO(a)         (fabs(a) <= DBL_EPSILON) /* argument should be evaluated only once - f() */
#define IS_DBL_EQUAL(a, b)     IS_DBL_ZERO((a) - (b)) /* arguments should be evaluated only once - f() */

unsigned long LeftRight14(double q2)
{
	double decision;

	decision = Mod2pi(q2);

	if (IS_DBL_ZERO(decision) || IS_DBL_EQUAL(decision, M_PI) || IS_DBL_EQUAL(decision, -M_PI))
	{
		/* it cannot be decided */
		return 2;
	}
	else
	{
		if (decision > 0.0)
		{
			return 1 /* Left */;
		}
		else
		{
			return 0 /* Right */;
		}
	}
}


/* customInverse - implements inverse kinematic of the mechanical system
 *
 * Input: 
 *   TcpPos - array - position of TCP coordinates (dimension of the array: Parameter.PathCount)
 *   RefJointPos - array - last known positions of joints coordinates (dimension of the array: Parameter.JointCount) 
 * Output:
 *   JointPos - array - position of joints (dimension of the array: Parameter.JointCount) 
 * Parameters:
 *   MechDimensionsAddr - address of the user defined PV variable containing dimensions of the mechanical system
 *   Tool - tool geometry and other parameters of currently active tool
 *   JointCount - provides number of joints configured in mechanical system configuration
 *   TcpCount - provides number of joints configured in mechanical system configuration
 * Info:
 *   Status - additional information provided by the user (e.g. error code)
 * Return 
 *   return mcPATHGEN_CUSMECH_SUCCESS, if function finished successfully, otherwise return mcPATHGEN_CUSMECH_INFO, mcPATHGEN_CUSMECH_WARNING or mcPATHGEN_CUSMECH_ERROR 
 */

McPathGenCusMechStatusEnum customInverseScara(struct McPathGenCusMechInvType* data)
{	
	CusMech_Scara4Ax_Dimensions dimensions = *(CusMech_Scara4Ax_Dimensions*)data->Parameter.MechDimensionsAddr;

	double tcpPos[4] = {data->Input.TcpPos[0], data->Input.TcpPos[1], data->Input.TcpPos[2], degreesToRadiansScara(data->Input.TcpPos[3])};
	double jointRefPos[4] = {degreesToRadiansScara(data->Input.JointRefPos[0]), degreesToRadiansScara(data->Input.JointRefPos[1]), data->Input.JointRefPos[2], degreesToRadiansScara(data->Input.JointRefPos[3])};
	
	double a1, a2, b1, b2, c1, c2,
	phi1, psi1, phi2, psi2,
	qs1[2], qs2[2],  /* q1 and q2 + their variants */
	a4[3] = {dimensions.a4x + data->Parameter.Tool.Translation.X, dimensions.a4y + data->Parameter.Tool.Translation.Y, dimensions.a4z + data->Parameter.Tool.Translation.Z}, a4Rotated[3],
	R[9];

	tcpPos[3] -= degreesToRadiansScara(data->Parameter.Tool.Orientation.Angle3);
	
	/* subtract offset a4 */
	(void)Rz(tcpPos[3], R);
	(void)Mat33Vec3Multiply(R, a4, a4Rotated);
	
	tcpPos[0] -= a4Rotated[0];
	tcpPos[1] -= a4Rotated[1];
	tcpPos[2] -= a4Rotated[2];

	a1 = dimensions.a1xy;
	a2 = 0.0;

	b1 = dimensions.a2xy;
	b2 = 0.0;

	c1 = tcpPos[0] - dimensions.a0x;
	c2 = tcpPos[1] - dimensions.a0y;

	switch (RphiAplusRpsiBequalC(a1, a2, b1, b2, c1, c2, &phi1, &psi1, &phi2, &psi2))
	{
		case 0: /* there exist no q2,q3 */
			data->Info.Status.Code = 1;
			return mcPATHGEN_CUSMECH_ERROR;

		case 255: /* everything is a solution for q2,q3 */
			data->Info.Status.Code = 2;
			return mcPATHGEN_CUSMECH_ERROR;

		case 254: /* phi is arbitrary - solvable to the future... */
		case 253: /* psi is arbitrary - solvable to the future... */
		case 252: /* there is a connection between q2,q3 - solvable to the future... */
			/* cannot be achieved by "real mechanics" of our type */
			data->Info.Status.Code = 3;
			return mcPATHGEN_CUSMECH_ERROR;

		case 1: /* the unique solution */
			data->Output.JointPos[0] = GoToWith2kpi(phi1       , jointRefPos[0]);
			data->Output.JointPos[1] = GoToWith2kpi(psi1 - phi1, jointRefPos[1]);

			break;

		default: /* there are two distinct solutions */

			qs1[0] = GoToWith2kpi(phi1       , jointRefPos[0]);
			qs1[1] = GoToWith2kpi(psi1 - phi1, jointRefPos[1]);

			qs2[0] = GoToWith2kpi(phi2       , jointRefPos[0]);
			qs2[1] = GoToWith2kpi(psi2 - phi2, jointRefPos[1]);

			unsigned long mode = LeftRight14(qs1[1]);
			
			if (mode == 0)
			{
				/* qs1 not in Left mode => take qs2 */
				data->Output.JointPos[0] = qs2[0];
				data->Output.JointPos[1] = qs2[1];
			}
			else if (mode == 1) 
			{
				/* qs1 in Left mode => take it */
				data->Output.JointPos[0] = qs1[0];
				data->Output.JointPos[1] = qs1[1];
			}
			else
			{
			    /* singularity */
				data->Info.Status.Code = 4;
				return mcPATHGEN_CUSMECH_ERROR;		
			}

			break;

	} /* end switch (RphiAplusRpsiBequalC) */

	/* C */
	data->Output.JointPos[3] = tcpPos[3] - data->Output.JointPos[0] - data->Output.JointPos[1];


	/* Z */
	data->Output.JointPos[2] = tcpPos[2] - (dimensions.a0z + dimensions.a1z + dimensions.a2z + dimensions.a3z);	
	
	/* convert to degrees */
	data->Output.JointPos[0] = radiansToDegreesScara(data->Output.JointPos[0]); 	
	data->Output.JointPos[1] = radiansToDegreesScara(data->Output.JointPos[1]); 	
	data->Output.JointPos[3] = radiansToDegreesScara(data->Output.JointPos[3]); 	
	
	return mcPATHGEN_CUSMECH_SUCCESS;	
}
