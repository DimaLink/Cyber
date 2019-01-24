#include <iostream>
#include <clocale>
#include <ctime>
#include "Windows.h"
#include "Game.h"

int main()
{
	system("chcp 1251 > nul");
	std::setlocale(LC_ALL, "Russian");


	srand(time(NULL));

	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);

	Game game;
	//game.function_06();
	//game.function_02();
	//game.function_07();
	game.runGameplay();

	system("pause");
	return 0;
}