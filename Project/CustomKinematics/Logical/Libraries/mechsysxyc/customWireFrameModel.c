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

enum McPathGenCusMechStatusEnum customWireFrameModel(
	struct McPathGenCusMechWMType* data)
{
	double  qx = data->Input.JointPos[0];
	double  qy = data->Input.JointPos[1];
	double  qc = degreesToRadians(data->Input.JointPos[2]);

	double length = *(double*)data->Parameter.MechDimensionsAddr; //*(double*)data->Parameter.WfmDescriptionAddr; 
	
	data->Output.EdgeCount = 2; // wireframe model edges has to be calculated here by user based on JointPos
	data->Output.Edge[0].ID = 10001;
	data->Output.Edge[0].Distance = 0.5;
	data->Output.Edge[0].Point1.X = qx;
	data->Output.Edge[0].Point1.Y = 0;
	data->Output.Edge[0].Point1.Z = 0;
	data->Output.Edge[0].Point2.X = data->Output.Edge[0].Point1.X;
	data->Output.Edge[0].Point2.Y = data->Output.Edge[0].Point1.Y + qy;
	data->Output.Edge[0].Point2.Z = data->Output.Edge[0].Point1.Z;

	data->Output.Edge[1].ID = 10002;
	data->Output.Edge[1].Distance = 0.5;
	data->Output.Edge[1].Point1.X = data->Output.Edge[0].Point2.X;
	data->Output.Edge[1].Point1.Y = data->Output.Edge[0].Point2.Y;
	data->Output.Edge[1].Point1.Z = data->Output.Edge[0].Point2.Z;
	data->Output.Edge[1].Point2.X = data->Output.Edge[1].Point1.X - sin(qc) * (length);
	data->Output.Edge[1].Point2.Y = data->Output.Edge[1].Point1.Y + cos(qc) * (length);
	data->Output.Edge[1].Point2.Z = data->Output.Edge[1].Point1.Z;
	
	if (data->Parameter.CheckSelfCollision) // if check self collision flag on, user should compute/fill self collision structure type
	{
		// compute self collision
		//...some code here
		// self collision occured
		//		data->Info.SelfCollision.Detected = 1;
		//		data->Info.SelfCollision.EdgeID1 = 10001;
		//		data->Info.SelfCollision.EdgeID2 = 10002;
	}
	
	if (0/*computation failed*/) // if computation fail user has to fill this
	{
		data->Info.Status.Code = 12345ul;
		return mcPATHGEN_CUSMECH_ERROR;
	}

	return mcPATHGEN_CUSMECH_SUCCESS;
}