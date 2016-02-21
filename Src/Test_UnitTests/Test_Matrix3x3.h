#pragma once

#include "Test.h"

class Matrix3x3;
class Vector3;

class Test_Matrix3x3 : public Test {
protected:
	void setupTest();
	void teardownTest();

	static bool testCase_basics(void* data);
	static bool testCase_sum(void* data);
	static bool testCase_subtract(void* data);
	static bool testCase_index(void* data);
	static bool testCase_multiply(void* data);
	static bool testCase_transform(void* data);
	static bool testCase_inverse_det(void* data);
	static bool testCase_special_matrices(void* data);

	static bool checkEquality(const Matrix3x3& m, float* mdata);
	static bool checkEquality(const Matrix3x3& m1, const Matrix3x3& m2);
	static bool checkEquality(const Vector3& v1, const Vector3& v2);
};
