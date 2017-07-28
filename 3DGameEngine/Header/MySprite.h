#pragma once

#include "OGLTexture.h"

class MySprite
{
public:

	void SetParentEntity();

	MySprite();
	void SetTexture(OGLTexture &tex);
	void Draw();
	~MySprite();

private:
	OGLTexture texture;
	unsigned int vboID, iboID;
};