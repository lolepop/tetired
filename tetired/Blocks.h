#pragma once

#include <iostream>
#include <array>
#include <tuple>
#include <random>
#include <functional>

#include "Matrix.h"
#include "Map.h"

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

class Block
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
	//bool bottomHit();
	void drawBlock();
	void placeBlock();
	bool tryMove(int x, int y);

	std::tuple<int, int> getPos()
	{
		return std::make_tuple(x, y);
	}

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

private:
	Map* map;

	// // mersenne_twister
	//std::uniform_int_distribution<int> idist(0, 100); // [0,100]
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
