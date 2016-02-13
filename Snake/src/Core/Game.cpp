#include "Game.h"

Game::Game(const std::string& title, const float fps, const unsigned width, const unsigned height)
	: m_window(title, { width,height }), m_fps(fps), m_width(width), m_height(height)
{
}


Game::~Game()
{
}

void Game::run()
{
	sf::Clock clock;
	float time;
	float frameRate = 1.0f / m_fps;

	while (m_window.isOpen())
	{
		m_window.update();

		handleInput();
		update();

		m_window.clear();
		render();
		m_window.display();

		time = clock.getElapsedTime().asSeconds();
		if (frameRate > time)
			sf::sleep(sf::seconds(frameRate - time));
		clock.restart();
	}
}

void Game::handleInput()
{
}

void Game::update()
{
}

void Game::render()
{
}

void Game::setFPS(float fps)
{
	m_fps = fps;
}

Window* Game::getWindow()
{
	return &m_window;
}

int Game::getWidth()
{
	return m_width;
}

int Game::getHeight()
{
	return m_height;
}