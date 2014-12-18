/*
 * AbstractGamestate.cpp
 *
 *  Created on: 5 dec 2014
 *      Author: joagy323
 */

#include "AbstractGamestate.h"

using namespace std;

Abstract_Gamestate::Abstract_Gamestate(SDL_Renderer*& renderer,
									   const string& gamestate)
	: running{true}, renderer{renderer}, gamestate{gamestate}, temp_score{nullptr}
{

	font = TTF_OpenFont("FreeSans.ttf", 36);
	if (font == nullptr)
	{
		cerr << "OpenFont error" << endl;
	}
	text_color = { 255, 255, 255, 0 };
}

Abstract_Gamestate::~Abstract_Gamestate()
{
}

void Abstract_Gamestate::load_temporary_texture(string message, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), text_color);
	temp_score = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	text_rect = { x,  y, text_width, text_height};

	SDL_RenderCopy(renderer, temp_score, nullptr, &text_rect);
	SDL_DestroyTexture(temp_score);
	temp_score = nullptr;
}
