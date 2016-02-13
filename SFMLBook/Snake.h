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

	void respawn();
	void move();
	void update();
	void extend();
	void render(sf::RenderWindow& window);

	void setDirection(Direction dir);
	Direction getDirection();
	sf::Vector2i getHeadPosition();
	bool isDead();
	SnakeContainer& getBody();

private:
	void checkSelfCollision();
	void cut(int numSegments);

	sf::RectangleShape m_rect;
	SnakeContainer m_body;
	Direction m_dir;
	int m_size;
	int m_lives;
	int m_score;
	int m_lost;
};