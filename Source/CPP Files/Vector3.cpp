#include "stdAfx.h"
#include "Vector3.h"


// Constructors

Vector3::Vector3(void)
{
	Init(0.0f, 0.0f, 0.0f);
}

Vector3::Vector3(float x, float y, float z)
{
	Init(x, y, z);
}

Vector3::Vector3(const Vector3& v)
{
	Copy(v);
}

Vector3::~Vector3(void)
{
}

// Accessors and mutators

//get xyz

float Vector3::GetX(void) const
{
	return _x;
}

float Vector3::GetY(void) const
{
	return _y;
}

float Vector3::GetZ(void) const
{
	return _z;
}

//set xyz

void Vector3::SetX(float x)
{
	_x = x;
}

void Vector3::SetY(float y)
{
	_y = y;
}

void Vector3::SetZ(float z)
{
	_z = z;
}

//Methods

//dot product
float Vector3::dotProduct(const Vector3& v) const
{
	return _x * v.GetX() + _y * v.GetY() + _z * v.GetZ();
}

//cross product
Vector3 Vector3::crossProduct(const Vector3& v) const
{
	Vector3 result;

	result.SetX(_y * v.GetZ() - v.GetY() * _z);
	result.SetY(_x * v.GetZ() - v.GetX() * _z);
	result.SetZ(_x * v.GetY() - v.GetX() * _y);

	return result;
}

//normalise the vectors
Vector3 Vector3::Normalise(Vector3 v) const
{
	Vector3 result;
	float mag;

	mag = sqrt(v.GetX() * v.GetX() + v.GetY() * v.GetY() + v.GetZ() * v.GetZ());
	result = v / mag;

	return result;
}

// Operator overloads
Vector3& Vector3::operator=(const Vector3 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

const Vector3 Vector3::operator+(const Vector3 &other) const
{
	Vector3 result;
	result.SetX(_x + other.GetX());
	result.SetY(_y + other.GetY());
	result.SetZ(_z + other.GetZ());
	return result;
}

const Vector3 Vector3::operator-(const Vector3 &other) const
{
	Vector3 result;
	result.SetX(_x - other.GetX());
	result.SetY(_y - other.GetY());
	result.SetZ(_z - other.GetZ());
	return result;
}

//calculate the magnitude for normilisasion
const Vector3 Vector3::operator/(const float &mag) const
{
	Vector3 result;

	if(mag == 0)
	{
		result.SetX(0);
		result.SetY(0);
		result.SetZ(0);
	}
	else
	{
		result.SetX(_x / mag);
		result.SetY(_y / mag);
		result.SetZ(_z / mag);
	}

	return result;
}
// Private methods

void Vector3::Init(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Vector3::Copy(const Vector3& v)
{
	_x = v.GetX();
	_y = v.GetY();
	_z = v.GetZ();
}