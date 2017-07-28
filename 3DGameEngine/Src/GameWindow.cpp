#include "GameWindow.h"

GameWindow::GameWindow()
{
}

void GameWindow::Initialize(const std::string &title) 
{
	window.create(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), title);
}

void GameWindow::Render()
{
	window.display();
}

void GameWindow::Resized()
{

}

void GameWindow::Close()
{
	window.close();
}

GameWindow::~GameWindow()
{
}