#pragma once

#ifndef MeshData_H
#define MeshData_H

#include <vector>
#include "Vertex.h"

struct MeshData
{
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	MeshData() {}

	MeshData(std::vector<Vertex> &verts, std::vector<int> &meshIndices)
	{
		vertices = verts;
		indices = meshIndices;
	}

	void SetData(std::vector<Vertex> &verts, std::vector<int> &meshIndices)
	{
		vertices = verts;
		indices = meshIndices;
	}
};
#endif