#include "Blocks.h"
#include "curses.h"
#include <cstring>

Block::Block(Map* map)
{
	this->map = map;
}

Block* Block::getBlock(Map* map, TETRIMINO type)
{
	Block* block = new Block(map);

	std::array<char, 16> tmp{};

	switch (type)
	{
	case TETRIMINO::I:
		tmp = BlockConst.I;
		block->size = 4;
		break;
	case TETRIMINO::J:
		tmp = BlockConst.J;
		block->size = 3;
		break;
	case TETRIMINO::L:
		tmp = Matrix::hFlip<4>(BlockConst.J, 3);
		block->size = 3;
		break;
	case TETRIMINO::O:
		tmp = BlockConst.O;
		block->size = 2;
		block->canRotate = false;
		break;
	case TETRIMINO::S:
		tmp = BlockConst.S;
		block->size = 3;
		break;
	case TETRIMINO::Z:
		tmp = Matrix::hFlip<4>(BlockConst.S, 3);
		block->size = 3;
		break;
	case TETRIMINO::T:
		tmp = BlockConst.T;
		block->size = 3;
		break;
	default:
		break;
	}

	block->block = tmp;

	return block;
}

Block* Block::getRandomBlock(Map* map, std::mt19937* gen)
{
	int r = std::uniform_int_distribution<int>{0, 6}(*gen);
	return Block::getBlock(map, static_cast<TETRIMINO>(r));
}

void Block::rotateBlock(bool clockwise)
{
	// do check on map if any blocks intersect + wall check
	auto orig = block;
	block = Matrix::rotate<BLOCKMATRIX>(block, size, clockwise);
	if (blockMapIntersect())
		block = orig;
}

bool Block::step()
{
	if (blockMapIntersect(0, 1))
		return false;
	y += 1;
	return true;
}

bool Block::blockMapIntersect(int xOff, int yOff)
{
	for (int yLoc = 0; yLoc < size; yLoc++)
	{
		for (int xLoc = 0; xLoc < size; xLoc++)
		{
			if (block[yLoc * BLOCKMATRIX + xLoc] != 0)
			{
				// TODO: check if outside of map
				if (x + xLoc + xOff < 0 || x + xLoc + xOff > WIDTH - 1 || y + yLoc + yOff > HEIGHT - 1)
					return true;
				if (map->map[(y + yLoc + yOff) * WIDTH + x + xLoc + xOff] != 0)
					return true;
			}
		}
	}
	return false;
}

void Block::drawBlock()
{
	for (int yLoc = 0; yLoc < size; yLoc++)
	{
		for (int xLoc = 0; xLoc < size; xLoc++)
		{
			if (block[yLoc * BLOCKMATRIX + xLoc] != 0)
				mvprintw(y + yLoc, x + xLoc, "O");
		}
	}
}

void Block::placeBlock()
{
	for (int yLoc = 0; yLoc < size; yLoc++)
	{
		for (int xLoc = 0; xLoc < size; xLoc++)
		{
			if (block[yLoc * BLOCKMATRIX + xLoc] != 0)
				map->map[(y + yLoc) * WIDTH + x + xLoc] = 1;
		}
	}
}

bool Block::tryMove(int x, int y)
{
	if (!blockMapIntersect(x, y))
	{
		this->x += x;
		this->y += y;
		return true;
	}
	return false;
}

