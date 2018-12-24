/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 2,2 }),
	goal(rng, brd, snek)
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (gameStarted)
	{
		if (!gameOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				Location cl = { 0, 1 };
				if (!(delta_loc == cl))
				{
					delta_loc = { 0, -1 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				Location cl = { 0, -1 };
				if (!(delta_loc == cl))
				{
					delta_loc = { 0, 1 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				Location cl = { 1, 0 };
				if (!(delta_loc == cl))
				{
					delta_loc = { -1, 0 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				Location cl = { -1, 0 };
				if (!(delta_loc == cl))
				{
					delta_loc = { 1, 0 };
				}
			}

			if (wnd.kbd.KeyIsPressed('X')) // Extreme Difficulty
			{
				snekMovePeriod = 1;
			}
			else if (wnd.kbd.KeyIsPressed('H')) // Hard Difficulty
			{
				snekMovePeriod = 2;
			}
			else if (wnd.kbd.KeyIsPressed('N')) // Normal Difficulty
			{
				snekMovePeriod = 5;
			}
			else if (wnd.kbd.KeyIsPressed('E')) // Easy Difficulty
			{
				snekMovePeriod = 10;
			}
			else if (wnd.kbd.KeyIsPressed('S')) // I'm Afraid Of Snakes Difficulty
			{
				snekMovePeriod = 20;
			}

			snekMoveCounter++;
		}


		if (snekMoveCounter >= snekMovePeriod)
		{
			snekMoveCounter = 0;

			const Location next = snek.GetNextHeadLocation(delta_loc);

			if (!brd.IsInsideBoard(next) ||
				snek.IsInTileExceptEnd(next))
			{
				gameOver = true;
			}
			else
			{
				const bool eating = (next == goal.GetLocation());

				if (eating)
				{
					snek.Grow(snek);
				}

				snek.MoveBy(delta_loc);

				if (eating)
				{
					goal.Respawn(rng, brd, snek);
				}
			}

		}
	}
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameStarted = true;
		}
	}


}

void Game::ComposeFrame()
{
	if (gameStarted)
	{
		snek.Draw(brd);
		goal.Draw(brd);
		brd.DrawBorder();
	}
	else
	{
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
}
