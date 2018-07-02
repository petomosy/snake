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
	SnakePart nextHead = getNextHead();
	isCollision = isAt(nextHead.place);

	parts.push_front(nextHead);
	
	SnakePart oldTail = parts.back();
	parts.pop_back();

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

bool Snake::isAt(Coordinate coordinate)
{
	for (std::list<SnakePart>::const_iterator it = getParts().begin(); it != getParts().end() && !isCollision; it++) {
		if (it->place.x == coordinate.x && it->place.y == coordinate.y)
		{
			return true;
		}
	}

	return false;
}

const std::list<SnakePart>& Snake::getParts()
{
	return parts;
}
