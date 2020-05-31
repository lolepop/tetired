#include "Map.h"
#include "curses.h"

//i forgot to compile pdcurses with the unicode flag and im too lazy to recompile so i cant use wide characters lol

void Map::drawMap()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y * WIDTH + x] != 0)
				mvprintw(y, x, "@");
			else
				mvprintw(y, x, " ");
		}
		printw("\n");
	}
}

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


	//std::vector<Range> yClear;

	//for (int y = HEIGHT - 1; y >= 0; y--)
	//{
	//	bool flag = false;
	//	for (int x = 0; x < WIDTH; x++)
	//	{
	//		if (map[y * WIDTH + x] == 0)
	//		{
	//			flag = true;
	//			break;
	//		}
	//	}

	//	if (!flag)
	//	{
	//		if (yClear.size() > 0)
	//		{
	//			if (yClear.back().end == y + 1)
	//				yClear.back().end = y;
	//			else
	//				yClear.push_back({ y, y });
	//		}
	//		else
	//		{
	//			yClear.push_back({ y, y });
	//		}
	//	}
	//}

	////mvprintw(21, 30, "%i %i, %i", yClear.size(), yClear[1].start, yClear[1].end);

	//int a = 0;
	//int i = 0;
	//int offset = 0;
	//for (auto &row: yClear)
	//{
	//	//for (int i = 0; i < yClear.size(); i++)
	//	mvprintw(20 + i, 30, "%i, %i %i", row.start, row.end, (yClear.size() >= i + 2 ? yClear[i + 1].end : 0));

	//	for (int y = 0; row.end - y - offset - 1 > (yClear.size() >= i + 2 ? yClear[i + 1].end : 0); y++)
	//	{
	//		for (int x = 0; x < WIDTH; x++)
	//		{
	//			mvprintw(row.start - y - offset, x, "%i", a);
	//			mvprintw(row.end - y - offset - 1, x, "%i", a);
	//			refresh();
	//			map[(row.start - y - offset) * WIDTH + x] = map[(row.end - y - 1 - offset) * WIDTH + x];
	//			map[(row.end - y - 1 - offset) * WIDTH + x] = 0;
	//		}
	//		a += 1;
	//	}
	//	offset += (row.start - row.end) + 1;
	//	i++;
	//	//break;
	//}

}

void Map::shiftIndexDown(int index)
{
	for (int x = 0; x < WIDTH; x++)
		map[(index + 1) * WIDTH + x] = map[index * WIDTH + x];
}
