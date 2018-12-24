#include "Snek.h"
#include <assert.h>

Snek::Snek(const Location & in_loc)
{
	segments[0].InitHead( in_loc );
}

void Snek::MoveBy(const Location & delta_loc)
{
	for (int i = size - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);

}

void Snek::Draw(Board & brd) const
{
	for (int i = size-1; i >= 0; i--)
	{
		segments[i].Draw(brd);
	}
}

void Snek::Grow(Snek& snek)
{
	if (size < maxSegments)
	{
		segments[size].InitBody(snek);
		size++;
	}
}

bool Snek::IsInTileExceptEnd(const Location & target) const
{
	for (int i = 0; i < size - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

bool Snek::IsInTile(const Location & target) const
{
	for (int i = 0; i < size; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}

	return false;
}

Location Snek::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments[0].GetLocation());
	l.Add(delta_loc);

	return l;
}

void Snek::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);

	loc.Add(delta_loc);
}

void Snek::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snek::headColor;
}

void Snek::Segment::InitBody(Snek& snek)
{
	if (snek.currentColor == 0)
	{
		c = bodyColor0;
	}
	else if (snek.currentColor == 1)
	{
		c = bodyColor1;
	}
	else if (snek.currentColor == 2)
	{
		c = bodyColor2;
	}
	else if (snek.currentColor == 3)
	{
		c = bodyColor3;
	}
	else
	{
		c = bodyColor1;
	}

	if (snek.colorNumberUp)
	{
		snek.currentColor++;
		if (snek.currentColor >= maxColor - 1)
		{
			snek.colorNumberUp = false;
		}
	}
	else
	{
		snek.currentColor--;
		if (snek.currentColor <= 0)
		{
			snek.colorNumberUp = true;
		}
	}
	
}

void Snek::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snek::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);

}

const Location& Snek::Segment::GetLocation() const
{
	return loc;
}