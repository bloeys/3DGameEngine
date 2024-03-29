#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class GameWindow
{
public:
	static const int WINDOWWIDTH = 800;
	static const int WINDOWHEIGHT = 600;

	sf::RenderWindow window;

	void Initialize(const std::string &title);
	void Render();
	void Resized();
	void Close();

	GameWindow();
	~GameWindow();
};