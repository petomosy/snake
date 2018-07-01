#include "stdafx.h"
#include <ctime>
#include "GameField.h"

using namespace std;

GameField::GameField(int width, int height)
{
	table = Table(width, height);
	placeAppleOnTable();
	points = 0;
	snakeAlive = true;

	movementRendered = false;
	borderRendered = false;
	pointsRendered = false;
}

GameField::~GameField()
{
}

void GameField::processInput()
{
	if (GetAsyncKeyState(VK_UP))
	{
		snake.setDirection(UP);
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		snake.setDirection(DOWN);
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		snake.setDirection(LEFT);
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		snake.setDirection(RIGHT);
	}
}

void GameField::update()
{
	// move or feed snake
	if (table.isAppleAt(snake.getNextHead().place))
	{
		snake.eat();
		placeAppleOnTable();

		points++;
		pointsRendered = false;
	}
	else
	{
		snakeOldTail = snake.move();
		movementRendered = false;
	}

	// collision detection
	snakeAlive = !table.isWallAt(snake.getParts().front().place) && !snake.getIsCollision();
}

void GameField::render()
{
	if (snakeAlive) {
		renderSnake();
		renderTable();
		renderPoints();
		renderApple();
	}
	else
	{
		renderGameOver();
	}
}

bool GameField::isAlive()
{
	return snakeAlive;
}

void GameField::placeAppleOnTable()
{
	Coordinate appleCoordinate;

	bool found = false;
	while (!found)
	{
		srand(time(NULL));
		appleCoordinate.x = rand() % (table.getWidth() - 2) + 1;
		appleCoordinate.y = rand() % (table.getHeight() - 2) + 1;
		found = true;
		for (list<SnakePart>::const_iterator it = snake.getParts().begin(); it != snake.getParts().end(); ++it)
		{
			if (appleCoordinate.x == it->place.x && appleCoordinate.y == it->place.y)
			{
				found = false;
			}
		}
	}

	table.setApplePlace(appleCoordinate);
}

void GameField::renderTable()
{
	// draw rectangle only once
	if (borderRendered) {
		return;
	}

	for (int x = 1; x < table.getWidth() - 1; x++) {
		writeToPosition(x, 0, char(205));
		writeToPosition(x, table.getHeight() - 1, char(205));
	}

	for (int y = 1; y < table.getHeight() - 1; y++) {
		writeToPosition(0, y, char(186));
		writeToPosition(table.getWidth() - 1, y, char(186));
	}

	writeToPosition(0, 0, char(201));
	writeToPosition(table.getWidth() - 1, 0, char(187));
	writeToPosition(0, table.getHeight() - 1, char(200));
	writeToPosition(table.getWidth() - 1, table.getHeight() - 1, char(188));
	
	borderRendered = true;
}

void GameField::renderPoints()
{
	setCursorPosition(1, 0);
	cout << '[' << points << ']';
}

void GameField::renderSnake()
{
	if (!movementRendered) {
		writeToPosition(snakeOldTail.x, snakeOldTail.y, ' ');
		movementRendered = true;
	}

	setConsoleColour(10);
	for (list<SnakePart>::const_iterator it = snake.getParts().begin(); it != snake.getParts().end(); it++) {
		writeToPosition(it->place.x, it->place.y, char(178));
	}

	setConsoleColour(14);
	writeToPosition(snake.getParts().front().place.x, snake.getParts().front().place.y, char(219));
	
	setConsoleColour(7);
}

void GameField::renderApple()
{
	writeToPosition(table.getApplePlace().x, table.getApplePlace().y, 'x');
}

void GameField::renderGameOver()
{
	setConsoleColour(124);
	
	setCursorPosition(max(0, (table.getWidth() - 12) / 2), table.getHeight() / 2);
	cout << " Game Over! ";

	setConsoleColour(7);
}

void GameField::writeToPosition(int x, int y, char c)
{
	setCursorPosition(x, y);
	cout << c;
}

void GameField::setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void GameField::setConsoleColour(unsigned short colour)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();
	SetConsoleTextAttribute(hOut, colour);
}
