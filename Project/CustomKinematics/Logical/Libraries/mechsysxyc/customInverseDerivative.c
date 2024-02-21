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

/* customInverseDerivative - implements inverse transformation for the first derivatives of the mechanical system
 *
 * Input:
 *   TcpPos - array - position of TCP coordinates (dimension of the array: Parameter.PathCount)
 *   TcpDer - array - derivative of TCP coordinates (dimension of the array: Parameter.PathCount)
 *   RefJointPos - array - last known positions of joints coordinates (dimension of the array: Parameter.JointCount)  
 * Output: 
 *   JointDer - array - first derivatives of joints (dimension of the array: Parameter.JointCount) 
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
McPathGenCusMechStatusEnum customInverseDerivative(struct McPathGenCusMechInvDerType* data)
{
	double  length = 650.0;
	
	double  X  = data->Input.TcpPos[0];
	double  Y  = data->Input.TcpPos[1];
	double  C  = degreesToRadians(data->Input.TcpPos[2]);
	
	double  Xd = data->Input.TcpDer[0];
	double  Yd = data->Input.TcpDer[1];
	double  Cd = degreesToRadians(data->Input.TcpDer[2]);
	
	double  toolX = data->Parameter.Tool.Translation.X;
	double  toolY = data->Parameter.Tool.Translation.Y;
	double  toolC = degreesToRadians(data->Parameter.Tool.Orientation.Angle3);

	data->Output.JointDer[0] = Xd + sin(C - toolC) * Cd * toolX + cos(C - toolC) * Cd * (length + toolY);  // qXd
	data->Output.JointDer[1] = Yd - cos(C - toolC) * Cd * toolX + sin(C - toolC) * Cd * (length + toolY);  // qYd
	data->Output.JointDer[2] = radiansToDegrees(Cd);                                                       // qCd
	
	return mcPATHGEN_CUSMECH_SUCCESS;
}
