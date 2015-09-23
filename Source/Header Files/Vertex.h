#pragma once
#include <string>
#include "Vector4.h"

//create a vertex class to store xyzw values
class Vertex
{
	public:
		Vertex(void);
		Vertex(const float x, const float y, const float z);
		Vertex(const Vertex& v);
		~Vertex(void);

		Vector4 GetP(void) const;

		float GetPX(void) const;
		float GetPY(void) const;
		float GetPZ(void) const;
		float GetPW(void) const;

		void SetP(Vector4 p);

		void SetPX(float px);
		void SetPY(float py);
		void SetPZ(float pz);
		void SetPW(float pw);

		Vertex& operator= (const Vertex &rhs);

	private:
		Vector4 _point;

		float _px, _py, _pz, _pw;

		//unsigned int colour;

		void Init(const float x, const float y, const float z);
		void Copy(const Vertex& v);
		
};
