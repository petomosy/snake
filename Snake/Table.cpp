#include "Table.h"

Table::Table()
{
	this->width = 20;
	this->height = 20;
}

Table::Table(int width, int height)
{
	this->width = width + 2;
	this->height = height + 2;
}

Table::~Table()
{
}

int Table::getWidth()
{
	return width;
}

int Table::getHeight()
{
	return height;
}

void Table::setApplePlace(Coordinate applePlace)
{
	this->applePlace = applePlace;
}

Coordinate Table::getApplePlace()
{
	return applePlace;
}

bool Table::isWallAt(Coordinate coordinate)
{
	return coordinate.x == 0 || coordinate.y == 0 || coordinate.x >= width - 1 || coordinate.y >= height - 1;
}

bool Table::isAppleAt(Coordinate coordinate)
{
	return coordinate.x == applePlace.x && coordinate.y == applePlace.y;
}
