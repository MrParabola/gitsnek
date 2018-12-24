#pragma once

#include "Board.h"


class Snek
{

private:

	class Segment
	{
	public:
		void MoveBy(const Location& delta_loc);
		void InitHead(const Location& in_loc);
		void InitBody(Snek& snek);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;

		const Location& GetLocation() const;

	private:
		Location loc;
		Color c;
	};

public:
	Snek(const Location& in_loc);

	void MoveBy(const Location& delta_loc);
	void Draw(Board& brd) const;
	void Grow(Snek& snek);
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;

	Location GetNextHeadLocation(const Location& delta_loc) const;

private:

	static constexpr Color headColor = Colors::MakeRGB(255,255,0);
	static constexpr Color bodyColor0 = Colors::MakeRGB(0,255,0);
	static constexpr Color bodyColor1 = Colors::MakeRGB(0,205,0);
	static constexpr Color bodyColor2 = Colors::MakeRGB(0,155,0);
	static constexpr Color bodyColor3 = Colors::MakeRGB(0,105,0);

	int currentColor = 0;
	bool colorNumberUp = false;

	static constexpr int maxColor = 4;

	static constexpr int maxSegments = 255;
	Segment segments[maxSegments];

	int size = 1;

};