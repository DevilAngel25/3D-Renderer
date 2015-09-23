#pragma once
#include <string>

#include "PolygonV.h"
#include "Vector4.h"
#include "Edge.h"


//draw the mesh using bresenham line algorithm.
class Draw_Line
{
	public:
		Draw_Line(void);
		Draw_Line(HDC& bdc, Edge e0, bool fill, COLORREF Colour);
		Draw_Line(const Draw_Line& m);
		~Draw_Line(void);

		Draw_Line& operator=(const Draw_Line &rhs);

	private:
		Edge _e0;
		Vector4 _v0, _v1;

		bool _fill;
		COLORREF _Colour;

		int _x0, _y0, _z0;
		int _x1, _y1, _z1;

		int _x, _y, _z;
		int _d, _dx, _dy, _dz;
		int _twoDx, _twoDy, _twoDz;

		int _R, _G, _B;

		void Init(Edge e0, bool fill, COLORREF Colour);
		//void Copy(const Draw_Line& m);
		
};