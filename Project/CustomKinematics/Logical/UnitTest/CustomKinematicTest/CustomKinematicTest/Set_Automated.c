/********************************************************************
 * COPYRIGHT --
 ********************************************************************
 * Program: -
 * Author:
 * Created: 
 ********************************************************************
 * Tests for ... 
 ********************************************************************/

#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
#include <AsDefault.h>
#endif

#include "UnitTest.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define true 1
#define false 0

#define TIMEOUT_TEST_CASE									\
	if (cycleCount >= 400)									\
	{														\
		char abortMessage[80];								\
		char substate[10];									\
		memset(abortMessage, 0, sizeof(abortMessage));		\
		memset(substate, 0, sizeof(substate));				\
		itoa(ActSubState, substate, 10);					\
		strcpy(abortMessage, "Timeout in ActSubState = ");	\
		strcat(abortMessage, substate);						\
		TEST_FAIL(abortMessage);							\
		TEST_DONE;											\
	}

_CYCLIC_SET(){
	cycleCount++;
	return;
}

_SETUP_SET(void){
	TEST_DONE;
}

_TEARDOWN_SET(void){
	TEST_DONE;
}


_SETUP_TEST(void){
	cycleCount = 0;
	ActSubState = 0;
	//Clear out any old inputs
	memset(&testIf.DirectPars.Input.JointPos,0,sizeof(testIf.DirectPars.Input.JointPos));
	memset(&testIf.DirectPars.Input.TcpRefPos,0,sizeof(testIf.DirectPars.Input.TcpRefPos));
	TEST_DONE;
}

_TEARDOWN_TEST(void){
	/* TODO:  add code running after test case here */
	ActSubState = 0;
	TEST_DONE;
}


_TEST DirectHomeTest(void){
	TIMEOUT_TEST_CASE;
	switch (TestState){
		case TEST_ARRANGE:
			
			testIf.DirectPars.Input.JointPos[0] = 0;
			testIf.DirectPars.Input.JointPos[1] = 0;
			testIf.DirectPars.Input.JointPos[2] = 0;
			double length = 650.0;
			//TODO: pass in the length correctly to the input function
			cycleCount = 0;
			TestState = TEST_ACT;
			break;
		case TEST_ACT:		
			testIf.ReturnVal = customDirect(&testIf.DirectPars);
			TestState = TEST_ASSERT;
			break;		
		case TEST_ASSERT:
			TEST_ASSERT_EQUAL_DOUBLE(0,testIf.DirectPars.Output.TcpPos[0]);
			TEST_ASSERT_EQUAL_DOUBLE(650.0,testIf.DirectPars.Output.TcpPos[1]);
			TEST_ASSERT_EQUAL_DOUBLE(0,testIf.DirectPars.Output.TcpPos[2]);
			TEST_ASSERT_EQUAL_INT(mcPATHGEN_CUSMECH_SUCCESS,testIf.ReturnVal);

			TEST_DONE;
			break;
	}    
	TEST_BUSY;
}


/*
B+R UnitTest: This is generated code.
Do not edit! Do not move!
Description: UnitTest Testprogramm infrastructure (TestSet).
LastUpdated: 2024-02-21 13:50:44Z
By B+R UnitTest Helper Version: 2.0.1.59
*/
UNITTEST_FIXTURES(fixtures)
{
	new_TestFixture("DirectHomeTest", DirectHomeTest), 
};

UNITTEST_CALLER_COMPLETE_EXPLICIT(Set_Automated, "Set_Automated", setupTest, teardownTest, fixtures, setupSet, teardownSet, cyclicSetCaller);

