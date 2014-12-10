/*
 * Level.cpp
 *
 *  Created on: 10 dec 2014
 *      Author: joagy323
 */

#include "Level.h"

using namespace std;

Level::Level(SDL_Renderer*& renderer)
{
	SDL_Surface* temp = IMG_Load("20x20_wall.png");
	textures["wall"] = SDL_CreateTextureFromSurface(renderer,temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("outer_x_wall.png");
	textures["outer_x"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("outer_y_wall.png");
	textures["outer_y"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("draft2.png");
	textures["player"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("player_shot4x4.png");
	textures["shot"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	temp = IMG_Load("coin.png");
	textures["coin"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

}

Level::~Level()
{
	for(map<string, SDL_Texture*>::iterator i = textures.begin();
			i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
	}
}


