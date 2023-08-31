#pragma once
#include <mutex>

class ProgressBar {

public:
	ProgressBar(int width_, int x, int y);

	void Start();

private:
	int width;
	int posX;
	int posY;

};