#define PDC_WIDE

#include <iostream>
#include <Windows.h>
#include <chrono>
#include "curses.h"
#include "Blocks.h"
#include "Map.h"
#include "Graphics.h"


using namespace std::chrono;

std::mt19937 engine;

Map* map;
Block* currBlock;

void update();
void draw(int delta);

time_point<high_resolution_clock> lastTime = high_resolution_clock::now();
double blockTimer = 0;

time_point<high_resolution_clock> timeNow()
{
	return high_resolution_clock::now();
}

void init()
{
	map = new Map();
	engine = std::mt19937(std::random_device()());
	currBlock = Block::getRandomBlock(map, &engine);

	HWND wnd = GetConsoleWindow();
	RECT a;
	GetWindowRect(wnd, &a);

	MoveWindow(wnd, a.left, a.top, 800, 800, TRUE);
}

int main()
{
	init();

	setlocale(LC_ALL, "");
	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	char title[50];

	// game loop
	while (!map->hasLost())
	{
		auto now = high_resolution_clock::now();
		
		double delta = duration_cast<duration<double, std::milli>>(now - lastTime).count();
		//mvprintw(5, 40, "%i fps", (int)(1000 / delta));
		sprintf_s(title, "Tetired - %i fps", (int)(1000 / delta));
		SetConsoleTitleA(title);
		
		blockTimer += delta;
		lastTime = now;

		update();
		draw(delta);
		refresh();
	}
	endwin();

	return 0;
}

void control(wchar_t c)
{
	switch (c)
	{
	case KEY_LEFT:
		currBlock->tryMove(-1, 0);
		break;
	case KEY_RIGHT:
		currBlock->tryMove(1, 0);
		break;
	case KEY_UP:
		currBlock->rotateBlock(true);
		break;
	case KEY_DOWN:
		currBlock->rotateBlock(false);
		break;
	default:
		break;
	}
}

void update()
{
	control(getch());
	// lazy
	if (blockTimer >= 300)
	{
		blockTimer -= 300;
		if (!currBlock->step())
		{
			currBlock->placeBlock();
			map->handleLineClear();
			
			delete currBlock; // epic
			currBlock = Block::getRandomBlock(map, &engine);
			//currBlock = Block::getBlock(map, TETRIMINO::I);
		}
	}
}

void draw(int delta)
{
	Graphics::draw(*map);
	Graphics::draw(*currBlock);
}
