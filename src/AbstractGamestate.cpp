/*
 * AbstractGamestate.cpp
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#include "AbstractGamestate.h"

using namespace std;

Abstract_Gamestate::Abstract_Gamestate(SDL_Renderer*& renderer)
	: renderer{renderer}
{

}

Abstract_Gamestate::~Abstract_Gamestate()
{
}

