#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

using MessageContainer = std::vector<std::string>;


class Textbox
{
public:
	Textbox();
	Textbox(int visible, int charSize, int width, sf::Vector2f position);
	~Textbox();

	void init(int visible, int charSize, int width, sf::Vector2f position);
	void add(const std::string& message);
	void clear();

	void render(sf::RenderWindow& window);

private:
	MessageContainer m_messages;
	int m_numVisible;

	sf::RectangleShape m_backdrop;
	sf::Font m_font;
	sf::Text m_content;
};

