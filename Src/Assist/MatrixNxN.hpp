/* ------------------------------------------------ *
 *  Written by:      Nagy Balint                    *
 *  Contact:         b.nagy.balint@gmail.com        *
 *                                                  *
 *  This file can be used/improved/redistributed    *
 *  under GNU public license                        *
 *                                                  *
 *  Nagy Balint (C) 2015                            *
 * ------------------------------------------------ */

#ifndef MATRIXNXN_HPP_
#define MATRIXNXN_HPP_

#include "Assist/Common.h"
#include "Assist/MathCommon.h"
#include "Assist/Memory.h"

// Represents a matrix of 3x3 floats.
//
// Logical layout of the matrix:
// 
//    [ m00 m01 m02 ]
//    [ m10 m11 m12 ]
//    [ m20 m21 m22 ]
// 
// Usage:
// 
//   Usage of this class conforms to the use of matrices in most mathematical 
//   papers. This was a design decision that has the benefit of understandability.
//	 
//   - Vectors passed (e.g. for matrix-vector multiplication) are interpreted as
//     column vectors. This means that vectors are left-multiplied by the matrix:
//                 [ m00, m01, m02 ]   [ vx ]   [ m00*vx + m01*vy + m02*vz ]
//        M1 * v = [ m10, m11, m12 ] * [ vy ] = [ m10*vx + m11*vy + m12*vz ]
//                 [ m20, m21, m22 ]   [ vz ]   [ m20*vx + m21*vy + m22*vz ]
//
//   - Matrix multiplication is applied in the order it is written (matrix on the
//     left side is left-multiplies to the matrix on the right side):
//                [ f00, f01, f02 ]   [ g00, g01, g02 ]   [ f00*g00 + f01*g10 + f02*g20 ]
//        F * G = [ f10, f11, f12 ] * [ g10, g11, g12 ] = [ f10*g00 + f11*g10 + f22*g20 ]
//                [ f20, f21, f22 ]   [ g20, g21, g22 ]   [ f20*g00 + f21*g10 + f22*g20 ]
//     In other words: the ij'th element of the resulting matrix will be the 
//     scalar product row i of the matrix on the left and column j of the matrix
//     on the right.
//
//   - Because of the following two properties, the following is true:
//        F * G * v = 
//        F * (G*v) =
//        (F*G) * v
//
//   - Also, we can interpret a matrix multiplication chain as follows
//     (right-to-left notation):
//        M1 * M2 * M3 * v0 = v3
//     if 
//        v1 := M3 * v0;
//        v2 := M2 * v1;
//        vr := M1 * v2;
//
// Remarks:
// 
//    When designing the class and its inner workings I wanted to create a memory 
//    layout, that can be directly passed/converted to DirectX (without the need 
//    for matrix transpose). For this reason, the memory layout looks like this:
//       [ m00, m10, m20 ]
//       [ m01, m11, m21 ]
//       [ m02, m12, m22 ]
//    or in flat view:
//       [ m00, m10, m20, m01, m11, m21, m02, m12, m22 ]
//    This has the disadvantage that some interface methods are not trivial and 
//    they differ from the notation above. These methods are marked with a warning 
//    and should be used carefully.
//

#define mxidx(row, col) ((col)*msNumCols + (row))
//#define mxidx(row, col) ((row)*msNumRows + (col))

template <int Dim>
class MatrixNxN {

public:

	// constructors, destructor
	MatrixNxN();
	explicit MatrixNxN(Coordtype fill);
	explicit MatrixNxN(const Coordtype* data); // WARNING read doc before using this method
	MatrixNxN(const MatrixNxN& m);
	virtual ~MatrixNxN();

	// copy, clear and fill
	MatrixNxN&        copy(const MatrixNxN& m);
	MatrixNxN&        clear();
	MatrixNxN&        fill(Coordtype value);

	// ####################################

	// addition
	MatrixNxN        sum(const MatrixNxN& m) const;
	// subtraction
	MatrixNxN        subtract(const MatrixNxN& m) const;
	// multiply
	MatrixNxN        multiply(const MatrixNxN& m) const;

	// ####################################

	// index functions
	Coordtype&        at(int row, int column);
	Coordtype         at(int row, int column) const;

	// ####################################

	// operators overloaded
	MatrixNxN&        operator =  (const MatrixNxN& m);       // set
	bool              operator == (const MatrixNxN& m) const; // equal
	bool              operator != (const MatrixNxN& m) const; // not equal

	MatrixNxN         operator -  () const;                   // unary minus

	MatrixNxN         operator +  (const MatrixNxN& m) const; // sum
	MatrixNxN         operator -  (const MatrixNxN& m) const; // subtract
	MatrixNxN         operator *  (const MatrixNxN& m) const; // multiply
	MatrixNxN         operator *  (Coordtype lambda) const;   // multiply by scalar
	MatrixNxN         operator /  (Coordtype lambda) const;   // divide by scalar

	MatrixNxN&        operator += (const MatrixNxN& m);       // "increase"
	MatrixNxN&        operator -= (const MatrixNxN& m);       // "decrease"
	MatrixNxN&        operator *= (const MatrixNxN& m);       // "concatenate"
	MatrixNxN&        operator *= (Coordtype lambda);         // "multiply by scalar"
	MatrixNxN&        operator /= (Coordtype lambda);         // "divide by scalar"

	Coordtype         operator () (int row, int column) const;// simplified index operator
	Coordtype&        operator () (int row, int column);      // simplified index operator

	// ####################################

	// data getters
	operator const Coordtype* () const; // WARNING read doc before using this method
	operator Coordtype* ();             // WARNING read doc before using this method
	const Coordtype*  getData() const;  // WARNING read doc before using this method
	Coordtype*        getData();        // WARNING read doc before using this method

	// protected:

	static const int msNumRows     = Dim;
	static const int msNumCols     = Dim;
	static const int msNumElements = Dim * Dim;

	// array holding the data for the matrix
	Coordtype mx[msNumRows*msNumRows];

	// friend functions
	friend MatrixNxN operator * (Coordtype lambda, const MatrixNxN& m);

}; /* class MatrixNxN */

// outer functions
template <int Dim>
MatrixNxN<Dim> operator * (Coordtype lambda, const MatrixNxN<Dim>& m);  // multiply by scalar

// ====================================================================
// ====================================================================

template<int Dim>
MatrixNxN<Dim>::MatrixNxN() { }

template<int Dim>
MatrixNxN<Dim>::MatrixNxN(Coordtype fill) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = fill;
}

template<int Dim>
MatrixNxN<Dim>::MatrixNxN(const Coordtype* data)
{
	Memory::Memcopy(mx, data, msNumElements * sizeof(Coordtype));
}

template<int Dim>
MatrixNxN<Dim>::MatrixNxN(const MatrixNxN& m) {
	Memory::Memcopy(mx, m.mx, msNumElements * sizeof(Coordtype));
}

template<int Dim>
MatrixNxN<Dim>::~MatrixNxN() {
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::copy(const MatrixNxN<Dim>& m) {
	Memory::Memcopy(mx, m.mx, msNumElements * sizeof(Coordtype));
	return *this;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::clear() {
	Memory::Memset(mx, 0x00, msNumElements * sizeof(Coordtype));
	return *this;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::fill(Coordtype value) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] = value;
	return *this;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::sum(const MatrixNxN<Dim>& m) const {
	MatrixNxN r;
	for (unsigned int i = 0; i < msNumElements; ++i)
		r.mx[i] = mx[i] + m.mx[i];
	return r;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::subtract(const MatrixNxN<Dim>& m) const {
	MatrixNxN<Dim> r;
	for (unsigned int i = 0; i < msNumElements; ++i)
		r.mx[i] = mx[i] - m.mx[i];
	return r;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::multiply(const MatrixNxN<Dim>& m) const {
	MatrixNxN<Dim> rv;
	for (int i = 0; i < msNumRows; i++) {
		for (int j = 0; j < msNumCols; j++) {
			Coordtype r = Coordtype(0);
			for (int k = 0; k < msNumRows; k++)
				r += mx[mxidx(i, k)] * m.mx[mxidx(k, j)];
			rv.mx[mxidx(i, j)] = r;
		}
	}
	return rv;
}

template<int Dim>
Coordtype& MatrixNxN<Dim>::at(int row, int col) {
	Assert(row >= 0 && row <= msNumRows - 1);
	Assert(col >= 0 && col <= msNumCols - 1);
	return mx[mxidx(row, col)];
}

template<int Dim>
Coordtype MatrixNxN<Dim>::at(int row, int col) const {
	Assert(row >= 0 && row <= msNumRows - 1);
	Assert(col >= 0 && col <= msNumCols - 1);
	return mx[mxidx(row, col)];
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator = (const MatrixNxN<Dim>& m) {
	if (this != &m)
		Memory::Memcopy(mx, m.mx, msNumElements * sizeof(Coordtype));
	return *this;
}

template<int Dim>
bool MatrixNxN<Dim>::operator == (const MatrixNxN<Dim>& m) const {
	for (unsigned int i = 0; i < msNumElements; ++i) {
		if (mx[i] != m.mx[i]) {
			return false;
		}
	}
	return true;
}

template<int Dim>
bool MatrixNxN<Dim>::operator != (const MatrixNxN<Dim>& m) const {
	for (unsigned int i = 0; i < msNumElements; ++i) {
		if (mx[i] != m.mx[i]) {
			return true;
		}
	}
	return false;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator - () const {
	MatrixNxN<Dim> r;
	for (unsigned int i = 0; i < msNumElements; ++i) {
		r.mx[i] = -mx[i];
	}
	return r;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator + (const MatrixNxN<Dim>& m) const {
	return sum(m);
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator - (const MatrixNxN<Dim>& m) const {
	return subtract(m);
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator * (const MatrixNxN<Dim>& m) const {
	return multiply(m);
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator * (Coordtype lambda) const {
	MatrixNxN<Dim> r;
	for (unsigned int i = 0; i < msNumElements; ++i) {
		r.mx[i] = mx[i] * lambda;
	}
	return r;
}

template<int Dim>
MatrixNxN<Dim> MatrixNxN<Dim>::operator / (Coordtype lambda) const {
	MatrixNxN<Dim> r;
	for (unsigned int i = 0; i < msNumElements; ++i) {
		r.mx[i] = mx[i] / lambda;
	}
	return r;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator += (const MatrixNxN<Dim>& m) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] += m.mx[i];
	return *this;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator -= (const MatrixNxN<Dim>& m) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] -= m.mx[i];
	return *this;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator *= (const MatrixNxN<Dim>& m) {
	operator = (multiply(m));
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator *= (Coordtype lambda) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] *= lambda;
	return *this;
}

template<int Dim>
MatrixNxN<Dim>& MatrixNxN<Dim>::operator /= (Coordtype lambda) {
	for (unsigned int i = 0; i < msNumElements; ++i)
		mx[i] /= lambda;
	return *this;
}

template<int Dim>
Coordtype MatrixNxN<Dim>::operator () (int row, int col) const {
	Assert(row >= 0 && row <= msNumRows - 1);
	Assert(col >= 0 && col <= msNumCols - 1);
	return mx[mxidx(row, col)];
}

template<int Dim>
Coordtype& MatrixNxN<Dim>::operator () (int row, int col) {
	Assert(row >= 0 && row <= msNumRows - 1);
	Assert(col >= 0 && col <= msNumCols - 1);
	return mx[mxidx(row, col)];
}

template<int Dim>
MatrixNxN<Dim>::operator const Coordtype* () const {
	Unimplemented(); // do not use this
	return mx;
}

template<int Dim>
MatrixNxN<Dim>::operator Coordtype* () {
	Unimplemented(); // do not use this
	return mx;
}

template<int Dim>
const Coordtype* MatrixNxN<Dim>::getData() const
{
	return mx;
}

template<int Dim>
Coordtype* MatrixNxN<Dim>::getData()
{
	return mx;
}

template<int Dim>
MatrixNxN<Dim> operator *  (Coordtype lambda, const MatrixNxN<Dim>& m) {

	return m.operator * (lambda);
}

#endif /* MATRIXNXN_HPP_ */
