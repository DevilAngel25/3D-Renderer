#include "StdAfx.h"
#include "Mesh.h"

// Constructors

Mesh::Mesh(void)
{
	Init();
}

Mesh::Mesh(const Mesh& m)
{
	Copy(m);
}

Mesh::~Mesh(void)
{
}

// Accessors and mutators

Vertex Mesh::GetV0(int i) const							//get vertex from triangle
{
	return _list_Triangles[i].mTriangles.GetV0();
}

Vertex Mesh::GetV1(int i) const							//get vertex from triangle
{
	return _list_Triangles[i].mTriangles.GetV1();
}

Vertex Mesh::GetV2(int i) const
{
	return _list_Triangles[i].mTriangles.GetV2();
}

Vector4 Mesh::GetV0P(int i) const						//get vector from vertex, from triangle
{
	return _list_Triangles[i].mTriangles.GetV0().GetP();
}

Vector4 Mesh::GetV1P(int i) const
{
	return _list_Triangles[i].mTriangles.GetV1().GetP();
}

Vector4 Mesh::GetV2P(int i) const
{
	return _list_Triangles[i].mTriangles.GetV2().GetP();
}


Edge Mesh::GetE0(int i) const								//get edge from triangle
{
	return _list_Triangles[i].mTriangles.GetE0();
}

Edge Mesh::GetE1(int i) const
{
	return _list_Triangles[i].mTriangles.GetE1();
}

Edge Mesh::GetE2(int i) const
{
	return _list_Triangles[i].mTriangles.GetE2();
}

Triangle Mesh::GetT(int i) const						//get triangle
{
	return _list_Triangles[i].mTriangles;
}

int Mesh::GetTCount() const								//get the triangle count
{
	return _tCount;
}

COLORREF Mesh::GetTColour(int i) const					//ge the triangle color
{
	return _list_Triangles[i].mTriangles.GetC();
}

//set the values
void Mesh::SetV0(int i, Vertex v)
{
	_list_Triangles[i].mTriangles.SetV0(v);
}

void Mesh::SetV1(int i, Vertex v)
{
	_list_Triangles[i].mTriangles.SetV1(v);
}

void Mesh::SetV2(int i, Vertex v)
{
	_list_Triangles[i].mTriangles.SetV2(v);
}

void Mesh::SetV0P(int i, Vector4 v)
{
	Vertex ver;

	ver.SetP(v);
	_list_Triangles[i].mTriangles.SetV0(ver);
}

void Mesh::SetV1P(int i, Vector4 v)
{
	Vertex ver;

	ver.SetP(v);
	_list_Triangles[i].mTriangles.SetV1(ver);
}

void Mesh::SetV2P(int i, Vector4 v)
{
	Vertex ver;

	ver.SetP(v);
	_list_Triangles[i].mTriangles.SetV2(ver);
}


void Mesh::SetE0(int i, Edge e)
{
	_list_Triangles[i].mTriangles.SetE0(e);
}

void Mesh::SetE1(int i, Edge e)
{
	_list_Triangles[i].mTriangles.SetE1(e);
}

void Mesh::SetE2(int i, Edge e)
{
	_list_Triangles[i].mTriangles.SetE2(e);
}

void Mesh::SetT(int i, Triangle t)
{
	_list_Triangles[i].mTriangles = t;
	_tCount += 1;
}

void Mesh::SetTCount(int i)
{
	_tCount = i;
}

void Mesh::SetTColour(int i, COLORREF c)
{
	_list_Triangles[i].mTriangles.SetC(c);
}

// Operator overloads

Mesh& Mesh::operator=(const Mesh &rhs)
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

void Mesh::Init()
{
	_tCount = 0;
}

void Mesh::Copy(const Mesh& v)
{
	_tCount = v.GetTCount();

	for(int i = 0; i < v.GetTCount(); i++)
	{
		_list_Triangles[i].mTriangles = v.GetT(i);
	}
}