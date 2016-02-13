#pragma once
#include "Window.h"

class Game
{
public:
	Game(const std::string& title = "Default Title", const unsigned width = 640, const unsigned height = 480);
	~Game();

	void run();

	Window* getWindow();

private:
	virtual void handleInput();
	virtual void update();
	virtual void render();

	Window m_window;
};

