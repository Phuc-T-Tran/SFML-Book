#include "Game.h"



Game::Game() : m_window("Game", { 1280,720 })
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