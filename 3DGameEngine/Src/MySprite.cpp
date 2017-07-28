#include "MySprite.h"
#include "GL\glew.h"

MySprite::MySprite()
{
	glGenBuffers(1, &vboID);
	glGenBuffers(1, &iboID);
}

void MySprite::SetParentEntity()
{
}

void MySprite::SetTexture(OGLTexture &tex)
{
	int x = 0, y = 0;
	texture = tex;
	float vertexData[12];

	//First triangle
	vertexData[0] = x + texture.width;
	vertexData[1] = y + texture.height;

	vertexData[2] = x + texture.width;
	vertexData[3] = y - texture.height;

	vertexData[4] = x - texture.width;
	vertexData[5] = y - texture.width;

	//Second triangle
	vertexData[6] = x - texture.width;
	vertexData[7] = y - texture.height;

	vertexData[8] = x - texture.width;
	vertexData[9] = y + texture.height;

	vertexData[10] = x + texture.width;
	vertexData[11] = y + texture.width;

	int ibo[12];
	ibo[0] = 0;
	ibo[1] = 1;
	ibo[2] = 2;
	ibo[3] = 3;
	ibo[4] = 4;
	ibo[5] = 5;
	ibo[6] = 6;
	ibo[7] = 7;
	ibo[8] = 8;
	ibo[9] = 9;
	ibo[10] = 10;
	ibo[11] = 11;

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 12, ibo, GL_STATIC_DRAW);

}

void MySprite::Draw()
{
	int ibo[12];
	ibo[0] = 0;
	ibo[1] = 1;
	ibo[2] = 2;
	ibo[3] = 3;
	ibo[4] = 4;
	ibo[5] = 5;
	ibo[6] = 6;
	ibo[7] = 7;
	ibo[8] = 8;
	ibo[9] = 9;
	ibo[10] = 10;
	ibo[11] = 11;
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, ibo);
}

MySprite::~MySprite()
{
	if (vboID != 0)
		glDeleteBuffers(1, &vboID);
	if (iboID!= 0)
		glDeleteBuffers(1, &iboID);
}