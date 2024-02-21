
{REDUND_ERROR} FUNCTION degreesToRadiansScara : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		valueInDegrees : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION radiansToDegreesScara : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		valueInRadians : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customDirectScara : McPathGenCusMechStatusEnum (*Custom direct method*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechDirType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customInverseScara : McPathGenCusMechStatusEnum (*Custom inverse method*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechInvType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customDirectDerivativeScara : McPathGenCusMechStatusEnum (*Custom direct method with derivatives*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechDirDerType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customInverseDerivativeScara : McPathGenCusMechStatusEnum (*Custom inverse method with derivatives*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechInvDerType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Rz : BOOL (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		a : LREAL;
		M : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Mat33Vec3Multiply : BOOL (*TODO: Add your comment here*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		A : REFERENCE TO LREAL;
		v : REFERENCE TO LREAL;
		w : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION RphiAplusRpsiBequalC : UDINT (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		a1 : LREAL;
		a2 : LREAL;
		b1 : LREAL;
		b2 : LREAL;
		c1 : LREAL;
		c2 : LREAL;
		phi1 : REFERENCE TO LREAL;
		psi1 : REFERENCE TO LREAL;
		phi2 : REFERENCE TO LREAL;
		psi2 : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION Mod2pi : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		alpha : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION GoToWith2kpi : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		alpha : LREAL;
		beta : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION jacobian : BOOL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		jointPos : REFERENCE TO LREAL;
		toolX : LREAL;
		toolY : LREAL;
		toolZ : LREAL;
		dimensions : CusMech_Scara4Ax_Dimensions;
		jacobianMatrix : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION MatVecMultiply : BOOL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		A : REFERENCE TO LREAL;
		v : REFERENCE TO LREAL;
		dimension : UDINT;
		w : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION invertMatrix44 : BOOL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		matrix : REFERENCE TO LREAL;
		matrixInverse : REFERENCE TO LREAL;
	END_VAR
END_FUNCTION
