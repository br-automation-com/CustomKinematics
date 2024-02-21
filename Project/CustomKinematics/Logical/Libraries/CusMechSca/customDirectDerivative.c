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

/* customDirectDerivative - implements forward (direct) transformation for the first derivatives of the mechanical system
 *
 * Input: 
 *   JointPos - array - position of joints (dimension of the array: Parameter.JointCount) 
 *   JointDer - array - first derivatives of joints (dimension of the array: Parameter.JointCount) 
 * Output: 
 *   TcpDer - array - derivative of TCP coordinates (dimension of the array: Parameter.PathCount)
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
McPathGenCusMechStatusEnum customDirectDerivativeScara(struct McPathGenCusMechDirDerType* data)
{	
	double jacobianMatrix[16];
	double tcpDer[4];
	
	double jointPos[4] = {degreesToRadiansScara(data->Input.JointPos[0]), degreesToRadiansScara(data->Input.JointPos[1]), data->Input.JointPos[2], degreesToRadiansScara(data->Input.JointPos[3])};
	
	CusMech_Scara4Ax_Dimensions* dimensions = (CusMech_Scara4Ax_Dimensions*)data->Parameter.MechDimensionsAddr;
	
	(void) jacobian(jointPos, data->Parameter.Tool.Translation.X, data->Parameter.Tool.Translation.Y, data->Parameter.Tool.Translation.Z, dimensions, jacobianMatrix);
	
	MatVecMultiply(jacobianMatrix, data->Input.JointDer, 4, data->Output.TcpDer);
	
	return mcPATHGEN_CUSMECH_SUCCESS;
}
