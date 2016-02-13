#include "Window.h"
#include <iostream>


Window::Window(const std::string& title, const sf::Vector2u& size, bool fullscreen)
	: m_title(title), m_size(size), m_resolution(size), m_fullscreen(fullscreen), m_isOpen(true)
{
	create();
}

Window::~Window()
{
	close();
}


void Window::create()
{
	auto style = m_fullscreen ? sf::Style::Fullscreen :
		         m_borderless? sf::Style::None :
		         sf::Style::Default;
	m_window.create({ m_size.x, m_size.y, 32 }, m_title, style);

	m_window.setView(sf::View({ 0,0,(float)m_resolution.x,(float)m_resolution.y }));
	m_window.setMouseCursorVisible(false);
}
void Window::close() { m_window.close(); }

void Window::update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_isOpen = false;
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_isOpen = false;
				break;
			case sf::Keyboard::F5:
				toggleFullscreen();
				break;
			case sf::Keyboard::F6:
				toggleBorderless();
				break;
			}
		}
	}
}
void Window::clear() { m_window.clear(); } // NOTE: Can add sf::Color parameter to clear().  TODO: Window color member
void Window::draw(sf::Drawable& drawable) { m_window.draw(drawable); }
void Window::display() { m_window.display(); }


void Window::toggleFullscreen()
{
	if (m_borderless)
		m_borderless = !m_borderless;

	m_fullscreen = !m_fullscreen;
	close();
	create();
}

void Window::toggleBorderless()
{
	if (m_fullscreen)
		m_fullscreen = !m_fullscreen;

	m_borderless = !m_borderless;

	if (m_borderless)
	{
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		m_size.x = desktop.width;
		m_size.y = desktop.height;
	}
	else
		m_size = m_resolution;

	close();
	create();
}

bool Window::isOpen() { return m_isOpen; }

sf::RenderWindow& Window::getRenderWindow() { return m_window; }