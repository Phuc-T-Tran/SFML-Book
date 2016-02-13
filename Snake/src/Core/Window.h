#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Window
{
public:
	Window(const std::string& title, const sf::Vector2u& size, bool fullscreen = false);
	~Window();

	void create();
	void close();

	void update();
	void clear();
	void draw(sf::Drawable& drawable);
	void display();

	void toggleFullscreen();
	void toggleBorderless();

	bool isOpen();
	sf::RenderWindow& getRenderWindow();

private:
	sf::RenderWindow m_window;

	std::string m_title;
	sf::Vector2u m_size;
	sf::Vector2u m_resolution;
	bool m_fullscreen;
	bool m_borderless;
	bool m_isOpen;
};