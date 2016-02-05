#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
	Window(const std::string& title, const sf::Vector2u& size, bool fullscreen = false);
	~Window();

	void update();
	void clear();
	void draw(sf::Drawable& drawable);
	void display();

	void toggleFullscreen();

	bool isOpen();

private:
	void create();
	void close();

	sf::RenderWindow m_window;

	std::string m_title;
	sf::Vector2u m_size;
	bool m_fullscreen;
	bool m_isOpen;
};