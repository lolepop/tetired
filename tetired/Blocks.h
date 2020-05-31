#pragma once

#include <iostream>
#include <array>
#include <tuple>
#include <random>

#include "Matrix.h"
#include "Map.h"
#include "IDrawable.h"

#define BLOCKMATRIX 4

enum class TETRIMINO
{
	I,
	J,
	L,
	O,
	S,
	T,
	Z
};

class Block : public IDrawable<BLOCKMATRIX, BLOCKMATRIX>
{
public:

	std::array<char, BLOCKMATRIX * BLOCKMATRIX> block;
	int size;
	bool canRotate = true;
	int x, y = 0;
	
	static Block* getBlock(Map* map, TETRIMINO type);
	static Block* getRandomBlock(Map* map, std::mt19937* gen);
	void rotateBlock(bool clockwise);
	bool step();
	bool blockMapIntersect(int xOff=0, int yOff=0);
	void placeBlock();
	bool tryMove(int x, int y);

	void printBlockMatrix()
	{
		for (int i = 0; i < BLOCKMATRIX; i++)
		{
			for (int v = 0; v < BLOCKMATRIX; v++)
			{
				printf("%i", block[i * BLOCKMATRIX + v]);
			}
			printf("\n");
		}
	}

	Block(Map* map);

	std::tuple<int, int> getOffset() { return std::make_tuple(x, y); }
	std::array<char, BLOCKMATRIX*BLOCKMATRIX> getPixels() { return block; }
	bool removeBackground() { return false; }
	std::vector<wchar_t> getCharMap() { return charMap; }

private:
	Map* map;

	const std::vector<wchar_t> charMap = {
		L' ',
		L'\u2593'
	};

};

struct
{
	std::array<char, 16> I = {
		0, 0, 0, 0,
		1, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	std::array<char, 16> J = {
		1, 0, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	std::array<char, 16> O = {
		1, 1, 0, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	std::array<char, 16> S = {
		0, 1, 1, 0,
		1, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

	std::array<char, 16> T = {
		0, 1, 0, 0,
		1, 1, 1, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
	};

} BlockConst;
