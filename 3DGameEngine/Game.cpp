#include <vector>
#include "Game.h"
#include "TransformSystem.h"
#include "MeshSystem.h"
#include "Input.h"
#include "GameTime.h"
#include "Printer.h"
#include "Mesh.h"
#include "Vertex.h"
#include "MyTransform.h"
#include "ResourceLoader.h"
#include "GLTexture.h"
#include "Entity.h"

Entity e, e2;
float transformationSpd = 0;

Game::Game() : seconds(0), frames(0)
{
	InitSystems();

	e.AddComponent(new MyTransform);
	e.AddComponent(new Mesh());
	e2.AddComponent(new MyTransform);
	e2.AddComponent(new Mesh);

	OGLTexture g = {};
	ResourceLoader::LoadTexture(R"(Resources/Textures/ButtonRound_Red.png)", g);
	if (g.id != 0)
		Printer::Print("Texture Loaded");

	if (ResourceLoader::LoadMesh(R"(Resources\Models\SimpleCube.obj)", *(Mesh*)e.GetComponent(Component::ComponentType::Mesh)))
		Printer::Print("Mesh Loaded");
	if (ResourceLoader::LoadMesh(R"(Resources\Models\SimpleCube.obj)", *(Mesh*)e2.GetComponent(Component::ComponentType::Mesh)))
		Printer::Print("Mesh Loaded");
}

void Game::InitSystems()
{
	new TransformSystem();
	new MeshSystem();
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

	//Rotate(0, 45 * GameTime::delta, 0);
	((MyTransform*)e.GetComponent(Component::ComponentType::Transform))->SetPosition(0, sin(transformationSpd) * 2, 20);
	((MyTransform*)e2.GetComponent(Component::ComponentType::Transform))->SetPosition(sin(transformationSpd) * 2, 0, 20);

	System::UpdateSystem(System::SystemType::TransformSystem);
}

void Game::Render()
{
	System::UpdateSystem(System::SystemType::RenderSystem);
}

Game::~Game()
{
}