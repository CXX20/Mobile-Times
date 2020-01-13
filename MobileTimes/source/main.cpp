/*
prefixes:
	s = static;
	p = pointer;
	n = number (total);
	m = member (private only);
	i = index || iterator || number (ordinal);
	d = demanded || desired;
	c = constant;

ids:
	usual ones must be positive (or zero if ut::glb::scFirstId == 0);
	negative ones stand for a special meaning
		explained in ut::NegativeId in globals.h;

positions:
	in tiles except ut::Render and ut::Sprite, where in pixels
		(and ut::Button by now, probably needs to be changed);
	memorized in size_t (as iTile);
	// TODO ? rename position --> iTileXY;

unsafe:
	ut::Terrain::mTiles::activeSquadId synchro with
		ut::Scenario::mIdToSquad::mPosiiton;
*/

#include <iostream> // DEBUG;
#include "Game.h"

void update_game(ut::Game& game)
{
	while (game.is_polling_event())
	{
		game.handle_event();
	}
	game.draw_self();
}

int main()
{
	ut::Game game;

	while (game.is_opened())
	{
		update_game(game);
	}

	return 0;
}