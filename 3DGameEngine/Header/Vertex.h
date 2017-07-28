#pragma once

#include <GL/glew.h>
#include <glm/vec3.hpp>

struct Color
{
	Color() : r(255), g(255), b(255), a(255)
	{

	}

	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex
{
	Vertex() : color()
	{}

	Vertex(const float x, const float y, const float z) : color()
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	glm::vec3 pos;
	Color color;

	void SetPosition(const float x, const float y, const float z)
	{
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	void SetColor(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}
};