#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Vertex.h"
#include "Vector4.h"
#include "Triangle.h"
#include "Mesh.h"

//create a class to Load an Object file
class LoadObj
{
	public:
		LoadObj(void);
		LoadObj(LPSTR fileName, Mesh& m);
		LoadObj(const LoadObj& e);
		~LoadObj(void);

		LPSTR GetFN(void) const;

		int GetFC(void) const;
		int GetVC(void) const;

		void SetFN(LPSTR fn);

		void SetFC(int fc);
		void SetVC(int vc);

		LoadObj& operator= (const LoadObj &rhs);

	private:
		LPSTR _fn;

		int _fCount;
		int _vCount;

		#define _MAX_V 300

		typedef struct { Vertex mVertices; } _Vertices;		
		_Vertices _list_Vertices[_MAX_V];					//store a list of vertices to use later

		#define _MAX_F 300

		typedef struct { int x; int y; int z; } _Faces;		
		_Faces _list_Faces[_MAX_F];							//store a list of faces to use later

		void Init(LPSTR fn);
		void Copy(const LoadObj& l);
		
};
