#include "Textbox.h"
#include <iostream>


Textbox::Textbox()
{
}


Textbox::~Textbox()
{
}

Textbox::Textbox(int numVisible, int charSize, int width, sf::Vector2f position)
	: m_numVisible(numVisible)
{
	m_backdrop.setFillColor({ 20, 20, 20, 120 });
	m_backdrop.setPosition(position);
	m_backdrop.setSize(sf::Vector2f{(float)width,(float)charSize*numVisible*1.3f});

	m_font.loadFromFile("data/fonts/Roboto-Regular.ttf");

	m_content.setPosition(position); // Offset added
	m_content.setCharacterSize(charSize);
	m_content.setFont(m_font);
	m_content.setColor(sf::Color(255,255,255,155));
}


void Textbox::init(int numVisible, int charSize, int width, sf::Vector2f position)
{

}

void Textbox::add(const std::string& message)
{
	m_messages.push_back(message);
	if (m_messages.size() > m_numVisible)
		m_messages.erase(m_messages.begin());
}
void Textbox::clear()
{
	m_messages.clear();
}

void Textbox::render(sf::RenderWindow& window)
{
	//window.draw(m_backdrop);

	std::string content;
	for (auto &it : m_messages)
		content.append(it + "\n");

	m_content.setString(content);
	window.draw(m_content);
}