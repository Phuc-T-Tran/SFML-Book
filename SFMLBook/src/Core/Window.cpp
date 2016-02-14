#include "Window.h"
#include <iostream>


Window::Window(const std::string& title, const sf::Vector2u& size, bool fullscreen)
	: m_title(title), m_size(size), m_resolution(size), m_fullscreen(fullscreen), m_isOpen(true), m_hasFocus(true)
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

	m_eventManager.addCallback("closeWindow", &Window::close, this);
	m_eventManager.addCallback("toggleFullscreen", &Window::toggleFullscreen, this);
	m_eventManager.addCallback("toggleBorderless", &Window::toggleBorderless, this);
}

void Window::close(EventData* data)
{
	m_window.close();
	m_eventManager.removeCallback("closeWindow");
	m_eventManager.removeCallback("toggleFullscreen");
}

void Window::update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus)
		{
			m_hasFocus = false;
			m_eventManager.setFocus(false);
		}
		else if (event.type == sf::Event::LostFocus)
		{
			m_hasFocus = true;
			m_eventManager.setFocus(true);
		}
		m_eventManager.handleEvent(event);
	}
	m_eventManager.update();
}
void Window::clear() { m_window.clear(); } // NOTE: Can add sf::Color parameter to clear().  TODO: Window color member
void Window::draw(sf::Drawable& drawable) { m_window.draw(drawable); }
void Window::display() { m_window.display(); }


void Window::toggleFullscreen(EventData* data)
{
	if (m_borderless)
		m_borderless = !m_borderless;

	m_fullscreen = !m_fullscreen;
	close();
	create();
}

void Window::toggleBorderless(EventData* data)
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