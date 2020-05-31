#pragma once

#include <array>
#include <vector>

#include "IDrawable.h"

#define HEIGHT 20
#define WIDTH 10

//struct Range
//{
//	int start, end;
//};

class Map : public IDrawable<WIDTH, HEIGHT>
{
public:
	std::array<char, HEIGHT*WIDTH> map {
		//0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
		//1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		//1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		//1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
		//1, 1, 1, 1, 1, 1, 1, 1, 1, 0
	};

	//void drawMap();
	void handleLineClear();

	bool hasLost() { return lost; }
	void doLose() { lost = true; }

	std::tuple<int, int> getOffset() { return std::make_tuple(0, 0); }
	std::array<char, HEIGHT*WIDTH> getPixels() { return map; }
	bool removeBackground() { return true; }
	std::vector<wchar_t> getCharMap() { return charMap; }

private:
	void shiftIndexDown(int index);
	bool lost = false;

	const std::vector<wchar_t> charMap = {
		L'\u2591',
		L'\u2588'
	};

};
