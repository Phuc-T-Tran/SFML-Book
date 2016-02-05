#include "Window.h"

Window::Window(const std::string& title, const sf::Vector2u& size, bool fullscreen)
	: m_title(title), m_size(size), m_fullscreen(fullscreen), m_isOpen(true)
{
	create();
}

Window::~Window()
{
	close();
}


void Window::create()
{
	auto style = m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
	m_window.create({ m_size.x, m_size.y, 32 }, m_title, style);
}
void Window::close() { m_window.close(); }

void Window::update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_isOpen = false;
		else if (event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::F5)
			toggleFullscreen();
	}
}
void Window::clear() { m_window.clear(); }
void Window::display() { m_window.display(); }


void Window::toggleFullscreen()
{
	m_fullscreen = !m_fullscreen;
	close();
	create();
}

bool Window::isOpen() { return m_isOpen; }