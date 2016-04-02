#include "RenderUtility.h"
#include <GL/glew.h>
#include "Printer.h"

void RenderUtil::InitGraphics()
{
	if (glewInit() != GLEW_OK)
		Printer::PrintError("Glew failed to initialize");

	glClearColor(0, 0, 1, 1);
	glFrontFace(GL_CW);	//Clock wise vertices is front face
	glCullFace(GL_BACK);	//Cull back face
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_FRAMEBUFFER_SRGB);
}

void RenderUtil::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderUtil::PrintOpenGLVersion()
{
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}