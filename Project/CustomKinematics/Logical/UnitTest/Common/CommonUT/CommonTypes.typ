
TYPE
	TestCaseEnum : 
		(
		TEST_ARRANGE,
		TEST_ACT,
		TEST_ASSERT
		);
	transformTestIfTyp : 	STRUCT 
		DirectPars : McPathGenCusMechDirType;
		InversePars : McPathGenCusMechInvType;
		DirectDerivativePars : McPathGenCusMechDirDerType;
		InverseDerivativePars : McPathGenCusMechInvDerType;
		ReturnVal : McPathGenCusMechStatusEnum;
	END_STRUCT;
END_TYPE
