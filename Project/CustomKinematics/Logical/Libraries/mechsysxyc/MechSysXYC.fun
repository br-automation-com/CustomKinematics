
{REDUND_ERROR} FUNCTION degreesToRadians : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		valueInRadians : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION radiansToDegrees : LREAL (* *) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		valueInDegrees : LREAL;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customDirect : McPathGenCusMechStatusEnum (*Custom direct method*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechDirType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customInverse : McPathGenCusMechStatusEnum (*Custom inverse method*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechInvType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customDirectDerivative : McPathGenCusMechStatusEnum (*Custom direct method with derivatives*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechDirDerType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customInverseDerivative : McPathGenCusMechStatusEnum (*Custom inverse method with derivatives*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechInvDerType;
	END_VAR
END_FUNCTION

{REDUND_ERROR} FUNCTION customWireFrameModel : McPathGenCusMechStatusEnum (*Custom wire frame model implementation*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		data : McPathGenCusMechWMType;
	END_VAR
END_FUNCTION
