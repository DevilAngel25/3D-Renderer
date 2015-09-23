#include "stdAfx.h"
#include "Edge.h"


// Constructors

Edge::Edge(void)
{
	Init(_v0, _v1);
}


Edge::Edge(Vertex v0, Vertex v1)
{
	Init(v0, v1);
}


Edge::Edge(const Edge& e)
{
	Copy(e);
}

Edge::~Edge()
{
}

// Accessors and mutators

Vertex Edge::GetV0(void) const		//get vertex from edge
{
	return _v0;
}

Vertex Edge::GetV1(void) const
{
	return _v1;
}

void Edge::SetV0(Vertex v0)		//set vertex from edge
{
	_v0.SetP(v0.GetP());
}

void Edge::SetV1(Vertex v1)
{
	_v1.SetP(v1.GetP());
}

// Operator overloads

Edge& Edge::operator=(const Edge &rhs)
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

void Edge::Init(Vertex v0, Vertex v1)
{
	_v0 = v0;
	_v1 = v1;
}

void Edge::Copy(const Edge& e)
{
	_v0 = e.GetV0();
	_v1 = e.GetV1();
}