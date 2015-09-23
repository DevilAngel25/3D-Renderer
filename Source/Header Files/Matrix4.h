#pragma once
#include <string>
#include "Vector3.h"
#include "Vector4.h"

//create a class to handle matrices
class Matrix4
{
	public:
		Matrix4(void);
		Matrix4(float r1c1, float r1c2, float r1c3, float r1c4, 
				float r2c1, float r2c2, float r2c3, float r2c4,
				float r3c1, float r3c2, float r3c3, float r3c4, 
				float r4c1, float r4c2, float r4c3, float r4c4);
		Matrix4(const Matrix4& m);
		~Matrix4(void);

		float GetM(int, int) const;
		void SetM(int, int, float);

		void Translation(float x, float y, float z);		//set translation matrix

		void RotationX(float);								//set a rotation in X
		void RotationY(float);								//set a rotation in Y
		void RotationZ(float);								//set a rotation in Z

		void Scale(float s);								//set the scale
		void ScaleX(float s);								//set the scale in X
		void ScaleY(float s);								//set the scale in Y
		void ScaleZ(float s);								//set the scale in Z

		void ResetMatrix();											//reset matrix values to default
		void View(Vector3 v, Vector3 u, Vector3 r, Vector3 eye);	//create the view matrix

		float DetA();						//Detrement for inversion
		Matrix4 Cofactor();					//cofactor for inversion
		Matrix4 Transpose();				//transpose of adjoint
		Matrix4 Invert(Matrix4 m);			//inversion of the matrix via the detrement, cofactor and adjoint

		Matrix4& operator= (const Matrix4 &rhs);

		const Matrix4 operator*(const Matrix4 &other) const;		//matrix multiplied by a matrix
		const Vector4 operator*(const Vector4 &other) const;		//matrix multiplied by a vector

		const Matrix4 operator/(const float &detA) const;			//divide matrix by the detrement

	private:
		float _mat4Val[4][4];


		void Init(float r1c1, float r1c2, float r1c3, float r1c4, 
				  float r2c1, float r2c2, float r2c3, float r2c4,
				  float r3c1, float r3c2, float r3c3, float r3c4, 
				  float r4c1, float r4c2, float r4c3, float r4c4);
		void Copy(const Matrix4& m);
		
};