#include "Board.h"
#include <assert.h>

Board::Board(Graphics& in_gfx)
	:
	gfx(in_gfx)
{}

void Board::DrawCell(const Location & loc, Color in_c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);


	gfx.DrawRectDim((loc.x * dimension) + distFromLeft + 1, (loc.y * dimension) + distFromTop + 1, dimension - 2, dimension - 2, in_c);

}

void Board::DrawBorder()
{
	for (int x = distFromLeft - borderWidth; x < (distFromLeft + (dimension * width)) + borderWidth; x++)
	{
		for (int y = distFromTop - borderWidth; y < (distFromTop + (dimension * height)) + borderWidth; y++)
		{
			if (!(x > distFromLeft &&
				x < distFromLeft + (dimension * width) &&
				y > distFromTop &&
				y < distFromTop + (dimension * height)))
			{
				gfx.PutPixel(x, y, c);
			}
		}
	}
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y >= 0 && loc.y < height;
}
