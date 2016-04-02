#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#pragma once
#include <GL/glew.h>

struct OGLTexture
{
	GLuint id;
	int width, height;
};

#endif // !GLTEXTURE_H