#pragma once

#include <vector>
#include "Vertex.h"
#include "Component.h"
#include "MeshData.h"

class Mesh : public Component
{
public:

	void AddVertices(const std::vector<Vertex> &vertices, const std::vector<int> &indices);
	void AddVertices(const MeshData& mData);
	void Draw();

	Mesh();
	~Mesh();

private:
	GLuint vboID;	//Vertex buffer object ID
	GLuint iboID;	//Index buffer object ID
	int singleVertexByteSize;
	int indexCount;

	virtual void SetParentEntity(Entity &e) override;
};