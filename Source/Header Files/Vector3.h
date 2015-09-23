#pragma once
#include <string>

//create a vector3 class
class Vector3
{
	public:
		Vector3(void);
		Vector3(const float x, const float y, const float z);
		Vector3(const Vector3& v);
		~Vector3(void);

		float GetX(void) const;
		float GetY(void) const;
		float GetZ(void) const;

		void SetX(float x);
		void SetY(float y);
		void SetZ(float z);

		float dotProduct(const Vector3& v) const;		//vector3 dotproduct
		Vector3 crossProduct(const Vector3& v) const;	//vector3 crossproduct

		Vector3 Normalise(Vector3 v) const;				//normalise vector

		Vector3& operator= (const Vector3 &rhs);

		const Vector3 operator+(const Vector3 &v) const;
	    const Vector3 operator-(const Vector3 &v) const;
		const Vector3 operator/(const float &mag) const;

	private:
		float _x, _y, _z;

		void Init(float x, float y, float z);
		void Copy(const Vector3& v);
		
};
