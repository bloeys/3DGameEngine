#include <iostream>
#include <GL/glew.h>
#include "EngineCore.h"
#include "GameWindow.h"
#include "Game.h"
#include "RenderUtility.h"
#include "GameTime.h"
#include "Input.h"
#include "Printer.h"
#include "MeshSystem.h"
#include "TransformSystem.h"

using namespace sf;

EngineCore::EngineCore() : engineHalted(false), isEngineRunning(false), game(nullptr), gWindow(nullptr)
{
	//Bring window to life
	gWindow = new GameWindow;
	gWindow->Initialize("3D Game Engine");
	Input::SetActiveWindow(gWindow);

	//Init opengl and glew and stuff
	RenderUtil::InitGraphics();
	RenderUtil::PrintOpenGLVersion();
}

void EngineCore::Start()
{
	if (isEngineRunning)
		return;

	//If this is the first time start is being called
	if (game == nullptr)
		game = new Game();

	Update();
}

void EngineCore::Update()
{
	isEngineRunning = true;

	//While window is open
	while (isEngineRunning)
	{
		if (Input::closePressed)
			Stop();

		//Send updates
		Input::Update();
		game->Input();
		game->Update();
		Render();

		//Update delta time
		GameTime::delta = frameTimer.restart().asSeconds();
	}

	if (!engineHalted)
		Cleanup();
}

void EngineCore::Render()
{
	RenderUtil::ClearScreen();
	game->Render();
	gWindow->Render();
}

void EngineCore::Stop()
{
	if (!isEngineRunning)
		return;

	isEngineRunning = false;
}

void EngineCore::HaltEngine()
{
	//If engine is already halted don't continue
	if (engineHalted)
		return;

	engineHalted = true;
	Stop();	//Stop the engine

	std::string s;
	std::getline(std::cin, s);

	if (s == "Close" || s == "close")
	{
		Cleanup();
	}

	else
	{
		//Clear console window
		if (s == "Clean" || s == "clean")
			for (int i = 0; i < 20; i++)
				std::cout << std::endl << std::endl << std::endl;

		//Start engine again
		Start();
	}

	engineHalted = false;
}

void EngineCore::Cleanup()
{
	gWindow->Close();
}

EngineCore::~EngineCore()
{
	delete gWindow;
	delete game;
}