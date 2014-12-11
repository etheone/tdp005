/*
 * AbstractGamestate.cpp
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#include "AbstractGamestate.h"

using namespace std;

Abstract_Gamestate::Abstract_Gamestate(SDL_Renderer*& renderer,
									   string gamestate)
	: renderer{renderer}, gamestate{gamestate}
{
}

Abstract_Gamestate::~Abstract_Gamestate()
{
}

string Abstract_Gamestate::get_state() const
{
	return gamestate;
}

void Abstract_Gamestate::set_gamestate(string str)
{
	gamestate = str;
}

