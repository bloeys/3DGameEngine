#pragma once

#include "MySprite.h"
class Game
{
public:

	void Input();
	void Update();
	void Render();

	Game();
	~Game();

private:
	float seconds;
	int frames;
	MySprite spr;
	void InitSystems();
};