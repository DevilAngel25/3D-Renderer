#pragma once
#include <string>
#include "Vertex.h"

//create an edge class to set edges
class Edge
{
	public:
		Edge(void);
		Edge(Vertex v0, Vertex v1);
		Edge(const Edge& e);
		~Edge(void);

		Vertex GetV0(void) const;
		Vertex GetV1(void) const;

		void SetV0(Vertex v0);
		void SetV1(Vertex v1);

		Edge& operator= (const Edge &rhs);

	private:
		Vertex _v0, _v1;

		void Init(Vertex v0, Vertex v1);
		void Copy(const Edge& v);
		
};
