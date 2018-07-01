#pragma once

#include "Coordinate.h"

class Table
{
private:
	int width;
	int height;

	Coordinate applePlace;

public:
	Table();
	Table(int width, int height);
	~Table();

	int getWidth();
	int getHeight();

	void setApplePlace(Coordinate applePlace);
	Coordinate getApplePlace();

	bool isWallAt(Coordinate coordinate);
	bool isAppleAt(Coordinate coordinate);
};
