#pragma once

#include "Table.h"
#include "Snake.h"

class GameField
{
private:
	Table table;
	Snake snake;
	int points;
	bool snakeAlive;

	bool movementRendered;
	bool borderRendered;
	bool pointsRendered;
	Coordinate snakeOldTail;

public:
	GameField(int width, int height);
	~GameField();

	void processInput();
	void update();
	void render();
	bool isAlive();

private:
	void placeAppleOnTable();
	void renderTable();
	void renderPoints();
	void renderSnake();
	void renderApple();
	void renderGameOver();

	void writeToPosition(int x, int y, char c);
	void setCursorPosition(int x, int y);
	void setConsoleColour(unsigned short colour);
};

