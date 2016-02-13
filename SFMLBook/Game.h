#pragma once
#include "Window.h"

class Game
{
public:
	Game(const std::string& title = "Default Title", const float fps = 30, const unsigned width = 640, const unsigned height = 480);
	~Game();

	void run();

	void setFPS(float fps);
	Window* getWindow();

protected:
	virtual void handleInput();
	virtual void update();
	virtual void render();
	int getWidth();
	int getHeight();

	Window m_window;
	float m_fps;
	int m_width;
	int m_height;
};

