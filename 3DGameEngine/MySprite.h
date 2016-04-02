#pragma once

#ifndef MYSPRITE_H
#define MYSPRITE_H

#include <GL/glew.h>

class MySprite
{
public:

	void Init();

	MySprite(float x, float y, float width, float height);
	~MySprite();

private:
	GLuint vboID = 0;
};

#endif