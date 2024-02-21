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

/* customDirect - implements forward (direct) kinematic of the mechanical system
 *
 * Input: 
 *   JointPos - array - position of joints (dimension of the array: Parameter.JointCount) 
 * Output: 
 *   TcpPos - array - positions of TCP coordinates (dimension of the array: Parameter.PathCount)
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

McPathGenCusMechStatusEnum customDirectScara(struct McPathGenCusMechDirType* data)
{
	CusMech_Scara4Ax_Dimensions dimensions = *(CusMech_Scara4Ax_Dimensions*)data->Parameter.MechDimensionsAddr;
	
	double jointPos[4] = {degreesToRadiansScara(data->Input.JointPos[0]), degreesToRadiansScara(data->Input.JointPos[1]), data->Input.JointPos[2], degreesToRadiansScara(data->Input.JointPos[3])};
	
	double  phi = jointPos[0],
        	psi = M_PI - jointPos[0] - jointPos[1],
	        a4[3] = {dimensions.a4x + data->Parameter.Tool.Translation.X, dimensions.a4y + data->Parameter.Tool.Translation.Y, dimensions.a4z + data->Parameter.Tool.Translation.Z}, a4Rotated[3],
	        R[9];

	/* TCP.x, TCP.y */
	data->Output.TcpPos[0] = dimensions.a1xy * cos(phi) - dimensions.a2xy * cos(psi) + dimensions.a0x;
	data->Output.TcpPos[1] = dimensions.a1xy * sin(phi) + dimensions.a2xy * sin(psi) + dimensions.a0y;

	/* TCP.z */
	data->Output.TcpPos[2] = jointPos[2] + (dimensions.a0z + dimensions.a1z + dimensions.a2z + dimensions.a3z);

	/* TCP.alpha */
	data->Output.TcpPos[3] = jointPos[0] + jointPos[1] + jointPos[3];

	/* add offset a4 + tool translation */
	(void) Rz(data->Output.TcpPos[3], R);
	(void) Mat33Vec3Multiply(R, a4, a4Rotated);
	
	data->Output.TcpPos[0] += a4Rotated[0];
	data->Output.TcpPos[1] += a4Rotated[1];
	data->Output.TcpPos[2] += a4Rotated[2];

	/* addition of a tool */
	data->Output.TcpPos[3] += degreesToRadiansScara(data->Parameter.Tool.Orientation.Angle3);
	data->Output.TcpPos[3] = radiansToDegreesScara(data->Output.TcpPos[3]);

	return mcPATHGEN_CUSMECH_SUCCESS;
}
