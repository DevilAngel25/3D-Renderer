#pragma once
#include <string>
#include "Vector3.h"

//create a vector4 class 
class Vector4
{
	public:
		Vector4(void);
		Vector4(const float x, const float y, const float z, const float w);
		Vector4(const Vector4& v);
		~Vector4(void);

		float GetX(void) const;
		float GetY(void) const;
		float GetZ(void) const;
		float GetW(void) const;

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);
		void SetW(float w);

		float dotProduct(const Vector4& v) const;			//dotproduct
		Vector4 crossProduct(const Vector4& v) const;		//crossproduct

		Vector3 DeHom(const Vector4& v) const;				//dehomogise the xyz values

		Vector4& operator= (const Vector4 &rhs);

		const Vector4 operator+(const Vector4 &v) const;
	    const Vector4 operator-(const Vector4 &v) const;

	private:
		float _x, _y, _z, _w;

		void Init(float x, float y, float z, float w);
		void Copy(const Vector4& v);
		
};
