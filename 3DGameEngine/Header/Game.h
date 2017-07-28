#pragma once

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

	void InitSystems();
};