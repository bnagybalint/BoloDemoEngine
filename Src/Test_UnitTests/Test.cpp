#include "Test.h"
#include <sstream>

void Test::run()
{
	setupTest();

	mSuccess = true;
	for (size_t i = 0; i < mTestCaseRunList.size(); i++)
	{
		std::string          tcName     = mTestCaseNameList[i];
		TestCaseSetupFunc    tcSetup    = mTestCaseSetupList[i];
		TestCaseFunc         tcRun      = mTestCaseRunList[i];
		TestCaseTeardownFunc tcTeardown = mTestCaseTeardownList[i];

		//log("Running test case");
		doIndent();

		void* tcData = NULL;
		if (tcSetup)
		{
			//log("Test case setup...");
			tcData = tcSetup();
			//log("Test case setup completed");
		}
		
		bool tcSuccess = tcRun(tcData);
		mSuccess = mSuccess && tcSuccess;

		if (tcSuccess)
			succeed(tcName);
		else
			fail(tcName);

		if (tcTeardown)
		{
			//log("Test case teardown...");
			tcTeardown(tcData);
			tcData = NULL;
			//log("Test case teardown completed");
		}

		undoIndent();
		//log("Test case finished");
	}

	teardownTest();
}

void Test::addTestCase(const std::string& name, TestCaseFunc tcFunc, TestCaseSetupFunc tcSetup, TestCaseTeardownFunc tcTeardown)
{
	mTestCaseNameList.push_back(name);
	mTestCaseSetupList.push_back(tcSetup);
	mTestCaseRunList.push_back(tcFunc);
	mTestCaseTeardownList.push_back(tcTeardown);
}

void Test::log(TestCaseResultEnum result, const std::string& check)
{
	std::stringstream s;
	switch (result)
	{
	case TestCaseResultEnum::Info:    s << "[INFO]"; break;
	case TestCaseResultEnum::Success: s << "[ OK ]"; break;
	case TestCaseResultEnum::Fail:    s << "[FAIL]"; break;
	default: Unimplemented();;
	}

	s << mCurrentInset;
	s << check;
	s << "\n";

	OutputDebugString(s.str().c_str());
}

void Test::doIndent()
{
	mCurrentInset = mCurrentInset + "  ";
}
void Test::undoIndent()
{
	mCurrentInset = mCurrentInset.substr(0, mCurrentInset.length()-2);
}

void TestSuite::addTest(Test* test)
{
	mTestCases.push_back(test);
}

void TestSuite::runTests()
{
	for (size_t i = 0; i < mTestCases.size(); i++)
	{
		mTestCases[i]->run();
	}
}