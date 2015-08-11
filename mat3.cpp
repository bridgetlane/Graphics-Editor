/*
 *  mat3.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Implements a 3x3 matrix
 *
 */

#include <iostream>			// input/output
#include <assert.h>			// assert
#include <cmath>			// math
#include "mat3.h"			// declaration of mat3

using namespace std;		// for printing

#define MAT_START	0
#define	MAT_END		2
#define PI			3.14159
#define	POSZERO		0.00001
#define	NEGZERO		-0.00001

// constructors
mat3::mat3()
{
	vec3 v;
	vec3 v1;
	vec3 v2;

	data[0] = v;
	data[1] = v1;
	data[2] = v2;
}

mat3::mat3(const vec3& row1, const vec3& row2, const vec3& row3)
{
	data[0] = row1;
	data[1] = row2;
	data[2] = row3;
}

// get a row
vec3 
mat3::operator[](unsigned int index) const 
{
	assert(index >= MAT_START);
	assert(index <= MAT_END);
	vec3 row = data[index];
	return row;
}

// set a row
vec3& 
mat3::operator[](unsigned int index)
{
	assert(index >= MAT_START);
	assert(index <= MAT_END);
	return data[index];
}

// get one column
vec3 
mat3::getColumn(unsigned int index) const
{
	assert(index >= MAT_START);
	assert(index <= MAT_END);
	vec3 col(data[0][index], data[1][index], data[2][index]);
	return col;
}

// print the matrix
void 
mat3::print()
{
	data[0].print();
	data[1].print();
	data[2].print();
}

// transpose (v_ij == v_ji)
mat3 
mat3::transpose() const
{
	mat3 t;
	t[0] = getColumn(0);
	t[1] = getColumn(1);
	t[2] = getColumn(2);
	return t;
}

// checks if m1 == m2, using epsilon for equivalency testing
bool
operator==(const mat3& m1, const mat3& m2)
{
	if ((m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// checks if m1 != m2, using epsilon for equivalency testing
bool
operator!=(const mat3& m1, const mat3& m2)
{
	if ((m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// matrix addition (m1 + m2)
mat3
operator+ (const mat3& m1, const mat3& m2)
{
	mat3 add;
	add[0] = m1[0] + m2[0];
	add[1] = m1[1] + m2[1];
	add[2] = m1[2] + m2[2];
	return add;
}

// matrix subtraction (m1 - m2)
mat3 
operator- (const mat3& m1, const mat3& m2)
{
	mat3 sub;
	sub[0] = m1[0] - m2[0];
	sub[1] = m1[1] - m2[1];
	sub[2] = m1[2] - m2[2];
	return sub;
}

// scalar multiplication (m * c)
mat3
operator* (const mat3& m, float c)
{
	mat3 mult;
	mult[0] = m[0] * c;
	mult[1] = m[1] * c;
	mult[2] = m[2] * c;
	return mult;
}

// scalar multiplication (c * m)
mat3
operator* (float c, const mat3& m)
{
	mat3 mult;
	mult[0] = c * m[0];
	mult[1] = c * m[1];
	mult[2] = c * m[2];
	return mult;
}

// scalar division (m / c)
mat3
operator/ (const mat3& m, float c)
{
	assert(c != 0);
	mat3 div;
	div[0] = m[0] / c;
	div[1] = m[1] / c;
	div[2] = m[2] / c;
	return div;
}

// matrix multiplication (m1 * m2)
mat3
operator* (const mat3& m1, const mat3& m2)
{
	mat3 mult;
	mult[0][0] = m1[0] * m2.getColumn(0);
	mult[0][1] = m1[0] * m2.getColumn(1);
	mult[0][2] = m1[0] * m2.getColumn(2);

	mult[1][0] = m1[1] * m2.getColumn(0);
	mult[1][1] = m1[1] * m2.getColumn(1);
	mult[1][2] = m1[1] * m2.getColumn(2);

	mult[2][0] = m1[2] * m2.getColumn(0);
	mult[2][1] = m1[2] * m2.getColumn(1);
	mult[2][2] = m1[2] * m2.getColumn(2);

	return mult;
}

// matrix*vector multiplication (m * v)
vec3
operator* (const mat3& m, const vec3& v)
{
	vec3 mult;
	mult[0] = (m[0][0] * v[0]) + (m[0][1] * v[1]) + (m[0][2] * v[2]);
	mult[1] = (m[1][0] * v[0]) + (m[1][1] * v[1]) + (m[1][2] * v[2]);
	mult[2] = (m[2][0] * v[0]) + (m[2][1] * v[1]) + (m[2][2] * v[2]);
	return mult;
}

// vector*matrix multiplication (v * m)
vec3
operator* (const vec3& v, const mat3& m)
{
	vec3 mult;
	mult[0] = (v[0] * m[0][0]) + (v[1] * m[1][0]) + (v[2] * m[2][0]);
	mult[1] = (v[0] * m[0][1]) + (v[1] * m[1][1]) + (v[2] * m[2][1]);
	mult[2] = (v[0] * m[0][2]) + (v[1] * m[1][2]) + (v[2] * m[2][2]);
	return mult;
}

// 2D rotation - takes an angle in degrees, returns a 3x3 rotation matrix
mat3
mat3::rotation2D(float angle)
{
	mat3 rot;
	if ((cos(angle * PI / 180.0) < POSZERO) && (cos(angle * PI / 180.0) > NEGZERO))
		rot[0][0] = 0.0;
	else
		rot[0][0] = cos(angle * PI / 180.0);
	if ((-1 * sin(angle * PI / 180.0) < POSZERO) && (-1 * sin(angle * PI / 180.0) > NEGZERO))
		rot[0][1] = 0.0;
	else
		rot[0][1] = -1 * sin(angle * PI / 180.0);
	rot[0][2] = 0;

	if ((sin(angle * PI / 180.0) < POSZERO) && (sin(angle * PI / 180.0) > NEGZERO))
		rot[1][0] = 0.0;
	else
		rot[1][0] = sin(angle * PI / 180.0);
	if ((cos(angle * PI / 180.0) < POSZERO) && (cos(angle * PI / 180.0) > NEGZERO))
		rot[1][1] = 0.0;
	else
		rot[1][1] = cos(angle * PI / 180.0);
	rot[1][2] = 0;

	rot[2][0] = 0;
	rot[2][1] = 0;
	rot[2][2] = 1;

	return rot;
}

// takes an x and y displacement and outputs a 3x3 translation matrix
mat3 
mat3::translation2D(float x, float y)
{
	mat3 tr;
	tr[0][0] = 1;
	tr[0][1] = 0;
	tr[0][2] = x;

	tr[1][0] = 0;
	tr[1][1] = 1;
	tr[1][2] = y;

	tr[2][0] = 0;
	tr[2][1] = 0;
	tr[2][2] = 1;

	return tr;
}

// takes an x and y scale and outputs a 3x3 scale matrix
mat3 
mat3::scale2D(float x, float y)
{
	mat3 sc;
	sc[0][0] = x;
	sc[0][1] = 0;
	sc[0][2] = 0;

	sc[1][0] = 0;
	sc[1][1] = y;
	sc[1][2] = 0;

	sc[2][0] = 0;
	sc[2][1] = 0;
	sc[2][2] = 1;

	return sc;
}

// generates a 3x3 identity matrix
mat3
mat3::identity()
{
	mat3 ident;
	ident[0][0] = 1;
	ident[0][1] = 0;
	ident[0][2] = 0;

	ident[1][0] = 0;
	ident[1][1] = 1;
	ident[1][2] = 0;

	ident[2][0] = 0;
	ident[2][1] = 0;
	ident[2][2] = 1;

	return ident;
}
