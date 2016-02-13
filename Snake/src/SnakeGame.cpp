#include "SnakeGame.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

SnakeGame::SnakeGame()
	: Game("Snake", 15.0f, 720, 480), BLOCK_SIZE(m_width/40),
	m_snake(BLOCK_SIZE), m_textbox(1, 18, 120, { 10,10 }),
	m_scorebox(1, 18, 120, { 10,28 }), m_highScore(0)
{
	srand(time(nullptr));

	m_textbox.add("Score: 0");
	m_scorebox.add("High Score: 0");

	m_apple.setRadius(BLOCK_SIZE / 2);
	m_apple.setFillColor(sf::Color(255,70,70));
	spawnApple();
}

SnakeGame::~SnakeGame()
{
}

void SnakeGame::handleInput()
{
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::W)))
		&& m_snake.getDirection() != Direction::Down)
		m_snake.setDirection(Direction::Up);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::S)))
		&& m_snake.getDirection() != Direction::Up)
		m_snake.setDirection(Direction::Down);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::A)))
		&& m_snake.getDirection() != Direction::Right)
		m_snake.setDirection(Direction::Left);
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
		&& m_snake.getDirection() != Direction::Left)
		m_snake.setDirection(Direction::Right);
}

void SnakeGame::update()
{
	int oldSize = m_snake.getSize();
	m_snake.update();
	if (m_snake.getSize() != oldSize)
		m_textbox.add("You bit yourself! Lives: " + std::to_string(m_snake.getLives()));

	if ((sf::Vector2f)m_snake.getHeadPosition() == m_apple.getPosition())
	{
		m_snake.incScore(10);
		m_textbox.add("Score: " + std::to_string(m_snake.getScore()));
		m_snake.extend();
		spawnApple();
	}
	else if (snakeOutOfBounds() || m_snake.isDead())
	{
		if (m_snake.getScore() > m_highScore)
		{
			m_highScore = m_snake.getScore();
			m_scorebox.add("High Score: " + std::to_string(m_snake.getScore()));
		}

		m_textbox.add("DEATH! Your score was: " + std::to_string(m_snake.getScore()));
		m_snake.respawn();
		spawnApple();
	}
}

void SnakeGame::render()
{
	m_snake.render(m_window.getRenderWindow());
	m_window.getRenderWindow().draw(m_apple);
	m_textbox.render(m_window.getRenderWindow());
	m_scorebox.render(m_window.getRenderWindow());
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