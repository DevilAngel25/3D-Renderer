#pragma once
#include <string>
#include "Vertex.h"
#include "Edge.h"
#include "Vector3.h"

//create a class to generate a triangle mesh
class Triangle
{
	public:
		Triangle(void);
		Triangle(Vertex v0, Vertex v1, Vertex v2, Edge e0, Edge e1, Edge e2);
		Triangle(const Triangle& m);
		~Triangle(void);

		Vertex GetV0(void) const;
		Vertex GetV1(void) const;
		Vertex GetV2(void) const;

		Edge GetE0(void) const;
		Edge GetE1(void) const;
		Edge GetE2(void) const;

		Vector3 GetN(void) const;
		COLORREF GetC(void) const;

		void SetV0(Vertex v0);
		void SetV1(Vertex v1);
		void SetV2(Vertex v2);

		void SetE0(Edge e0);
		void SetE1(Edge e1);
		void SetE2(Edge e2);

		void SetN(Vector3 n);
		void SetC(COLORREF c);

		Triangle& operator= (const Triangle &rhs);

	private:
		Vertex _mVertices[3];
		Edge _mEdges[3];
		Vector3 _Normal;
		COLORREF _Colour;

		void Init(Vertex v0, Vertex v1, Vertex v2, Edge e0, Edge e1, Edge e2);
		void Copy(const Triangle& m);
		
};
