#include <iostream>
#include <Windows.h>
#include <chrono>
#include "curses.h"
#include "Blocks.h"
#include "Map.h"

using namespace std::chrono;

std::mt19937 engine;

Map* map;
Block* currBlock;

void update();
void draw(int delta);

//int timeNow();

time_point<high_resolution_clock> lastTime = high_resolution_clock::now();
double blockTimer = 0;

time_point<high_resolution_clock> timeNow()
{
	return high_resolution_clock::now();
	//duration<double> a = high_resolution_clock::now().time_since_epoch();
}

int main()
{
	map = new Map();
	
	engine = std::mt19937(std::random_device()());

	currBlock = Block::getRandomBlock(map, &engine);
	//currBlock = Block::getBlock(map, TETRIMINO::I);
	//currBlock->printBlockMatrix();
	//printf("\n");
	//currBlock->rotateBlock(false);
	//currBlock->printBlockMatrix();
	//printf("\n");
	//currBlock->rotateBlock(true);
	//currBlock->printBlockMatrix();
	
	//Sleep(10000);
	//Block* block1 = Block::getBlock(TETRIMINO::Z);
	//block1->printBlockMatrix();

	char title[50];

	initscr();
	raw();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);

	// game loop
	while (true)
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
		//Sleep(500);
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
	default:
		break;
	}
}

void update()
{
	control(getch());
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
	map->drawMap();
	currBlock->drawBlock();
	//mvprintw(5, 40, "%i fps, %i, %i", delta, currBlock->x, currBlock->y);
}
