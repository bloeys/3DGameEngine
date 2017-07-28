#include <cstddef>	//To use 'offsetof'
#include "Mesh.h"
#include "Printer.h"
#include "MeshSystem.h"
#include "Entity.h"

Mesh::Mesh() : vboID(0), iboID(0), singleVertexByteSize(0), indexCount(0)
{
	type = ComponentType::Mesh;
	requiredComponents = ComponentType::None;
	
	//Generate buffers
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &iboID);
}

void Mesh::AddVertices(const std::vector<Vertex> &vertices, const std::vector<int> &indices)
{
	singleVertexByteSize = sizeof(Vertex);
	indexCount = indices.size();	//Store vertex count

	glBindBuffer(GL_ARRAY_BUFFER, vboID);	//Bind buffer of type x to this ID
	glBufferData(GL_ARRAY_BUFFER, singleVertexByteSize * vertices.size(), &vertices[0], GL_STATIC_DRAW);	//Assign data to buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);	//Bind buffer of this type to this id
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexCount, &indices[0], GL_STATIC_DRAW);	//Buffer the data
}

void Mesh::AddVertices(const MeshData &mData)
{
	singleVertexByteSize = sizeof(Vertex);
	indexCount = mData.indices.size();	//Store vertex count

	glBindBuffer(GL_ARRAY_BUFFER, vboID);	//Bind buffer of type x to this ID
	glBufferData(GL_ARRAY_BUFFER, singleVertexByteSize * mData.vertices.size(), &mData.vertices[0], GL_STATIC_DRAW);	//Assign data to buffer

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);	//Bind buffer of this type to this id
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indexCount, &mData.indices[0], GL_STATIC_DRAW);	//Buffer the data
}

void Mesh::SetParentEntity(Entity& e)
{
	if (!parentEntity)
	{
		parentEntity = std::make_shared<Entity>(e);
		System::AddToSystem(e, System::SystemType::RenderSystem);
	}
}

void Mesh::Draw()
{
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, singleVertexByteSize, (void *)offsetof(Vertex, pos));	//Position attribute
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, singleVertexByteSize, (void *)offsetof(Vertex, color));	//Color attribute

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);	//Draw the vertices as specified by the indicies
}

Mesh::~Mesh()
{
	//Free buffers
	glDeleteBuffers(1, &vboID);
	glDeleteBuffers(1, &iboID);
}