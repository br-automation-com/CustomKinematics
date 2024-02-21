
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define True 1
#define False 0

void _CYCLIC ProgramCyclic(void){
	if(transformTestIf.Cmds.RunDirect){
		transformTestIf.ReturnVal = customDirect(&transformTestIf.DirectPars);
		transformTestIf.Cmds.RunDirect = False;
	}
	
	if(transformTestIf.Cmds.RunInverse){
		transformTestIf.ReturnVal = customDirect(&transformTestIf.InversePars);
		transformTestIf.Cmds.RunDirect = False;
	}
	
	if(transformTestIf.Cmds.RunDirectDerivative){
		transformTestIf.ReturnVal = customDirect(&transformTestIf.DirectDerivativePars);
		transformTestIf.Cmds.RunDirect = False;
	}
	
	if(transformTestIf.Cmds.RunInverseDerivative){
		transformTestIf.ReturnVal = customDirect(&transformTestIf.InverseDerivativePars);
		transformTestIf.Cmds.RunDirect = False;
	}
	
	if(transformTestIf.Cmds.RunWireframe){
		transformTestIf.ReturnVal = customWireFrameModel(&transformTestIf.WireFramePars);
		transformTestIf.Cmds.RunDirect = False;
	}
}
