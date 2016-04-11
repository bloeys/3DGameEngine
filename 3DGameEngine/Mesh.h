#pragma once

#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Vertex.h"
#include "Component.h"

class Mesh
{
public:

	void AddVertices(const std::vector<Vertex> &vertices, const std::vector<int> &indices);
	void Draw();

	Mesh();
	~Mesh();

private:
	GLuint vboID;	//Vertex buffer object ID
	GLuint iboID;	//Index buffer object ID
	int singleVertexByteSize;
	int indexCount;
};

#endif // !MESH_H