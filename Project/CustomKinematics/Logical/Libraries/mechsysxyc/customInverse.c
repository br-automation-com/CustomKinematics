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
McPathGenCusMechStatusEnum customInverse(
	struct McPathGenCusMechInvType* data)
{	
	double  length = 650.0;
	
	double  X = data->Input.TcpPos[0];
	double  Y = data->Input.TcpPos[1];
	double  C = degreesToRadians(data->Input.TcpPos[2]);
	
	double  toolX = data->Parameter.Tool.Translation.X;
	double  toolY = data->Parameter.Tool.Translation.Y;
	double  toolC = degreesToRadians(data->Parameter.Tool.Orientation.Angle3);
		
	data->Output.JointPos[0] = X - cos(C - toolC) * toolX + sin(C - toolC) * (length + toolY);    // QX
	data->Output.JointPos[1] = Y - sin(C - toolC) * toolX - cos(C - toolC) * (length + toolY);    // QY
	data->Output.JointPos[2] = radiansToDegrees(C - toolC);                                       // QC
	
	if (data->Output.JointPos[1] > 700)
	{
		data->Info.Status.Code = 1002;
		return mcPATHGEN_CUSMECH_INFO;
	}	
	
	return mcPATHGEN_CUSMECH_SUCCESS;	
}
