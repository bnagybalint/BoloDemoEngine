
#include <windows.h>
#include "Test.h"

#include "Test_Matrix3x3.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	TestSuite suite;

	Test_Matrix3x3 test_mx3;
	suite.addTest(&test_mx3);

	suite.runTests();

	return 0;
}