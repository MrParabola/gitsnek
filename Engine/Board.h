#pragma once
#include "Graphics.h"
#include "Location.h"

class Board
{
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, Color in_c);
	void DrawBorder();
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;

private:
	static constexpr int dimension = 20;
	static constexpr int width = 36;
	static constexpr int height = 26;
	static constexpr int distFromLeft = 40;
	static constexpr int distFromTop = 40;
	static constexpr int borderWidth = 10;
	static constexpr Color c = Colors::MakeRGB(255, 255, 255);
	Graphics& gfx;
};