#include "Test_Matrix3x3.h"

#include "Assist/Math/Matrix3x3.hpp"
#include "Assist/Math/Vector3.hpp"


void Test_Matrix3x3::setupTest()
{

	addTestCase("testCase_basics     ", testCase_basics, NULL, NULL);
	//addTestCase("testCase_sum        ", testCase_sum, NULL, NULL);
	//addTestCase("testCase_subtract   ", testCase_subtract, NULL, NULL);
	addTestCase("testCase_index      ", testCase_index, NULL, NULL);
	addTestCase("testCase_multiply   ", testCase_multiply, NULL, NULL);
	addTestCase("testCase_transform  ", testCase_transform, NULL, NULL);
	addTestCase("testCase_inverse_det", testCase_inverse_det, NULL, NULL);

	doIndent();
	log("Running Matrix3x3 test cases");
}

void Test_Matrix3x3::teardownTest()
{
	log("Matrix3x3 test cases finished!");
	undoIndent();
}

/*static*/ bool Test_Matrix3x3::testCase_basics(void* data) {
	float md[] = {
		1, 2, 3, // 1 4 7
		4, 5, 6, // 2 5 8
		7, 8, 9	 // 3 6 9
	};

	Matrix3x3 m = Matrix3x3(md);
	const Matrix3x3 cm = Matrix3x3(md);

	bool b = true;
	b = b && checkRelation(m.at(0, 0), 1.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(0, 1), 4.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(0, 2), 7.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(1, 0), 2.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(1, 1), 5.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(1, 2), 8.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(2, 0), 3.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(2, 1), 6.0f, RelationEnum::Equal, Compare_WithLess<float>());
	b = b && checkRelation(m.at(2, 2), 9.0f, RelationEnum::Equal, Compare_WithLess<float>());
	return b;
}
/*static*/ bool Test_Matrix3x3::testCase_sum(void* data) {
	Unimplemented();
	return true;
}
/*static*/ bool Test_Matrix3x3::testCase_subtract(void* data) {
	Unimplemented();
	return true;
}
/*static*/ bool Test_Matrix3x3::testCase_index(void* data) {
	Unimplemented();
	return true;
}
/*static*/ bool Test_Matrix3x3::testCase_multiply(void* data) {
	float mdZero[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float mdId[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	float md1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	float md2[] = { 2, 0, 0, 0, 2, 0, 0, 0, 2 };
	float md3[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	float md4[] = { 1, 2, 1, 2, 3, 1, 3, 5, 7 };
	float md5[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float md6[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

	float mdr12[] = { 2, 4, 6, 8, 10, 12, 14, 16, 18 };
	float mdr13[] = { 24, 30, 36, 24, 30, 36, 24, 30, 36 };
	float mdr14[] = { 16, 20, 24, 21, 27, 33, 72, 87, 102 };
	float mdr23[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4 };
	float mdr24[] = { 2, 4, 2, 4, 6, 2, 6, 10, 14 };
	float mdr34[] = { 8, 8, 8, 12, 12, 12, 30, 30, 30 };


	Matrix3x3 mZero = Matrix3x3(mdZero);
	Matrix3x3 mId = Matrix3x3(mdId);
	Matrix3x3 m1 = Matrix3x3(md1);
	Matrix3x3 m2 = Matrix3x3(md2);
	Matrix3x3 m3 = Matrix3x3(md3);
	Matrix3x3 m4 = Matrix3x3(md4);
	Matrix3x3 m5 = Matrix3x3(md5);
	Matrix3x3 m6 = Matrix3x3(md6);

	struct TestMultiply
	{
		static bool test(const Matrix3x3& m1, const Matrix3x3& m2, float* expected)
		{
			Matrix3x3 r1 = m1 * m2;
			Matrix3x3 r2 = Matrix3x3::multiply(m1, m2);
			Matrix3x3 r3 = m1; r3.multiply(m2);

			bool b = true;
			b = b && checkEquality(r1, expected);
			b = b && checkEquality(r2, expected);
			b = b && checkEquality(r3, expected);
			return b;
		}
	};

	bool b = true;

	b = b && TestMultiply::test(mZero, mZero, mdZero);
	b = b && TestMultiply::test(mZero, mId, mdZero);
	b = b && TestMultiply::test(mId, mZero, mdZero);
	b = b && TestMultiply::test(mZero, m1, mdZero);

	b = b && TestMultiply::test(mId, mId, mdId);
	b = b && TestMultiply::test(mId, m1, md1);
	b = b && TestMultiply::test(mId, m2, md2);
	b = b && TestMultiply::test(mId, m3, md3);
	b = b && TestMultiply::test(mId, m4, md4);
	b = b && TestMultiply::test(mId, m5, md5);
	b = b && TestMultiply::test(mId, m6, md6);
	b = b && TestMultiply::test(m1, mId, md1);

	b = b && TestMultiply::test(m1, m2, mdr12);
	b = b && TestMultiply::test(m1, m3, mdr13);
	b = b && TestMultiply::test(m1, m4, mdr14);
	b = b && TestMultiply::test(m2, m3, mdr23);
	b = b && TestMultiply::test(m2, m4, mdr24);
	b = b && TestMultiply::test(m3, m4, mdr34);

	return b;
}
/*static*/ bool Test_Matrix3x3::testCase_transform(void* data) {
	float mdZero[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float mdId[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	float md1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	float md2[] = { 2, 0, 0, 0, 2, 0, 0, 0, 2 };
	float md3[] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
	float md4[] = { 1, 2, 1, 2, 3, 1, 3, 5, 7 };

	Matrix3x3 mZero = Matrix3x3(mdZero);
	Matrix3x3 mId = Matrix3x3(mdId);
	Matrix3x3 m1 = Matrix3x3(md1);
	Matrix3x3 m2 = Matrix3x3(md2);
	Matrix3x3 m3 = Matrix3x3(md3);
	Matrix3x3 m4 = Matrix3x3(md4);

	Vector3 v1 = Vector3(0, 0, 0);
	Vector3 v2 = Vector3(1, 0, 0);
	Vector3 v3 = Vector3(0, 1, 0);
	Vector3 v4 = Vector3(0, 0, 1);
	Vector3 v5 = Vector3(1, 1, 1);
	Vector3 v6 = Vector3(1, 2, 3);

	struct TestTransform
	{
		static bool test(const Matrix3x3& m, const Vector3& v, const Vector3& res)
		{
			Vector3 r1 = m * v;
			Vector3 r2 = Matrix3x3::transform(m, v);
			Vector3 r3 = m.transform(v);

			bool b = true;
			b = b && checkEquality(r1, res);
			b = b && checkEquality(r2, res);
			b = b && checkEquality(r3, res);
			return b;
		}
	};

	bool b = true;

	b = b && TestTransform::test(mZero, v1, Vector3(0, 0, 0));
	b = b && TestTransform::test(mZero, v2, Vector3(0, 0, 0));
	b = b && TestTransform::test(mZero, v3, Vector3(0, 0, 0));
	b = b && TestTransform::test(mZero, v4, Vector3(0, 0, 0));
	b = b && TestTransform::test(mZero, v5, Vector3(0, 0, 0));
	b = b && TestTransform::test(mZero, v6, Vector3(0, 0, 0));

	b = b && TestTransform::test(mId, v1, v1);
	b = b && TestTransform::test(mId, v2, v2);
	b = b && TestTransform::test(mId, v3, v3);
	b = b && TestTransform::test(mId, v4, v4);
	b = b && TestTransform::test(mId, v5, v5);
	b = b && TestTransform::test(mId, v6, v6);

	b = b && TestTransform::test(m2, v1, 2.0f*v1);
	b = b && TestTransform::test(m2, v2, 2.0f*v2);
	b = b && TestTransform::test(m2, v3, 2.0f*v3);
	b = b && TestTransform::test(m2, v4, 2.0f*v4);
	b = b && TestTransform::test(m2, v5, 2.0f*v5);
	b = b && TestTransform::test(m2, v6, 2.0f*v6);

	b = b && TestTransform::test(m1, v1, Vector3(0, 0, 0));
	b = b && TestTransform::test(m2, v1, Vector3(0, 0, 0));
	b = b && TestTransform::test(m3, v1, Vector3(0, 0, 0));
	b = b && TestTransform::test(m4, v1, Vector3(0, 0, 0));

	b = b && TestTransform::test(m1, v2, m1.getColumn(0));
	b = b && TestTransform::test(m2, v2, m2.getColumn(0));
	b = b && TestTransform::test(m3, v2, m3.getColumn(0));
	b = b && TestTransform::test(m4, v2, m4.getColumn(0));

	b = b && TestTransform::test(m1, v3, m1.getColumn(1));
	b = b && TestTransform::test(m2, v3, m2.getColumn(1));
	b = b && TestTransform::test(m3, v3, m3.getColumn(1));
	b = b && TestTransform::test(m4, v3, m4.getColumn(1));

	b = b && TestTransform::test(m1, v4, m1.getColumn(2));
	b = b && TestTransform::test(m2, v4, m2.getColumn(2));
	b = b && TestTransform::test(m3, v4, m3.getColumn(2));
	b = b && TestTransform::test(m4, v4, m4.getColumn(2));

	b = b && TestTransform::test(m1, v5, Vector3(12,15,18));
	b = b && TestTransform::test(m2, v5, Vector3(2,2,2));
	b = b && TestTransform::test(m3, v5, Vector3(6,6,6));
	b = b && TestTransform::test(m4, v5, Vector3(6,10,9));

	b = b && TestTransform::test(m1, v6, Vector3(30,36,42));
	b = b && TestTransform::test(m2, v6, Vector3(2,4,6));
	b = b && TestTransform::test(m3, v6, Vector3(12,12,12));
	b = b && TestTransform::test(m4, v6, Vector3(14,23,24));

	return b;

}
/*static*/ bool Test_Matrix3x3::testCase_inverse_det(void* data) {
	float mdZero[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float mdId[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	float md1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 10 };
	float md2[] = { 2, 0, 0, 0, 2, 0, 0, 0, 2 };

	float detrZero = 0;  float mdrZero[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	float detrId   = 1;  float mdrId[] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	float detr1    = -3; float mdr1[] = { -2, -4, 3, -2, 11, -6, 3, -6, 3 }; for (int i = 0; i < 9; i++) mdr1[i] *= 0.3333333333333f;
	float detr2    = 8;  float mdr2[] = { 0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5 };

	Matrix3x3 mZero = Matrix3x3(mdZero);
	Matrix3x3 mId   = Matrix3x3(mdId);
	Matrix3x3 m1    = Matrix3x3(md1);
	Matrix3x3 m2    = Matrix3x3(md2);

	bool b = true;

	b = b && checkRelation(mZero.determinant(), detrZero, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
	b = b && checkRelation(mId.determinant(), detrId, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
	b = b && checkRelation(m1.determinant(), detr1, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
	b = b && checkRelation(m2.determinant(), detr2, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));

	//Matrix3x3 mrZero = Matrix3x3::inverse(mZero);
	Matrix3x3 mrId = Matrix3x3::inverse(mId);
	Matrix3x3 mr1 = Matrix3x3::inverse(m1);
	Matrix3x3 mr2 = Matrix3x3::inverse(m2);

	//b = b && checkEquality(mrZero, mdrZero);
	b = b && checkEquality(mrId, mdrId);
	b = b && checkEquality(mr1, mdr1);
	b = b && checkEquality(mr2, mdr2);
	return b;
}

/*static*/ bool Test_Matrix3x3::testCase_special_matrices(void* data)
{

	Vector3 x = Vector3::UNIT_X;
	Vector3 y = Vector3::UNIT_Y;
	Vector3 z = Vector3::UNIT_Z;

	Matrix3x3 mId = Matrix3x3::IDENTITY;
	Matrix3x3 mZero = Matrix3x3::ZERO;

	Matrix3x3 mRotx90 = Matrix3x3::createFromRotation(Math::Deg2Rad(90), x);
	Matrix3x3 mRoty90 = Matrix3x3::createFromRotation(Math::Deg2Rad(90), y);
	Matrix3x3 mRotz90 = Matrix3x3::createFromRotation(Math::Deg2Rad(90), z);

	Matrix3x3 mRotx180 = Matrix3x3::createFromRotation(Math::Deg2Rad(180), x);
	Matrix3x3 mRoty180 = Matrix3x3::createFromRotation(Math::Deg2Rad(180), y);
	Matrix3x3 mRotz180 = Matrix3x3::createFromRotation(Math::Deg2Rad(180), z);

	Matrix3x3 mRotx_90 = Matrix3x3::createFromRotation(Math::Deg2Rad(-90), x);
	Matrix3x3 mRoty_90 = Matrix3x3::createFromRotation(Math::Deg2Rad(-90), y);
	Matrix3x3 mRotz_90 = Matrix3x3::createFromRotation(Math::Deg2Rad(-90), z);
	
	Matrix3x3 mRotx_90_alt = Matrix3x3::createFromRotation(Math::Deg2Rad(90), -x);
	Matrix3x3 mRoty_90_alt = Matrix3x3::createFromRotation(Math::Deg2Rad(90), -y);
	Matrix3x3 mRotz_90_alt = Matrix3x3::createFromRotation(Math::Deg2Rad(90), -z);

	Matrix3x3 mRotx90_b = Matrix3x3::createFromBasis(x,z,-y);
	Matrix3x3 mRoty90_b = Matrix3x3::createFromBasis(-z,y,x);
	Matrix3x3 mRotz90_b = Matrix3x3::createFromBasis(y,-x,z);

	Matrix3x3 mRotx_90_b = Matrix3x3::createFromBasis(x, -z, y);
	Matrix3x3 mRoty_90_b = Matrix3x3::createFromBasis(z, y, -x);
	Matrix3x3 mRotz_90_b = Matrix3x3::createFromBasis(-y, x, z);

	Matrix3x3 mScx2 = Matrix3x3::createFromScale(Vector3(2,1,1));
	Matrix3x3 mScy2 = Matrix3x3::createFromScale(Vector3(1,2,1));
	Matrix3x3 mScz2 = Matrix3x3::createFromScale(Vector3(1,1,2));

	bool b = true;

	b = b && checkEquality(mRotx_90, mRotx_90_alt);
	b = b && checkEquality(mRoty_90, mRoty_90_alt);
	b = b && checkEquality(mRotz_90, mRotz_90_alt);

	b = b && checkEquality(mRotx_90, mRotx_90_b);
	b = b && checkEquality(mRoty_90, mRoty_90_b);
	b = b && checkEquality(mRotz_90, mRotz_90_b);

	b = b && checkEquality(mRotx90, mRotx90_b);
	b = b && checkEquality(mRoty90, mRoty90_b);
	b = b && checkEquality(mRotz90, mRotz90_b);

	b = b && checkEquality(mId*x, x);
	b = b && checkEquality(mId*y, y);
	b = b && checkEquality(mId*z, z);

	b = b && checkEquality(mZero*x, Vector3::ZERO);
	b = b && checkEquality(mZero*y, Vector3::ZERO);
	b = b && checkEquality(mZero*z, Vector3::ZERO);

	b = b && checkEquality(mRotx90*x, x);
	b = b && checkEquality(mRotx90*y, z);
	b = b && checkEquality(mRotx90*z, -y);

	b = b && checkEquality(mRoty90*x, -z);
	b = b && checkEquality(mRoty90*y, y);
	b = b && checkEquality(mRoty90*z, x);

	b = b && checkEquality(mRotz90*x, y);
	b = b && checkEquality(mRotz90*y, -x);
	b = b && checkEquality(mRotz90*z, z);

	b = b && checkEquality(mRotx180*x, x);
	b = b && checkEquality(mRotx180*y, -y);
	b = b && checkEquality(mRotx180*z, -z);

	b = b && checkEquality(mRoty180*x, -z);
	b = b && checkEquality(mRoty180*y, y);
	b = b && checkEquality(mRoty180*z, -x);

	b = b && checkEquality(mRotz180*x, -y);
	b = b && checkEquality(mRotz180*y, -x);
	b = b && checkEquality(mRotz180*z, z);


	return b;
}

/*static*/ bool Test_Matrix3x3::checkEquality(const Matrix3x3& m, float* mdata)
{
	return checkRelationArray(9, m.getData(), mdata, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
}

/*static*/ bool Test_Matrix3x3::checkEquality(const Matrix3x3& m1, const Matrix3x3& m2)
{
	return checkRelationArray(9, m1.getData(), m2.getData(), RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
}

/*static*/ bool Test_Matrix3x3::checkEquality(const Vector3& v1, const Vector3& v2)
{
	float v1d[4];  v1.xyz(v1d);
	float v2d[4];  v2.xyz(v2d);

	return checkRelationArray(3, v1d, v2d, RelationEnum::Equal, Compare_FloatEpsilon<float>(1e-3f));
}
