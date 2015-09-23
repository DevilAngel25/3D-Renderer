#include "StdAfx.h"
#include "Matrix4.h"

// Constructors

Matrix4::Matrix4(void)
{
	Init(1.0f, 0.0f, 0.0f, 0.0f, 
		 0.0f, 1.0f, 0.0f, 0.0f, 
		 0.0f, 0.0f, 1.0f, 0.0f, 
		 0.0f, 0.0f, 0.0f, 1.0f);		//default matrix.
}

Matrix4::Matrix4(float r1c1, float r1c2, float r1c3, float r1c4, 
				 float r2c1, float r2c2, float r2c3, float r2c4,
				 float r3c1, float r3c2, float r3c3, float r3c4, 
				 float r4c1, float r4c2, float r4c3, float r4c4)
{
	Init(r1c1, r1c2, r1c3, r1c4, 
		 r2c1, r2c2, r2c3, r2c4, 
		 r3c1, r3c2, r3c3, r3c4,
		 r4c1, r4c2, r4c3, r4c4);
}

Matrix4::Matrix4(const Matrix4& m)
{
	Copy(m);
}

Matrix4::~Matrix4(void)
{
}

// Accessors and mutators

float Matrix4::GetM(int i, int j) const			//get the value at matrix position
{
	return _mat4Val[i][j];
}

void Matrix4::SetM(int i, int j, float k)		//set the matrix value at position
{
	_mat4Val[i][j] = k;
}


// Methods

void Matrix4::ResetMatrix()					//reset the matrix if needed (to default)
{
	Init(1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix4::Translation(float x, float y, float z)	//set translation matrix.
{
	_mat4Val[0][3] = x;
	_mat4Val[1][3] = y;
	_mat4Val[2][3] = z;
}

void Matrix4::RotationX(float a)							//set rotation X matrix
{
	a = a * (3.14159265/180);
	_mat4Val[1][1] = cos(a), _mat4Val[1][2] = -sin(a);
	_mat4Val[2][1] = sin(a), _mat4Val[2][2] = cos(a);
}

void Matrix4::RotationY(float a)							//set rotation Y matrix
{
	a = a * (3.14159265/180);
	_mat4Val[0][0] = cos(a), _mat4Val[0][2] = sin(a);
	_mat4Val[2][0] = -sin(a), _mat4Val[2][2] = cos(a);
}

void Matrix4::RotationZ(float a)							//set rotation Z matrix
{
	a = a * (3.14159265/180);
	_mat4Val[0][0] = cos(a), _mat4Val[0][1] = -sin(a);
	_mat4Val[1][0] = sin(a), _mat4Val[1][1] = cos(a);
}

void Matrix4::Scale(float s)							//set Scale matrix
{
	_mat4Val[0][0] = _mat4Val[0][0] * s;
	_mat4Val[1][1] = _mat4Val[1][1] * s;
	_mat4Val[2][2] = _mat4Val[2][2] * s;
}

void Matrix4::ScaleX(float s)							//set X Scale matrix
{
	_mat4Val[0][0] = _mat4Val[0][0] * s;
	_mat4Val[1][1] = _mat4Val[1][1] * 1;
	_mat4Val[2][2] = _mat4Val[2][2] * 1;
}

void Matrix4::ScaleY(float s)							//set Y Scale matrix
{
	_mat4Val[0][0] = _mat4Val[0][0] * 1;
	_mat4Val[1][1] = _mat4Val[1][1] * s;
	_mat4Val[2][2] = _mat4Val[2][2] * 1;
}

void Matrix4::ScaleZ(float s)							//set Z Scale matrix
{
	_mat4Val[0][0] = _mat4Val[0][0] * 1;
	_mat4Val[1][1] = _mat4Val[1][1] * 1;
	_mat4Val[2][2] = _mat4Val[2][2] * s;
}

//set the view matrix
void Matrix4::View(Vector3 v, Vector3 u, Vector3 r, Vector3 e)
{
	_mat4Val[0][0] = r.GetX(), _mat4Val[0][1] = r.GetY(), _mat4Val[0][2] = r.GetZ(), _mat4Val[0][3] = e.GetX();
	_mat4Val[1][0] = u.GetX(), _mat4Val[1][1] = u.GetY(), _mat4Val[1][2] = u.GetZ(), _mat4Val[1][3] = e.GetY();
	_mat4Val[2][0] = v.GetX(), _mat4Val[2][1] = v.GetY(), _mat4Val[2][2] = v.GetZ(), _mat4Val[2][3] = e.GetZ();
	_mat4Val[3][0] = 0,	_mat4Val[3][1] = 0, _mat4Val[3][2] = 0, _mat4Val[3][3] = 1;
}

//find the determenant for inversion matrix
float Matrix4::DetA()
{
	float a, b, c, d, detA;

	a = _mat4Val[0][0] * (_mat4Val[1][1] * ((_mat4Val[2][2] * _mat4Val[3][3]) - (_mat4Val[3][2] * _mat4Val[2][3])) - _mat4Val[1][2] * ((_mat4Val[2][1] * _mat4Val[3][3]) - (_mat4Val[3][1] * _mat4Val[2][3])) + _mat4Val[1][3] * ((_mat4Val[2][1] * _mat4Val[3][2]) - (_mat4Val[3][1] * _mat4Val[2][2])));
	b = -_mat4Val[0][1] * (_mat4Val[1][0] * ((_mat4Val[2][2] * _mat4Val[3][3]) - (_mat4Val[3][2] * _mat4Val[2][3])) - _mat4Val[1][2] * ((_mat4Val[2][0] * _mat4Val[3][3]) - (_mat4Val[3][0] * _mat4Val[2][3])) + _mat4Val[1][3] * ((_mat4Val[2][0] * _mat4Val[3][2]) - (_mat4Val[3][0] * _mat4Val[2][2])));
	c = _mat4Val[0][2] * (_mat4Val[1][0] * ((_mat4Val[2][1] * _mat4Val[3][3]) - (_mat4Val[3][1] * _mat4Val[2][3])) - _mat4Val[1][1] * ((_mat4Val[2][0] * _mat4Val[3][3]) - (_mat4Val[3][0] * _mat4Val[2][3])) + _mat4Val[1][3] * ((_mat4Val[2][0] * _mat4Val[3][1]) - (_mat4Val[3][0] * _mat4Val[2][1])));
	d = -_mat4Val[0][3] * (_mat4Val[1][0] * ((_mat4Val[2][1] * _mat4Val[3][2]) - (_mat4Val[3][1] * _mat4Val[2][2])) - _mat4Val[1][1] * ((_mat4Val[2][0] * _mat4Val[3][2]) - (_mat4Val[3][0] * _mat4Val[2][2])) + _mat4Val[1][2] * ((_mat4Val[2][0] * _mat4Val[3][1]) - (_mat4Val[3][0] * _mat4Val[2][1])));

	detA = a + b + c + d;

	return detA;
}

//find the cofactor for inversion matrix
Matrix4 Matrix4::Cofactor()
{
	Matrix4 result;
	float r1c1, r1c2, r1c3, r1c4, 
		  r2c1, r2c2, r2c3, r2c4,
		  r3c1, r3c2, r3c3, r3c4, 
		  r4c1, r4c2, r4c3, r4c4;

	r1c1 =  (_mat4Val[1][1] * ((_mat4Val[2][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[2][3])) -
			_mat4Val[2][1] * ((_mat4Val[1][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[1][3])) + 
			_mat4Val[3][1] * ((_mat4Val[1][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[1][3])));

	r1c2 = -(_mat4Val[1][0] * ((_mat4Val[2][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[2][3])) -
			_mat4Val[2][0] * ((_mat4Val[1][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[1][3])) +
			_mat4Val[3][0] * ((_mat4Val[1][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[1][3])));

	r1c3 =  (_mat4Val[1][0] * ((_mat4Val[2][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[2][3])) -
			_mat4Val[2][0] * ((_mat4Val[1][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[1][3])) +
			_mat4Val[3][0] * ((_mat4Val[1][1]*_mat4Val[2][3])-(_mat4Val[2][1]*_mat4Val[1][3])));

	r1c4 = -(_mat4Val[1][0] * ((_mat4Val[2][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[2][2])) -
			_mat4Val[2][0] * ((_mat4Val[1][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[1][2])) +
			_mat4Val[3][0] * ((_mat4Val[1][1]*_mat4Val[2][2])-(_mat4Val[2][1]*_mat4Val[1][2])));


	r2c1 = -(_mat4Val[0][1] * ((_mat4Val[2][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[2][3])) -
			_mat4Val[2][1] * ((_mat4Val[0][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[0][3])) +
			_mat4Val[3][1] * ((_mat4Val[0][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[0][3])));

	r2c2 =	(_mat4Val[0][0] * ((_mat4Val[2][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[2][3])) -
			_mat4Val[2][0] * ((_mat4Val[0][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[0][3])) +
			_mat4Val[3][0] * ((_mat4Val[0][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[0][3])));

	r2c3 = -(_mat4Val[0][0] * ((_mat4Val[2][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[2][3])) -
			_mat4Val[2][0] * ((_mat4Val[0][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[0][3])) +
			_mat4Val[3][0] * ((_mat4Val[0][1]*_mat4Val[2][3])-(_mat4Val[2][1]*_mat4Val[0][3])));

	r2c4 =	(_mat4Val[0][0] * ((_mat4Val[2][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[2][2])) -
			_mat4Val[2][0] * ((_mat4Val[0][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[0][2])) +
			_mat4Val[3][0] * ((_mat4Val[0][1]*_mat4Val[2][2])-(_mat4Val[2][1]*_mat4Val[0][2])));


	r3c1 =	(_mat4Val[0][1] * ((_mat4Val[1][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[1][3])) -
			_mat4Val[1][1] * ((_mat4Val[0][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[0][3])) +
			_mat4Val[3][1] * ((_mat4Val[0][2]*_mat4Val[1][3])-(_mat4Val[1][2]*_mat4Val[0][3])));

	r3c2 = -(_mat4Val[0][0] * ((_mat4Val[1][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[1][3])) -
			_mat4Val[1][0] * ((_mat4Val[0][2]*_mat4Val[3][3])-(_mat4Val[3][2]*_mat4Val[0][3])) +
			_mat4Val[3][0] * ((_mat4Val[0][2]*_mat4Val[1][3])-(_mat4Val[1][2]*_mat4Val[0][3])));

	r3c3 =	(_mat4Val[0][0] * ((_mat4Val[1][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[1][3])) -
			_mat4Val[1][0] * ((_mat4Val[0][1]*_mat4Val[3][3])-(_mat4Val[3][1]*_mat4Val[0][3])) +
			_mat4Val[3][0] * ((_mat4Val[0][1]*_mat4Val[1][3])-(_mat4Val[1][1]*_mat4Val[0][3])));

	r3c4 = -(_mat4Val[0][0] * ((_mat4Val[1][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[1][2])) -
			_mat4Val[1][0] * ((_mat4Val[0][1]*_mat4Val[3][2])-(_mat4Val[3][1]*_mat4Val[0][2])) +
			_mat4Val[3][0] * ((_mat4Val[0][1]*_mat4Val[1][2])-(_mat4Val[1][1]*_mat4Val[0][2])));


	r4c1 = -(_mat4Val[0][1] * ((_mat4Val[1][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[1][3])) -
			_mat4Val[1][1] * ((_mat4Val[0][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[0][3])) +
			_mat4Val[2][1] * ((_mat4Val[0][2]*_mat4Val[1][3])-(_mat4Val[1][2]*_mat4Val[0][3])));

	r4c2 =	(_mat4Val[0][0] * ((_mat4Val[1][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[1][3])) -
			_mat4Val[1][0] * ((_mat4Val[0][2]*_mat4Val[2][3])-(_mat4Val[2][2]*_mat4Val[0][3])) +
			_mat4Val[2][0] * ((_mat4Val[0][2]*_mat4Val[1][3])-(_mat4Val[3][2]*_mat4Val[0][3])));

	r4c3 = -(_mat4Val[0][0] * ((_mat4Val[1][1]*_mat4Val[2][3])-(_mat4Val[2][1]*_mat4Val[1][3])) -
			_mat4Val[1][0] * ((_mat4Val[0][1]*_mat4Val[2][3])-(_mat4Val[2][1]*_mat4Val[0][3])) +
			_mat4Val[2][0] * ((_mat4Val[0][1]*_mat4Val[1][3])-(_mat4Val[1][1]*_mat4Val[0][3])));

	r4c4 =	(_mat4Val[0][0] * ((_mat4Val[1][1]*_mat4Val[2][2])-(_mat4Val[2][1]*_mat4Val[1][2])) -
			_mat4Val[1][0] * ((_mat4Val[0][1]*_mat4Val[2][2])-(_mat4Val[2][1]*_mat4Val[0][2])) +
			_mat4Val[2][0] * ((_mat4Val[0][1]*_mat4Val[1][2])-(_mat4Val[1][1]*_mat4Val[0][2])));


	result.SetM(0,0, r1c1), result.SetM(0,1, r1c2), result.SetM(0,2, r1c3), result.SetM(0,3, r1c4);
	result.SetM(1,0, r2c1), result.SetM(1,1, r2c2), result.SetM(1,2, r2c3), result.SetM(1,3, r2c4);
	result.SetM(2,0, r3c1), result.SetM(2,1, r3c2), result.SetM(2,2, r3c3), result.SetM(2,3, r3c4);
	result.SetM(3,0, r4c1), result.SetM(3,1, r4c2), result.SetM(3,2, r4c3), result.SetM(3,3, r4c4);

	return result;
}

//set the transpose for the inversion matrix
Matrix4 Matrix4::Transpose()
{
	Matrix4 result;
	float value;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			value = _mat4Val[i][j];
			result.SetM(j,i, value);
		}
	}

	return result;

}
// invert the matrix (inversion)
Matrix4 Matrix4::Invert(Matrix4 m)
{
	Matrix4 cofactor, result, adjoint;
	float detA;

	detA = m.DetA();
	cofactor = m.Cofactor();
	adjoint = cofactor.Transpose();

	result = adjoint / detA;

	return result;
}

// Operator overloads

Matrix4& Matrix4::operator=(const Matrix4 &rhs)
{
	if (this != &rhs)
	{
		// Only copy if we are not assigning to ourselves. 
		// (remember that a = b is the same as a.operator=(b))
		Copy(rhs);
	}
	return *this;
}

//Matrix-Matrix multiplication
const Matrix4 Matrix4::operator*(const Matrix4 &other) const
{

	Matrix4 result;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			float value = 0;
			for(int k = 0; k < 4; k++)
			{
				value += _mat4Val[i][k] * other.GetM(k, j);
			}
			result.SetM(i, j, value);
		}
	}

	return result;
}

//result of inversion divide by determenant
const Matrix4 Matrix4::operator/(const float &detA) const
{
	Matrix4 result;

	result.SetM(0,0, _mat4Val[0][0] / detA), result.SetM(0,1, _mat4Val[0][1] / detA), result.SetM(0,2, _mat4Val[0][2] / detA), result.SetM(0,3, _mat4Val[0][3] / detA);
	result.SetM(1,0, _mat4Val[1][0] / detA), result.SetM(1,1, _mat4Val[1][1] / detA), result.SetM(1,2, _mat4Val[1][2] / detA), result.SetM(1,3, _mat4Val[1][3] / detA);
	result.SetM(2,0, _mat4Val[2][0] / detA), result.SetM(2,1, _mat4Val[2][1] / detA), result.SetM(2,2, _mat4Val[2][2] / detA), result.SetM(2,3, _mat4Val[2][3] / detA);
	result.SetM(3,0, _mat4Val[3][0] / detA), result.SetM(3,1, _mat4Val[3][1] / detA), result.SetM(3,2, _mat4Val[3][2] / detA), result.SetM(3,3, _mat4Val[3][3] / detA);

	return result;
}

//Matrix-Vector multiplication
const Vector4 Matrix4::operator*(const Vector4 &v) const
{
	Vector4 result;

	result.SetX(_mat4Val[0][0] * v.GetX() + _mat4Val[0][1] * v.GetY() + _mat4Val[0][2] * v.GetZ() + _mat4Val[0][3] * v.GetW());
	result.SetY(_mat4Val[1][0] * v.GetX() + _mat4Val[1][1] * v.GetY() + _mat4Val[1][2] * v.GetZ() + _mat4Val[1][3] * v.GetW());
	result.SetZ(_mat4Val[2][0] * v.GetX() + _mat4Val[2][1] * v.GetY() + _mat4Val[2][2] * v.GetZ() + _mat4Val[2][3] * v.GetW());
	result.SetW(_mat4Val[3][0] * v.GetX() + _mat4Val[3][1] * v.GetY() + _mat4Val[3][2] * v.GetZ() + _mat4Val[3][3] * v.GetW());

	return result;
}
// Private methods

void Matrix4::Init(float r1c1, float r1c2, float r1c3, float r1c4, 
				   float r2c1, float r2c2, float r2c3, float r2c4,
				   float r3c1, float r3c2, float r3c3, float r3c4, 
				   float r4c1, float r4c2, float r4c3, float r4c4)
{
	_mat4Val[0][0] = r1c1, _mat4Val[0][1] = r1c2, _mat4Val[0][2] = r1c3, _mat4Val[0][3] = r1c4;
	_mat4Val[1][0] = r2c1, _mat4Val[1][1] = r2c2, _mat4Val[1][2] = r2c3, _mat4Val[1][3] = r2c4;
	_mat4Val[2][0] = r3c1, _mat4Val[2][1] = r3c2, _mat4Val[2][2] = r3c3, _mat4Val[2][3] = r3c4;
	_mat4Val[3][0] = r4c1, _mat4Val[3][1] = r4c2, _mat4Val[3][2] = r4c3, _mat4Val[3][3] = r4c4;
}

void Matrix4::Copy(const Matrix4& m)
{
	_mat4Val[0][0] = m.GetM(0, 0), _mat4Val[0][1] = m.GetM(0, 1), _mat4Val[0][2] = m.GetM(0, 2), _mat4Val[0][3] = m.GetM(0, 3);
	_mat4Val[1][0] = m.GetM(1, 0), _mat4Val[1][1] = m.GetM(1, 1), _mat4Val[1][2] = m.GetM(1, 2), _mat4Val[1][3] = m.GetM(1, 3);
	_mat4Val[2][0] = m.GetM(2, 0), _mat4Val[2][1] = m.GetM(2, 1), _mat4Val[2][2] = m.GetM(2, 2), _mat4Val[2][3] = m.GetM(2, 3);
	_mat4Val[3][0] = m.GetM(3, 0), _mat4Val[3][1] = m.GetM(3, 1), _mat4Val[3][2] = m.GetM(3, 2), _mat4Val[3][3] = m.GetM(3, 3);
}