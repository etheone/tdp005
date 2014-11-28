/*
 * Gameengine.cpp
 *
 *  Created on: 27 nov 2014
 *      Author: joagy323
 */

#include "Gameengine.h"

using namespace std;

Game_Engine::Game_Engine() {

	// TODO Auto-generated constructor stub

}

Game_Engine::~Game_Engine() {
	// TODO Auto-generated destructor stub

}

void Game_Engine::logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* Game_Engine::loadTexture(int& pictureWidth, int& pictureHeight, const char*& file, SDL_Renderer *renderer)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* loadedImage = IMG_Load(file);
	// If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr)
	{

		pictureWidth = loadedImage->w;
		pictureHeight = loadedImage->h;
		texture = SDL_CreateTextureFromSurface(renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
		// Make sure converting went okay too
		if (texture == nullptr)
		{
			logSDLError(cerr, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(cerr, "LoadTexture");
	}
	return texture;
}
