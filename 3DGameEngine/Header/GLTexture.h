#pragma once

#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include <GL/glew.h>

struct OGLTexture
{
	GLuint id;
	int width, height;
};

#endif // !GLTEXTURE_H