#include <vector>
#include "Game.h"
#include "Input.h"
#include "GameTime.h"
#include "Printer.h"
#include "Mesh.h"
#include "GLSLProgram.h"
#include "Vertex.h"
#include "MyTransform.h"
#include "ResourceLoader.h"
#include "GLTexture.h"

Mesh *m;
GLSLProgram glp;
MyTransform tr;
float transformationSpd = 0;

Game::Game() : seconds(0), frames(0)
{
	glp.CompileShader(R"(Resources\Shaders\SimpleColorShader.vert)", R"(Resources\Shaders\SimpleColorShader.frag)");
	glp.AddAttribute("vertPos");
	glp.AddAttribute("vertColor");
	glp.LinkShaders();
	glp.AddUniform("transformation");

	m = new Mesh();
	tr.SetPosition(0, 0, 20);

	OGLTexture g = {};
	ResourceLoader::LoadTexture(R"(Resources\Textures\ButtonRound_Red.png)", g);
	if (g.id != 0)
		Printer::Print("Texture Loaded");

	if (ResourceLoader::LoadMesh(R"(Resources\Models\SimpleCube.obj)", *m))
		Printer::Print("Mesh Loaded");
}

void Game::Input()
{
}

void Game::Update()
{
	//Handle updating and printing framerate
	seconds += GameTime::delta;
	if (seconds >= 1)
	{
		Printer::Print(frames);
		seconds = frames = 0;
	}

	else
		frames++;

	transformationSpd += GameTime::delta * 2;
	tr.Rotate(0, 45 * GameTime::delta, 0);
	tr.SetPosition(0, sin(transformationSpd) * 0.5f, 20);
}

void Game::Render()
{
	glp.Use();
	glp.SetUniform("transformation", tr.GetProjectedTransformationMatrix());
	m->Draw();
	glp.UnUse();
}

Game::~Game()
{
}