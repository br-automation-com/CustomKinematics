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
McPathGenCusMechStatusEnum customDirectDerivative(struct McPathGenCusMechDirDerType* data)
{	
	double  length = 650.0;
	
	double  qC =  degreesToRadians(data->Input.JointPos[2]);
	
	double  qXd = data->Input.JointDer[0];
	double  qYd = data->Input.JointDer[1];
	double  qCd = degreesToRadians(data->Input.JointDer[2]);

	double  toolX = data->Parameter.Tool.Translation.X;
	double  toolY = data->Parameter.Tool.Translation.Y;
	
	data->Output.TcpDer[0] = qXd - sin(qC) * qCd * toolX - cos(qC) * qCd * (length + toolY);    // Xd
	data->Output.TcpDer[1] = qYd + cos(qC) * qCd * toolX - sin(qC) * qCd * (length + toolY);    // Yd 
	data->Output.TcpDer[2] = radiansToDegrees(qCd);                                             // Cd  
	
	return mcPATHGEN_CUSMECH_SUCCESS;
}
