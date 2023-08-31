#pragma once
#include <windows.h>


class consoleParameter
{
public:
	static void setPosition(int x, int y)
	{
		COORD point;
		point.X = x;
		point.Y = y;
		SetConsoleCursorPosition(hStdOut, point);
	}

private:
	static HANDLE hStdOut;
};

