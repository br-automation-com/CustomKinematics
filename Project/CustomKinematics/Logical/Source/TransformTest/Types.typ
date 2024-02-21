
TYPE
	transformTestCmdTyp : 	STRUCT 
		RunDirect : BOOL;
		RunInverse : BOOL;
		RunDirectDerivative : BOOL;
		RunInverseDerivative : BOOL;
		RunWireframe : BOOL;
	END_STRUCT;
	transformTestIfTyp : 	STRUCT 
		Cmds : transformTestCmdTyp;
		DirectPars : McPathGenCusMechDirType;
		InversePars : McPathGenCusMechInvType;
		DirectDerivativePars : McPathGenCusMechDirDerType;
		InverseDerivativePars : McPathGenCusMechInvDerType;
		WireFramePars : McPathGenCusMechWMType;
		ReturnVal : McPathGenCusMechStatusEnum;
	END_STRUCT;
END_TYPE
