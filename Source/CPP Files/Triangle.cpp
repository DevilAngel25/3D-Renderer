#include "StdAfx.h"
#include "Triangle.h"

// Constructors

Triangle::Triangle(void)
{
	Init(_mVertices[0], _mVertices[1], _mVertices[2], _mEdges[0], _mEdges[1], _mEdges[2]);
}

//i've never caled the triangle class with these parameters but its there if i ever need it.
Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2, Edge e0, Edge e1, Edge e2)
{
	Init(v0, v1, v2, e0, e1, e2);
}

Triangle::Triangle(const Triangle& t)
{
	Copy(t);
}

Triangle::~Triangle(void)
{
}

// Accessors and mutators

Vertex Triangle::GetV0() const		//get vertecies, vertex 0 (1)
{
	return _mVertices[0];
}

Vertex Triangle::GetV1() const		 //get vertecies, vertex 1 (2)
{
	return _mVertices[1];
}

Vertex Triangle::GetV2() const
{
	return _mVertices[2];
}

Edge Triangle::GetE0() const		//get Edges, edge 0 (1)
{
	return _mEdges[0];
}

Edge Triangle::GetE1() const		//get Edges, edge 1 (2)
{
	return _mEdges[1];
}

Edge Triangle::GetE2() const
{
	return _mEdges[2];
}

Vector3 Triangle::GetN() const		//get normal (if one exists)
{
	return _Normal;
}

COLORREF Triangle::GetC() const		//get the color (if one exists)
{
	return _Colour;
}


//set values
void Triangle::SetV0(Vertex v0)		//set vertecies
{
	_mVertices[0] = v0;
}

void Triangle::SetV1(Vertex v1)
{
	_mVertices[1] = v1;
}

void Triangle::SetV2(Vertex v2)
{
	_mVertices[2] = v2;
}

void Triangle::SetE0(Edge e0)		//set edges
{
	_mEdges[0] = e0;
}

void Triangle::SetE1(Edge e1)
{
	_mEdges[1] = e1;
}

void Triangle::SetE2(Edge e2)
{
	_mEdges[2] = e2;
}

void Triangle::SetN(Vector3 v)
{
	_Normal = v;
}

void Triangle::SetC(COLORREF c)
{
	_Colour = c;
}

// Operator overloads

Triangle& Triangle::operator=(const Triangle &rhs)
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

void Triangle::Init(Vertex v0, Vertex v1, Vertex v2, Edge e0, Edge e1, Edge e2)
{
	_mVertices[0] = v0;
	_mVertices[1] = v1;
	_mVertices[2] = v2;
	_mEdges[0] = e0;
	_mEdges[1] = e0;
	_mEdges[2] = e0;

	_Colour = 0;
}

void Triangle::Copy(const Triangle& t)
{
	_mVertices[0] = t.GetV0();
	_mVertices[1] = t.GetV1();
	_mVertices[2] = t.GetV2();

	_mEdges[0] = t.GetE0();
	_mEdges[1] = t.GetE1();
	_mEdges[2] = t.GetE2();

	_Colour = t.GetC();
}