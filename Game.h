#pragma once
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void run();

	Window* getWindow();

private:
	void handleInput();
	void update();
	void render();

	Window m_window;
};

