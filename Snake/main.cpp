// Snake.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "GameField.h"

int _tmain(int argc, _TCHAR* argv[])
{
	GameField gameField = GameField(20, 20);
	
	while (gameField.isAlive()) 
	{
		gameField.processInput();
		gameField.update();
		gameField.render();

		Sleep(100);
	}

	std::cin.get();
	return 0;
}
