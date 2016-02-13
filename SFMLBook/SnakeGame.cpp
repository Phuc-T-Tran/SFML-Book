#include "SnakeGame.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

SnakeGame::SnakeGame()
	: Game("Snake", 20.0f, 720, 480), BLOCK_SIZE(m_width/40), m_snake(BLOCK_SIZE)
{
	srand(time(nullptr));
	m_apple.setRadius(BLOCK_SIZE / 2);
	m_apple.setFillColor(sf::Color(255,70,70));
	spawnApple();
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		&& m_snake.getDirection() != Direction::Down)
		m_snake.setDirection(Direction::Up);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
		&& m_snake.getDirection() != Direction::Up)
		m_snake.setDirection(Direction::Down);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
		&& m_snake.getDirection() != Direction::Right)
		m_snake.setDirection(Direction::Left);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
		&& m_snake.getDirection() != Direction::Left)
		m_snake.setDirection(Direction::Right);
}

void SnakeGame::update()
{
	m_snake.update();
	if ((sf::Vector2f)m_snake.getHeadPosition() == m_apple.getPosition())
	{
		m_snake.extend();
		spawnApple();
	}
	else if (snakeOutOfBounds() || m_snake.isDead())
	{
		m_snake.respawn();
		spawnApple();
	}
}

void SnakeGame::render()
{
	m_snake.render(m_window.getRenderWindow());
	m_window.getRenderWindow().draw(m_apple);
}

void SnakeGame::spawnApple()
{
	SnakeContainer body = m_snake.getBody();

	float xPos = rand() % ((getWidth() / BLOCK_SIZE) - 1);
	for (int i = 0; i < body.size();)
	{
		if (xPos == body[i].position.x)
		{
			xPos = rand() % ((getWidth() / BLOCK_SIZE) - 1);
			i = 0;
			continue;
		}
		i++;
	}

	float yPos = rand() % ((getHeight() / BLOCK_SIZE) - 1);
	for (int i = 0; i < body.size();)
	{
		if (yPos == body[i].position.y)
		{
			yPos = rand() % ((getHeight() / BLOCK_SIZE) - 1);
			i = 0;
			continue;
		}
		i++;
	}

	m_apple.setPosition({ xPos * BLOCK_SIZE, yPos * BLOCK_SIZE });
}

bool SnakeGame::snakeOutOfBounds()
{
	return m_snake.getHeadPosition().x < 0 || m_snake.getHeadPosition().x > getWidth() - BLOCK_SIZE ||
		m_snake.getHeadPosition().y < 0 || m_snake.getHeadPosition().y > getHeight() - BLOCK_SIZE;
}