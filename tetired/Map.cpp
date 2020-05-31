#include "Map.h"
#include "curses.h"

void Map::handleLineClear()
{
	// tpp lazy to optimise
	std::vector<int> yClear;

	for (int y = HEIGHT - 1; y >= 0; y--)
	{
		bool flag = false;
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y * WIDTH + x] == 0)
			{
				flag = true;
				// put shiftindexdown in here with offset instead
				break;
			}
		}

		if (!flag)
			yClear.push_back(y);
	}
	
	for (size_t i = 0; i < yClear.size(); i++)
	{
		for (int y = yClear[i] - 1; y >= 0; y--)
			shiftIndexDown(y + i);
	}

}

void Map::shiftIndexDown(int index)
{
	for (int x = 0; x < WIDTH; x++)
		map[(index + 1) * WIDTH + x] = map[index * WIDTH + x];
}
