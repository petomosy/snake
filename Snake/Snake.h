#pragma once

#include <list>
#include "Coordinate.h"

// direction
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

// snake parts
struct SnakePart {
	Coordinate place;
	Direction direction = RIGHT;

	SnakePart(int x, int y, Direction direction) {
		this->place.x = x;
		this->place.y = y;
		this->direction = direction;
	}
};

// snake
class Snake
{
private:
	std::list<SnakePart> parts;
	bool isCollision;

public:
	Snake();
	~Snake();

	void eat();
	Coordinate move();
	void setDirection(Direction direction);
	
	SnakePart getNextHead();
	bool getIsCollision();

	const std::list<SnakePart>& getParts();

private:
	void calculateCollision();
};
