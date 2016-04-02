#include "MySprite.h"

void MySprite::Init()
{
}

MySprite::MySprite(float x, float y, float width, float height)
{
	glGenBuffers(1, &vboID);

	float vertexData[12];

	//First triangle
	vertexData[0] = x + width;
	vertexData[1] = y + height;

	vertexData[2] = x + width;
	vertexData[3] = y - height;

	vertexData[4] = x - width;
	vertexData[5] = y - width;

	//Second triangle
	vertexData[6] = x - width;
	vertexData[7] = y - height;

	vertexData[8] = x - width;
	vertexData[9] = y + height;

	vertexData[10] = x + width;
	vertexData[11] = y + width;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

MySprite::~MySprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
}