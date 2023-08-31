#include <iostream>
#include "consoleParameter.h"
#include "ProgressBar.h"
#include <thread>
#include <Windows.h>

using namespace std::chrono_literals;


ProgressBar::ProgressBar(int width_, int x, int y) : width(width_), posX(x), posY(y) {}

void ProgressBar::Start() {

	const char symbol = '#';
	for (int i = posX; i < width + posX; ++i)
	{
		std::this_thread::sleep_for(200ms);
		consoleParameter::setPosition(i, posY);
		std::cout << symbol;
	}
}
HANDLE consoleParameter::hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);