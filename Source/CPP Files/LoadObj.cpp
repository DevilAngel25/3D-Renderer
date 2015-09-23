#include "stdAfx.h"
#include "LoadObj.h"


// Constructors

LoadObj::LoadObj(void)
{
	Init(_fn);
}

//load .obj file
LoadObj::LoadObj(LPSTR fn, Mesh& m)
{
	Init(fn);

	char op; 
	float fx = 0.0f, fy = 0.0f, fz = 0.0f;
	int ix = 0, iy = 0, iz = 0;

	char buffer[100];
	int sizeBuffer = 100;

	//if loading a Cube use this path
	if(fn == "Cube")
	{
		fn = "Objects\\Cube.obj";
	}

	if(fn == "Diamond")
	{
		fn = "Objects\\Diamond.obj";
	}

	if(fn == "Dodeca")
	{
		fn = "Objects\\Dodeca.obj";
	}

	if(fn == "Icosa")
	{
		fn = "Objects\\Icosa.obj";
	}

	if(fn == "Octa")
	{
		fn = "Objects\\Octa.obj";
	}

	if(fn == "Humanoid")
	{
		fn = "Objects\\Humanoid.obj";
	}

	Vector4 vec;
	Vertex ver0, ver1;
	Edge edg0, edg1, edg2;

	std::ifstream infile(fn, std::ifstream::in);	//if file exists open it.

	while(infile.getline(buffer, sizeBuffer))		//get each line
	{
			std::istringstream iss(buffer, std::istringstream::in);

			iss>>op; //find op

			if(op == '#')
			{
				//comment, ignore
				//reset values (just in case)
				fx = 0.0f; 
				fy = 0.0f; 
				fz = 0.0f;

				ix = 0; 
				iy = 0; 
				iz = 0;
			}
			else if(op == 'v')
			{
				//vertices x,y,z
				iss>>fx>>fy>>fz; //find remaining values if v (floats)

				vec.SetX(fx);
				vec.SetY(fy);
				vec.SetZ(fz);
				vec.SetW(1);

				_list_Vertices[_vCount].mVertices.SetP(vec);	//set vertex into the buffer
				_vCount++;										//increse the vertex counter
			}
			else if(op == 'f')
			{
				//faces x,y,z

				//create face (ploygon) from values
				iss>>ix>>iy>>iz;	//find remainging values if f (ints)

				_list_Faces[_fCount].x = ix-1;		//x is face first value (x-1 so arrays/lists match up)
				_list_Faces[_fCount].y = iy-1;		//y is second ect.
				_list_Faces[_fCount].z = iz-1;

				_fCount++;		//increase face count.
			}
			else
			{
				//invalide data, ignore
				//reset values (just in case)
				fx = 0.0f; 
				fy = 0.0f; 
				fz = 0.0f;

				ix = 0; 
				iy = 0; 
				iz = 0;
			}
	}

	infile.close(); //close file (if needed)

	for(int i = 0; i < _fCount; i++)
	{
		m.SetV0(i, _list_Vertices[_list_Faces[i].x].mVertices);		//set the vertices of the mesh from the loadobject vertices buffer
		m.SetV1(i, _list_Vertices[_list_Faces[i].y].mVertices);		//sorting them by the face integer
		m.SetV2(i, _list_Vertices[_list_Faces[i].z].mVertices);

		for(int j = 0; j < _fCount; j++)
		{
			edg0.SetV0(_list_Vertices[_list_Faces[j].x].mVertices);		//set the edges of the mesh
			edg0.SetV1(_list_Vertices[_list_Faces[j].y].mVertices);

			edg1.SetV0(_list_Vertices[_list_Faces[j].y].mVertices);
			edg1.SetV1(_list_Vertices[_list_Faces[j].z].mVertices);

			edg2.SetV0(_list_Vertices[_list_Faces[j].z].mVertices);
			edg2.SetV1(_list_Vertices[_list_Faces[j].x].mVertices);

			m.SetE0(j, edg0);
			m.SetE1(j, edg1);
			m.SetE2(j, edg2);

			m.SetTCount(i+1);
		}
	}	
}

LoadObj::LoadObj(const LoadObj& l)
{
	Copy(l);
}

LoadObj::~LoadObj()
{
}

// Accessors and mutators

LPSTR LoadObj::GetFN() const	//get the file name
{
	return _fn;
}

int LoadObj::GetFC() const		//get the face count
{
	return _fCount;
}

int LoadObj::GetVC() const		//get the vertex count
{
	return _vCount;
}

//set the values
void LoadObj::SetFN(LPSTR fn)
{
	_fn = fn;
}

void LoadObj::SetFC(int fc)
{
	_fCount = fc;
}

void LoadObj::SetVC(int vc)
{
	_vCount = vc;
}
// Operator overloads

LoadObj& LoadObj::operator=(const LoadObj &rhs)
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

void LoadObj::Init(LPSTR fileName)
{
	_fn = fileName;
	_fCount = 0;
	_vCount = 0;
}

void LoadObj::Copy(const LoadObj& l)
{
	_fn = l.GetFN();
	_fCount = l.GetFC();
	_vCount = l.GetVC();
}