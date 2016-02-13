#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

enum class Direction { None, Up, Down, Left, Right };

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x, y) {}
	sf::Vector2i position;
};

using SnakeContainer = std::vector<SnakeSegment>;

class Snake
{
public:
	Snake(int length);
	~Snake();

	void move();
	void update();
	void render(sf::RenderWindow& window);

private:
	SnakeContainer m_body;
	int m_size;
	Direction m_dir;
	int m_speed;
	sf::RectangleShape m_rect;
};