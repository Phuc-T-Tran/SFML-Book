#pragma once
#include "Core/Game.h"
#include "Core/Textbox.h"
#include "Snake.h"

class SnakeGame : public Game
{
public:
	SnakeGame();
	~SnakeGame();

	void spawnApple();

protected:
	virtual void handleInput();
	virtual void update();
	virtual void render();

private:
	bool snakeOutOfBounds();

	const int BLOCK_SIZE;
	Snake m_snake;
	sf::CircleShape m_apple;
	int m_highScore;

	Textbox m_textbox;
	Textbox m_scorebox;
};

