#pragma once

#ifndef ENGINECORE_H
#define ENGINECORE_H

#include <SFML/System.hpp>

class GameWindow;
class Game;

class EngineCore
{
public:
	GameWindow *gWindow;
	bool isEngineRunning;

	void Start();
	void Stop();
	void HaltEngine();

	EngineCore();
	~EngineCore();

private:
	Game *game;
	sf::Clock frameTimer;
	bool engineHalted;

	void Update();
	void Render();
	void Cleanup();
};
#endif // !ENGINECORE_H