#pragma once

#include "Assist/Common.h"

#include <string>
#include <vector>

template <class T>
struct Compare_WithLess {
	int operator() (const T& a, const T& b) const;
};

template <class FloatType>
struct Compare_FloatEpsilon {
	explicit Compare_FloatEpsilon(FloatType eps) :mEpsilon(eps) {}

	int operator() (FloatType a, FloatType b) const;

	FloatType mEpsilon;
};

class Test {
public:

	EnumBegin(RelationEnum, Equal)
		Equal,
		Less,
		Greater,
	EnumEnd(RelationEnum)

	EnumBegin(TestCaseResultEnum, Info)
		Info,
		Success,
		Fail,
	EnumEnd(TestCaseResultEnum)

	typedef void* (*TestCaseSetupFunc)(void);
	typedef bool (*TestCaseFunc)(void* data);
	typedef void (*TestCaseTeardownFunc)(void* data);

public:
	Test() :mCurrentInset(""), mSuccess(false){}
	void run();
	bool succeeded() const { return mSuccess; }
protected:

	virtual void setupTest() = 0;
	virtual void teardownTest() = 0;

	void addTestCase(const std::string& name, TestCaseFunc tcFunc, TestCaseSetupFunc tcSetup = NULL, TestCaseTeardownFunc tcTeardown = NULL);

	template <class T, class CompareFunctor>
	static bool checkRelation(const T&, const T&, RelationEnum expected, const CompareFunctor& compare);
	template <class T, class CompareFunctor>
	static bool checkRelationArray(size_t num, const T*, const T*, enum RelationEnum expected, const CompareFunctor& compare);

	void log(TestCaseResultEnum result, const std::string& check);
	void log(const std::string& check) { log(TestCaseResultEnum::Info, check); }
	void fail(const std::string& check) { log(TestCaseResultEnum::Fail, check); }
	void succeed(const std::string& check) { log(TestCaseResultEnum::Success, check); }

	void doIndent();
	void undoIndent();

private:
	std::string mCurrentInset;
	bool mSuccess;
	std::vector<std::string>          mTestCaseNameList;
	std::vector<TestCaseSetupFunc>    mTestCaseSetupList;
	std::vector<TestCaseFunc>         mTestCaseRunList;
	std::vector<TestCaseTeardownFunc> mTestCaseTeardownList;
};

class TestSuite
{
public:
	void addTest(Test* test);
	void runTests();
private:
	std::vector<Test*> mTestCases;
};

template <class T>
int Compare_WithLess<T>::operator() (const T& a, const T& b) const
{
	std::less<T> l;
	if (l(a, b))
		return -1;
	if (l(b, a))
		return 1;
	return 0;
}

template <class FloatType>
int Compare_FloatEpsilon<FloatType>::operator() (FloatType a, FloatType b) const
{
	FloatType diff = Math::Abs(a - b);

	if (diff < mEpsilon)
		return 0;
	return a < b;
}

template <class T, class CompareFunctor>
bool Test::checkRelation(const T& a, const T& b, RelationEnum expected, const CompareFunctor& compare){
	return compare(a, b) == expected;
}
template <class T, class CompareFunctor>
bool Test::checkRelationArray(size_t num, const T* aPtr, const T* bPtr, enum RelationEnum expected, const CompareFunctor& compare)
{
	bool rv = true;
	for (size_t i = 0; i < num; i++)
		rv = rv && checkRelation(*aPtr++, *bPtr++, expected, compare);
	return rv;
}

