#pragma once
#include <string>
#include "Vertex.h"
#include "Vector4.h"
#include "Edge.h"
#include "Triangle.h"

//create a model mesh out of all of the triangle meshes created.
class Mesh
{
	public:
		Mesh(void);
		Mesh(const Mesh& m);
		~Mesh(void);

		Vertex GetV0(int) const;
		Vertex GetV1(int) const;
		Vertex GetV2(int) const;

		Vector4 GetV0P(int) const;
		Vector4 GetV1P(int) const;
		Vector4 GetV2P(int) const;

		Edge GetE0(int) const;
		Edge GetE1(int) const;
		Edge GetE2(int) const;

		Triangle GetT(int) const;
		int GetTCount() const;
		COLORREF GetTColour(int) const;


		void SetV0(int, Vertex v);
		void SetV1(int, Vertex v);
		void SetV2(int, Vertex v);

		void SetV0P(int, Vector4 v);
		void SetV1P(int, Vector4 v);
		void SetV2P(int, Vector4 v);

		void SetE0(int, Edge e);
		void SetE1(int, Edge e);
		void SetE2(int, Edge e);

		void SetT(int, Triangle t);
		void SetTCount(int);
		void SetTColour(int, COLORREF);


		Mesh& operator= (const Mesh &rhs);

	private:
		int _tCount;

		#define _MAX_T 300

		typedef struct { Triangle mTriangles; } _Triangles;		
		_Triangles _list_Triangles[_MAX_T];						//list of triangles we can access.

		void Init();
		void Copy(const Mesh& m);
		
};