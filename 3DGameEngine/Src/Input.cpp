#include <glm/vec2.hpp>
#include <unordered_map>
#include "Input.h"
#include "GameWindow.h"

namespace Input
{
	//Private vars
	static std::unordered_map<sf::Keyboard::Key, bool> pressedKeyboardKeys;	//Holds pressed keys and a bool that states whether each key was pressed this frame or not
	static std::unordered_map<sf::Mouse::Button, bool> pressedMouseButtons;	//Holds pressed mouse buttons and a bool that states whether each key was pressed this frame or not
	static GameWindow *gameWindow = nullptr;	//Pointer to engine window

	//Whether the window close button has been pressed or not
	bool Input::closePressed;

	void SetActiveWindow(GameWindow *w)
	{
		gameWindow = w;
	}

	void Input::Update()
	{
		//Make the bool for 'pressed this frame' false for all keys
		for (auto &i : pressedKeyboardKeys)
		{
			i.second = false;
		}

		for (auto &i : pressedMouseButtons)
		{
			i.second = false;
		}

		//Poll events
		sf::Event ev;
		while (gameWindow->window.pollEvent(ev))
		{
			//If a key is pressed and it doesn't exist in our map add it and set it to pressed this frame
			if (ev.type == sf::Event::KeyPressed && pressedKeyboardKeys.find(ev.key.code) == pressedKeyboardKeys.end())
			{
				pressedKeyboardKeys[ev.key.code] = true;
			}

			//Remove key if its released
			else if (ev.type == sf::Event::KeyReleased)
			{
				pressedKeyboardKeys.erase(ev.key.code);
			}

			//Add mouse keys
			else if (ev.type == sf::Event::MouseButtonPressed && pressedMouseButtons.find(ev.mouseButton.button) == pressedMouseButtons.end())
			{
				pressedMouseButtons[ev.mouseButton.button] = true;
			}

			//Remove mouse keys
			else if (ev.type == sf::Event::MouseButtonReleased)
			{
				pressedMouseButtons.erase(ev.mouseButton.button);
			}

			//Update close button bool
			else if (ev.type == sf::Event::Closed)
			{
				closePressed = true;
			}

			else if (ev.type == sf::Event::Resized)
			{
				gameWindow->Resized();
			}
		}
	}

	///<summary>Returns true if a key is pressed</summary>
	bool Input::IsKeyHeld(sf::Keyboard::Key key)
	{
		return pressedKeyboardKeys.find(key) != pressedKeyboardKeys.end();
	}

	///<summary>Returns true if a key was pressed this frame</summary>
	bool Input::IsKeyPressed(sf::Keyboard::Key key)
	{
		return pressedKeyboardKeys.find(key) != pressedKeyboardKeys.end() && pressedKeyboardKeys[key];
	}

	bool Input::IsMouseHeld(sf::Mouse::Button button)
	{
		return pressedMouseButtons.find(button) != pressedMouseButtons.end();
	}

	bool Input::IsMousePressed(sf::Mouse::Button button)
	{
		return pressedMouseButtons.find(button) != pressedMouseButtons.end() && pressedMouseButtons[button];
	}

	bool Input::IsAnyKeyDown()
	{
		return pressedKeyboardKeys.size() > 0;
	}

	bool Input::IsAnyMouseDown()
	{
		return pressedMouseButtons.size() > 0;
	}

	///Position in desktop coordinates
	glm::ivec2 Input::GetGlobalMousePos()
	{
		sf::Vector2<int> mousePos = sf::Mouse::getPosition();
		return glm::ivec2(mousePos.x, mousePos.y);
	}

	///Position in active window coordinates
	glm::ivec2 Input::GetLocalMousePos()
	{
		sf::Vector2<int> mousePos = sf::Mouse::getPosition(gameWindow->window);
		return glm::ivec2(mousePos.x, mousePos.y);
	}
}