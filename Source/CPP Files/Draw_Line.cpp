#include "StdAfx.h"
#include "Draw_Line.h"

// Constructors

Draw_Line::Draw_Line(void)
{
	Init(_e0, _fill, _Colour);
}

// draw a line from point A too point B using the algorithm
Draw_Line::Draw_Line(HDC& bdc, Edge e0, bool fill, COLORREF Colour) 
{
	Init(e0, fill, Colour);

	_dx = abs(_x1 - _x0);
	_dy = abs(_y1 - _y0);

	_twoDy = _dy << 1;
	_twoDx = _dx << 1;

	_x = _x0;
	_y = _y0;

	if (_dy <= _dx)
	{
		_d = _dx - _twoDy;

		for(_x = _x0; _x <= _x1; _x++)
		{
			SetPixel(bdc, _x, _y, RGB(_R, _G, _B));
			if(_d < 0)
			{
				_d += _twoDx;
				if(_y0 <= _y1)
				{
					_y++;
				}
				else
				{
					_y--;
				}
			}
			_d -= _twoDy;
		}

		for(_x = _x0; _x > _x1; _x--)
		{
			SetPixel(bdc, _x, _y, RGB(_R, _G, _B));
			if(_d < 0)
			{
				_d += _twoDx;
				if(_y0 <= _y1)
				{
					_y++;
				}
				else
				{
					_y--;
				}
			}
			_d -= _twoDy;
		}
	}
	else if (_dy > _dx)
	{
		_d = _dy - _twoDx;

		for(_y = _y0; _y <= _y1; _y++)
		{
			SetPixel(bdc, _x, _y, RGB(_R, _G, _B));
			if(_d < 0)
			{
				_d += _twoDy;
				if(_x0 <= _x1)
				{
					_x++;
				}
				else
				{
					_x--;
				}
			}
			_d -= _twoDx;
		}

		for(_y = _y0; _y > _y1; _y--)
		{
			SetPixel(bdc, _x, _y, RGB(_R, _G, _B));
			if(_d < 0)
			{
				_d += _twoDy;
				if(_x0 <= _x1)
				{
					_x++;
				}
				else
				{
					_x--;
				}
			}
			_d -= _twoDx;
		}
	}
}

Draw_Line::~Draw_Line(void)
{
}


// Private methods
void Draw_Line::Init(Edge e0, bool fill, COLORREF Colour)
{
	_fill = fill;
	_Colour = Colour;

	_R = GetRValue(Colour);
	_G = GetGValue(Colour);
	_B = GetBValue(Colour);

	Vertex ver0, ver1;
	Vector3 vec0, vec1;

	ver0 = e0.GetV0();
	ver1 = e0.GetV1();

	_v0 = ver0.GetP();
	_v1 = ver1.GetP();
	
	vec0 = _v0.DeHom(_v0);
	vec1 = _v1.DeHom(_v1);
	
	_x0 = (int)vec0.GetX();
	_y0 = (int)vec0.GetY();
	_z0 = (int)vec0.GetZ();

	_x1 = (int)vec1.GetX();
	_y1 = (int)vec1.GetY();
	_z1 = (int)vec1.GetZ();
}