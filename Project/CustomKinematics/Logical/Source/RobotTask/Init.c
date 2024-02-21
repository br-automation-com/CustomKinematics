
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

#define True 1
#define False 0

void _INIT ProgramInit(void){
	dimensions = 650.0;
	robotFb.MpLink = &gRobot;
	robotFb.Parameters = &roboPars;
	robotFb.Override = 100;
	robotFb.Enable = True;
	MpRoboticsFlex(&robotFb);
}
