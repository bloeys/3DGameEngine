#pragma once

#include <glm/fwd.hpp>
#include <SFML/Window.hpp>

class GameWindow;

namespace Input
{
	extern bool closePressed;	//Whether the window close button has been pressed or not

	void SetActiveWindow(GameWindow *w);
	void Update();

	bool IsKeyHeld(sf::Keyboard::Key key);
	bool IsKeyPressed(sf::Keyboard::Key key);
	bool IsMouseHeld(sf::Mouse::Button button);
	bool IsMousePressed(sf::Mouse::Button button);
	bool IsAnyKeyDown();
	bool IsAnyMouseDown();

	glm::ivec2 GetGlobalMousePos();
	glm::ivec2 GetLocalMousePos();
}