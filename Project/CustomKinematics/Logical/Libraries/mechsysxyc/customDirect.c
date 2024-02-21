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

McPathGenCusMechStatusEnum customDirect(struct McPathGenCusMechDirType* data){
	double  length = 650.0;
	
	double  qX = data->Input.JointPos[0];
	double  qY = data->Input.JointPos[1];
	double  qC = degreesToRadians(data->Input.JointPos[2]);

	double  toolX = data->Parameter.Tool.Translation.X;
	double  toolY = data->Parameter.Tool.Translation.Y;
	double  toolC = degreesToRadians(data->Parameter.Tool.Orientation.Angle3);
	
	data->Output.TcpPos[0] = qX + cos(qC) * toolX - sin(qC) * (length + toolY);    // X
	data->Output.TcpPos[1] = qY + sin(qC) * toolX + cos(qC) * (length + toolY);    // Y
	data->Output.TcpPos[2] = radiansToDegrees(qC + toolC);                         // C
	
	if (data->Output.TcpPos[0] > 800)
	{
		data->Info.Status.Code = 1001;
		return mcPATHGEN_CUSMECH_WARNING;
	}

	return mcPATHGEN_CUSMECH_SUCCESS;
}
