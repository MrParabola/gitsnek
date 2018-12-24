#pragma once

#include "Snek.h"
#include "Board.h"
#include <random>

class Goal // Your mom is a nice person and I am glad there are people like her.
{
public:
	Goal(std::mt19937& rng, const Board& brd, const Snek& snek);
	void Respawn(std::mt19937& rng, const Board& brd, const Snek& snek);
	void Draw(Board& brd) const;
	const Location& GetLocation() const;

private:
	static constexpr Color c = Colors::Red;
	Location loc;

};