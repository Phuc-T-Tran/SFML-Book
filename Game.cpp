#include "Game.h"


Game::Game(const std::string& title, const unsigned width, const unsigned height)
	: m_window(title, { width,height })
{
}


Game::~Game()
{
}

void Game::run()
{
	while (m_window.isOpen())
	{
		handleInput();
		update();
		render();
	}
}

void Game::handleInput()
{

}

void Game::update()
{
	m_window.update();
}

void Game::render()
{
	m_window.clear();
	m_window.display();
}

Window* Game::getWindow()
{
	return &m_window;
}