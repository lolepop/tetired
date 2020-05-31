#pragma once

#include "IDrawable.h"
#include "curses.h"

namespace Graphics
{
	void scaledPrint(int y, int x, wchar_t c, int scale)
	{
		for (int ys = 0; ys < scale; ys++)
		{
			for (int xs = 0; xs < scale * 2; xs++)
			{
				mvaddwstr(y * scale + ys, x * scale * 2 + xs, (const wchar_t*)&c);
			}
		}
	}

	template<int w, int h>
	void draw(IDrawable<w, h>& obj)
	{
		auto charMap = obj.getCharMap();
		auto [x, y] = obj.getOffset();
		auto pixels = obj.getPixels();
		bool shouldRemoveBackground = obj.removeBackground();

		for (int yLoc = 0; yLoc < h; yLoc++)
		{
			for (int xLoc = 0; xLoc < w; xLoc++)
			{
				auto px = pixels[yLoc * w + xLoc];
				if (px != 0)
					scaledPrint(y + yLoc, x + xLoc, charMap[px], 2);
					//mvprintw(y + yLoc, x + xLoc, "%c", charMap[px]);
				else if (shouldRemoveBackground)
					scaledPrint(y + yLoc, x + xLoc, charMap[px], 2);
					//mvprintw(y + yLoc, x + xLoc, "%c", charMap[px]);
			}
		}
	}

}
