
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define True 1
#define False 0


void _INIT ProgramInit(void){
	mechDimensions = 650.0;
	
	transformTestIf.DirectPars.Parameter.JointCount = JointCount;
	transformTestIf.DirectPars.Parameter.TcpCount = TcpCount;
	transformTestIf.DirectPars.Parameter.MechDimensionsAddr = (UDINT)&mechDimensions;
	
	transformTestIf.InversePars.Parameter.JointCount = JointCount;
	transformTestIf.InversePars.Parameter.TcpCount = TcpCount;
	transformTestIf.InversePars.Parameter.MechDimensionsAddr = (UDINT)&mechDimensions;
	
	transformTestIf.DirectDerivativePars.Parameter.JointCount = JointCount;
	transformTestIf.DirectDerivativePars.Parameter.TcpCount = TcpCount;
	transformTestIf.DirectDerivativePars.Parameter.MechDimensionsAddr = (UDINT)&mechDimensions;
	
	transformTestIf.InverseDerivativePars.Parameter.JointCount = JointCount;
	transformTestIf.InverseDerivativePars.Parameter.TcpCount = TcpCount;
	transformTestIf.InverseDerivativePars.Parameter.MechDimensionsAddr = (UDINT)&mechDimensions;
	
	transformTestIf.DirectPars.Parameter.JointCount = JointCount;
	transformTestIf.DirectPars.Parameter.TcpCount = TcpCount;
	transformTestIf.DirectPars.Parameter.MechDimensionsAddr = (UDINT)&mechDimensions;
}
