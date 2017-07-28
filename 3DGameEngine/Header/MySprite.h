#pragma once

#include <GL/glew.h>

class MySprite
{
public:

	void SetParentEntity();

	MySprite(float x, float y, float width, float height);
	~MySprite();

private:
	GLuint vboID = 0;
};