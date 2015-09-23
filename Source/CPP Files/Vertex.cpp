#include "stdAfx.h"
#include "Vertex.h"


// Constructors

Vertex::Vertex(void)
{
	Init(0.0f,0.0f,0.0f);
}

Vertex::Vertex(const float x, const float y, const float z)
{
	Init(x,y,z);
}

Vertex::Vertex(const Vertex& v)
{
	Copy(v);
}

Vertex::~Vertex()
{
}

// Accessors and mutators

Vector4 Vertex::GetP(void) const	//get the point xyzw
{
	return _point;
}

float Vertex::GetPX(void) const		//get the x from point
{
	return _point.GetX();
}

float Vertex::GetPY(void) const		//get the y from point
{
	return _point.GetY();
}

float Vertex::GetPZ(void) const		//get the z from point
{
	return _point.GetZ();
}

float Vertex::GetPW(void) const		//get the w from point
{
	return _point.GetW();
}

void Vertex::SetP(Vector4 p)		//set the point of xyzw
{
	_point = p;
}

void Vertex::SetPX(float px)		//set the x of point
{
	_point.SetX(px);
}

void Vertex::SetPY(float py)		//ect
{
	_point.SetY(py);
}

void Vertex::SetPZ(float pz)
{
	_point.SetZ(pz);
}

void Vertex::SetPW(float pw)
{
	_point.SetW(pw);
}

// Operator overloads

Vertex& Vertex::operator= (const Vertex &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

// Private methods

void Vertex::Init(const float x, const float y, const float z)
{
	_point.SetX(x);
	_point.SetY(y);
	_point.SetZ(z);
	_point.SetW(1.0f);

	_px = _point.GetX();
	_py = _point.GetY();
	_pz = _point.GetZ();
	_pw = 1;
}

void Vertex::Copy(const Vertex& v)
{
	_point = v.GetP();
	_px = v.GetPX();
	_py = v.GetPY();
	_pz = v.GetPZ();
	_pw = v.GetPW();
}