/*
 *  vec3.cpp
 *  written by Bridget Lane
 *  HW4, CS 351, Professor Allbeck
 *
 *  Implements a 3D vector
 *
 */

#include <iostream>			// input/output
#include <assert.h>			// assert
#include <cmath>			// math
#include "vec3.h"			// declaration of vec3

using namespace std;		// for printing

#define VEC_START	0
#define VEC_END		2
#define	EPSILON		0.00001

// constructors
vec3::vec3()
{
	data[0] = 0.0;
	data[1] = 0.0;
	data[2] = 0.0;
}
vec3::vec3(float x, float y, float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}

// getter
float 
vec3::operator[](unsigned int index) const
{
	assert(index >= VEC_START);
	assert(index <= VEC_END);
	float value = data[index];
	return value;
}

// setter
float& 
vec3::operator[](unsigned int index) 
{
	assert(index >= VEC_START);
	assert(index <= VEC_END);
	return data[index];
}

// prints out the vector nicely
void
vec3::print()
{
	cout.precision(6);		// control decimal precision
	//cout << "x: " << data[0] << " y: " << data[1] << " z: " << data[2] << endl;
	cout << "\t\t" << data[0] << "\t\t" << data[1] << "\t\t" << data[2] << endl;		// works better with mat3
}

// returns geometric length of vector
float 
vec3::length() const
{
	float len = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
	return len;
}

// override == op
bool
operator==(const vec3& v1, const vec3& v2)
{
	if ((abs(v1[0] - v2[0]) < EPSILON) && (abs(v1[1] - v2[1]) < EPSILON) && (abs(v1[2] - v2[2]) < EPSILON))
	{
		return true;
	}
	else
	{
		return false;
	}
}

// override != op
bool 
operator!=(const vec3& v1, const vec3& v2)
{
	if ((abs(v1[0] - v2[0]) < EPSILON) && (abs(v1[1] - v2[1]) < EPSILON) && (abs(v1[2] - v2[2]) < EPSILON))
	{
		return false;
	}
	else
	{
		return true;
	}
}

// vector addition
vec3
operator+(const vec3& v1, const vec3& v2)
{
	vec3 v3((v1[0] + v2[0]), (v1[1] + v2[1]), (v1[2] + v2[2]));
	return v3;
}

// vector subtraction
vec3
operator-(const vec3& v1, const vec3& v2)
{
	vec3 v3((v1[0] - v2[0]), (v1[1] - v2[1]), (v1[2] - v2[2]));
	return v3;
}

// scalar multiplication (v * c)
vec3 
operator* (const vec3& v, float c)
{
	vec3 v3((v[0] * c), (v[1] * c), (v[2] * c));
	return v3;
}

// scalar multiplication (c * v)
vec3 
operator* (float c, const vec3& v)
{
	vec3 v3((c * v[0]), (c * v[1]), (c * v[2]));
	return v3;
}

// scalar division (v / c)
vec3 
operator/ (const vec3& v, float c)
{
	assert(c != 0);
	vec3 v3((v[0] / c), (v[1] / c), (v[2] / c));
	return v3;
}

// dot product (v1 * v2)
float 
operator* (const vec3& v1, const vec3& v2)
{
	float dot = (v1[0] * v2[0]) + (v1[1] * v2[1]) + (v1[2] * v2[2]);
	return dot;
}

// cross product (v1 % v2)
vec3 
operator% (const vec3& v1, const vec3& v2)
{
	vec3 v3(((v1[1] * v2[2]) - (v1[2] * v2[1])), ((v1[2] * v2[0]) - (v1[0] * v2[2])), ((v1[0] * v2[1]) - (v1[1] * v2[0])));
	return v3;
}
