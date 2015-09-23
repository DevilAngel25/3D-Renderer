#include "stdAfx.h"
#include "PolygonV.h"


// Constructors

PolygonV::PolygonV(void)
{
	Init(_e0, _e1, _e2, _e3);
}

PolygonV::PolygonV(Edge e0, Edge e1, Edge e2, Edge e3)
{
	Init(e0, e1, e2, e3);
}

PolygonV::PolygonV(const PolygonV& v)
{
	Copy(v);
}

PolygonV::~PolygonV(void)
{
}

// Accessors and mutators

Edge PolygonV::GetE0(void) const
{
	return _e0;
}

Edge PolygonV::GetE1(void) const
{
	return _e1;
}

Edge PolygonV::GetE2(void) const
{
	return _e2;
}

Edge PolygonV::GetE3(void) const
{
	return _e3;
}


void PolygonV::SetE0(Edge e0)
{
	_e0 = e0;
}

void PolygonV::SetE1(Edge e1)
{
	_e1 = e1;
}

void PolygonV::SetE2(Edge e2)
{
	_e2 = e2;
}

void PolygonV::SetE3(Edge e3)
{
	_e3 = e3;
}

// Private methods

void PolygonV::Init(Edge e0, Edge e1, Edge e2, Edge e3)
{
	_e0 = e0;
	_e1 = e1;
	_e2 = e2;
	_e3 = e3;
}

void PolygonV::Copy(const PolygonV& p)
{
	_e0 = p.GetE0();
	_e1 = p.GetE1();
	_e2 = p.GetE2();
	_e3 = p.GetE3();
}