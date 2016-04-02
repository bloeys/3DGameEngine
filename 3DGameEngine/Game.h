#pragma once

#ifndef GAME_H
#define GAME_H

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
};
#endif // !GAME_H