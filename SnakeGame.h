#pragma once
#include "Game.h"
#include "Snake.h"

class SnakeGame : public Game
{
public:
	SnakeGame(int gridSize);
	~SnakeGame();

private:
	Snake snake;
};

