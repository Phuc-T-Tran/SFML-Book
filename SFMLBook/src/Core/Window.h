#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "EventManager.h"

class Window
{
public:
	Window(const std::string& title, const sf::Vector2u& size, bool fullscreen = false);
	~Window();

	void create();
	void close(EventData* data = nullptr);

	void update();
	void clear();
	void draw(sf::Drawable& drawable);
	void display();

	void toggleFullscreen(EventData* data);
	void toggleBorderless(EventData* data);

	bool isOpen();
	sf::RenderWindow& getRenderWindow();
	EventManager& getEventManager();

private:
	sf::RenderWindow m_window;
	EventManager m_eventManager;

	std::string m_title;
	sf::Vector2u m_size;
	sf::Vector2u m_resolution;
	bool m_fullscreen;
	bool m_borderless;
	bool m_isOpen;
	bool m_hasFocus;
};