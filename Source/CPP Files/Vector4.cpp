#include "stdAfx.h"
#include "Vector4.h"


// Constructors

Vector4::Vector4(void)
{
	Init(0.0f, 0.0f, 0.0f, 1.0f);
}

Vector4::Vector4(float x, float y, float z, float w)
{
	Init(x, y, z, w);
}

Vector4::Vector4(const Vector4& v)
{
	Copy(v);
}

Vector4::~Vector4(void)
{
}

// Accessors and mutators

float Vector4::GetX(void) const		//get x
{
	return _x;
}

float Vector4::GetY(void) const		//get y
{
	return _y;
}

float Vector4::GetZ(void) const		//get z
{
	return _z;
}

float Vector4::GetW(void) const		//ect
{
	return _w;
}

//set the xyz values

void Vector4::SetX(float x)
{
	_x = x;
}

void Vector4::SetY(float y)
{
	_y = y;
}

void Vector4::SetZ(float z)
{
	_z = z;
}

void Vector4::SetW(float w)
{
	_w = w;
}

//Methods

//calculate the dotproduct
float Vector4::dotProduct(const Vector4& v) const
{
	return _x * v.GetX() + _y * v.GetY() + _z * v.GetZ() + _w * v.GetW();
}

//calculate the crossproduct
Vector4 Vector4::crossProduct(const Vector4& v) const
{
	Vector4 result;

	result.SetX(_y * v.GetZ() - v.GetY() * _z);
	result.SetY(_x * v.GetZ() - v.GetX() * _z);
	result.SetZ(_x * v.GetY() - v.GetX() * _y);

	return result;
}

//dehomogise the coords
Vector3 Vector4::DeHom(const Vector4& v) const
{
	Vector3 result;

	result.SetX(v.GetX() / v.GetW());
	result.SetY(v.GetY() / v.GetW());
	result.SetZ(v.GetZ() / v.GetW());

	return result;
}

// Operator overloads
Vector4& Vector4::operator=(const Vector4 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Vector4 Vector4::operator+(const Vector4 &other) const
{
	Vector4 result;
	result.SetX(_x + other.GetX());
	result.SetY(_y + other.GetY());
	result.SetZ(_z + other.GetZ());
	//result.SetZ(_w + other.GetW());
	return result;
}

const Vector4 Vector4::operator-(const Vector4 &other) const
{
	Vector4 result;
	result.SetX(_x - other.GetX());
	result.SetY(_y - other.GetY());
	result.SetZ(_z - other.GetZ());
	//result.SetZ(_w - other.GetW());
	return result;
}

// Private methods

void Vector4::Init(float x, float y, float z, float w)
{
	_x = x;
	_y = y;
	_z = z;
	_w = w;
}

void Vector4::Copy(const Vector4& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
	_w = v.GetW();
}