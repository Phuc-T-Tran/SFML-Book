#include "Snake.h"


Snake::Snake(int size) : m_size(size)
{
	m_rect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	respawn();
}

Snake::~Snake()
{

}

void Snake::respawn()
{
	m_body.clear();

	m_body.push_back(SnakeSegment(5, 7));
	m_body.push_back(SnakeSegment(5, 6));
	m_body.push_back(SnakeSegment(5, 5));

	setDirection(Direction::None);
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}

void Snake::move()
{
	// "Inchworm" up to the head
	for (int i = m_body.size() - 1; i > 0; i--)
	{
		m_body[i].position = m_body[i - 1].position;
	}

	// Handle the head's new position based on direction
	switch (m_dir)
	{
	case Direction::Up:
		m_body[0].position.y--;
		break;
	case Direction::Down:
		m_body[0].position.y++;
		break;
	case Direction::Left:
		m_body[0].position.x--;
		break;
	case Direction::Right:
		m_body[0].position.x++;
		break;
	}
}

void Snake::update()
{
	if (m_body.empty() || m_dir == Direction::None)
		return;

	move();
	checkSelfCollision();
}

void Snake::extend()
{
	if (m_body.size() < 2)
		return;

	auto tail = m_body[m_body.size() - 1];
	auto prevTail = m_body[m_body.size() - 2];

	if (tail.position.x == prevTail.position.x)
	{
		if (tail.position.y < prevTail.position.y)
			m_body.push_back(SnakeSegment(tail.position.x, tail.position.y - 1));
		else
			m_body.push_back(SnakeSegment(tail.position.x, tail.position.y + 1));
	}
	else
	{
		if (tail.position.x < prevTail.position.x)
			m_body.push_back(SnakeSegment(tail.position.x - 1, tail.position.y));
		else
			m_body.push_back(SnakeSegment(tail.position.x + 1, tail.position.y));
	}
}

void Snake::render(sf::RenderWindow& window)
{
	if (m_body.empty())
		return;

	// Draw the head
	auto head = m_body.begin();
	m_rect.setFillColor(sf::Color(70,255,70));
	m_rect.setPosition(head->position.x * m_size, head->position.y * m_size);
	window.draw(m_rect);

	// Draw the body
	m_rect.setFillColor(sf::Color(70,200,70));
	for (auto it = m_body.begin() + 1; it != m_body.end(); it++)
	{
		m_rect.setPosition(it->position.x * m_size, it->position.y * m_size);
		window.draw(m_rect);
	}
}

void Snake::setDirection(Direction dir)
{
	m_dir = dir;
}

void Snake::incScore(int amount)
{
	m_score += amount;
}

void Snake::loseLife() { m_lives--; }

Direction Snake::getDirection()
{
	return m_dir;
}

sf::Vector2i Snake::getHeadPosition()
{
	if (m_body.empty())
		return sf::Vector2i(-1, -1);

	return sf::Vector2i(m_body[0].position.x * m_size, m_body[0].position.y * m_size);
}

void Snake::checkSelfCollision()
{
	// Can't possibly collide with self
	// with 4 or less segments
	if (m_body.size() < 5)
		return;

	for (int i = 4; i < m_body.size(); i++)
	{
		if (m_body[0].position == m_body[i].position)
		{
			cut(m_body.size() - i);
			m_lives--;
			m_lost = (m_lives < 1);
			return;
		}
	}
}

void Snake::cut(int numSegments)
{
	m_body.erase(m_body.end() - numSegments, m_body.end());
}

bool Snake::isDead()
{
	return m_lost;
}

SnakeContainer& Snake::getBody()
{
	return m_body;
}

int Snake::getLives() { return m_lives; }
int Snake::getScore() { return m_score; }
int Snake::getSize() { return m_body.size(); }