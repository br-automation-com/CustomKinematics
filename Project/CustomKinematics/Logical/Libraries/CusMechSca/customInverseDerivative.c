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

McPathGenCusMechStatusEnum customInverseDerivativeScara(struct McPathGenCusMechInvDerType* data)
{
	McPathGenCusMechInvType invData;
	McPathGenCusMechStatusEnum status;
	
	/* prepare data for inverse call */
	invData.Input.TcpPos[0] = data->Input.TcpPos[0];
	invData.Input.TcpPos[1] = data->Input.TcpPos[1];
	invData.Input.TcpPos[2] = data->Input.TcpPos[2];
	invData.Input.TcpPos[3] = data->Input.TcpPos[3];
	
	invData.Input.JointRefPos[0] = data->Input.JointRefPos[0];	
	invData.Input.JointRefPos[1] = data->Input.JointRefPos[1];	
	invData.Input.JointRefPos[2] = data->Input.JointRefPos[2];	
	invData.Input.JointRefPos[3] = data->Input.JointRefPos[3];	
	
	invData.Parameter.MechDimensionsAddr = data->Parameter.MechDimensionsAddr;
	invData.Parameter.Tool = data->Parameter.Tool;
	
	if ((status = customInverseScara(&invData)) == mcPATHGEN_CUSMECH_ERROR)
	{
		data->Info.Status.Code = invData.Info.Status.Code + 1000;
		return status;
	}
	
	CusMech_Scara4Ax_Dimensions* dimensions = (CusMech_Scara4Ax_Dimensions*)data->Parameter.MechDimensionsAddr;
	
	double jacobianMatrix[16], jacobianInverseMatrix[16];
	double jointPos[4] = {degreesToRadiansScara(invData.Output.JointPos[0]), degreesToRadiansScara(invData.Output.JointPos[1]), invData.Output.JointPos[2], degreesToRadiansScara(invData.Output.JointPos[3])};

	double jointDer[4];	
	
	/* compute jacobian from resulting jointPos */
	(void) jacobian(jointPos, data->Parameter.Tool.Translation.X, data->Parameter.Tool.Translation.Y, data->Parameter.Tool.Translation.Z, dimensions, jacobianMatrix);
	
	/* invert jacobian */
	if (invertMatrix44(jacobianMatrix, jacobianInverseMatrix) == 0)
	{
		data->Info.Status.Code = 1004;
		return mcPATHGEN_CUSMECH_ERROR;
	}
	
	/* compute joint derivatives out of tcp derivatives using Jacobian */
	MatVecMultiply(jacobianInverseMatrix, data->Input.TcpDer, 4, data->Output.JointDer);
		
	return status;
}
