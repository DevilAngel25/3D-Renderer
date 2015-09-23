#pragma once
#include <string>
#include "Edge.h"
#include "Draw_Line.h"

class PolygonV
{
	public:
		PolygonV(void);
		PolygonV(Edge e0, Edge e1, Edge e2, Edge e3);
		PolygonV(const PolygonV& p);
		~PolygonV(void);

		Edge GetE0(void) const;
		Edge GetE1(void) const;
		Edge GetE2(void) const;
		Edge GetE3(void) const;

		void SetE0(Edge e0);
		void SetE1(Edge e1);
		void SetE2(Edge e2);
		void SetE3(Edge e3);

		PolygonV& operator= (const PolygonV &rhs);


	private:
		Edge _e0, _e1, _e2, _e3;

		void Init(Edge e0, Edge e1, Edge e2, Edge e3);
		void Copy(const PolygonV& v);
		
};
