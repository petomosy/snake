#include "Snake.h"

Snake::Snake()
{
	isCollision = false;
	parts.push_back(SnakePart(3, 1, RIGHT));
	parts.push_back(SnakePart(2, 1, RIGHT));
	parts.push_back(SnakePart(1, 1, RIGHT));
}

Snake::~Snake()
{
}

void Snake::eat()
{
	parts.push_front(getNextHead());
}

Coordinate Snake::move()
{
	parts.push_front(getNextHead());
	
	SnakePart oldTail = parts.back();
	parts.pop_back();

	calculateCollision();

	return oldTail.place;
}

void Snake::setDirection(Direction direction)
{
	if (parts.front().direction == LEFT && direction == RIGHT ||
		parts.front().direction == RIGHT && direction == LEFT ||
		parts.front().direction == UP && direction == DOWN ||
		parts.front().direction == DOWN && direction == UP)
	{
		return;
	}

	parts.front().direction = direction;
}

SnakePart Snake::getNextHead()
{
	SnakePart head = parts.front();

	switch (head.direction)
	{
	case RIGHT:
		head.place.x++;
		break;

	case LEFT:
		head.place.x--;
		break;

	case UP:
		head.place.y--;
		break;

	case DOWN:
		head.place.y++;
		break;
	}

	return head;
}

bool Snake::getIsCollision()
{
	return isCollision;
}

const std::list<SnakePart>& Snake::getParts()
{
	return parts;
}

void Snake::calculateCollision()
{
	Coordinate head = parts.front().place;

	std::list<SnakePart>::const_iterator it = getParts().begin();
	for (++it; it != getParts().end() && !isCollision; it++) {
		isCollision = it->place.x == head.x && it->place.y == head.y;
	}
}
