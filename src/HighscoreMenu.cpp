/*
 * HighscoreMenu.cpp
 *
 *  Created on: 15 dec 2014
 *      Author: joagy323
 */

#include "HighscoreMenu.h"

using namespace std;

Highscore_Menu::Highscore_Menu(SDL_Renderer*& renderer, string file)
:Abstract_Gamestate(renderer, "Highscore"),  highscore_file{file}, temp_score{nullptr}

{
	font = TTF_OpenFont("FreeSans.ttf", 20);
	if(font == nullptr)
	{
		cerr << "OpenFont error" << endl;
	}
    textColor = { 255, 255, 255, 0 };

//	SDL_Surface* temp = IMG_Load("textures/start_button.png");
//	textures["button1"] = SDL_CreateTextureFromSurface(renderer, temp);
//	SDL_FreeSurface(temp);
//
//	temp = IMG_Load("textures/highscore_button.png");
//	textures["button2"] = SDL_CreateTextureFromSurface(renderer, temp);
//	SDL_FreeSurface(temp);
//
//	temp = IMG_Load("textures/quit_button.png");
//	textures["button3"] = SDL_CreateTextureFromSurface(renderer, temp);
//	SDL_FreeSurface(temp);
//
//	buttons["start_game"] = new Button(500, 190, 187, 85, textures["button1"]);
//	buttons["highscore_button"] = new Button(420, 320, 355, 166, textures["button2"]);
//	buttons["quit_game"] = new Button(500, 520, 174, 100, textures["button3"]);
}

Highscore_Menu::~Highscore_Menu()
{
	//delete buttons;
	for (map<string, Button*>::iterator i = buttons.begin();
				i != buttons.end(); ++i)
		{
			delete i->second;
			i->second = nullptr;
		}

	for (map<string, SDL_Texture*>::iterator i = textures.begin();
				i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
	}

	 // Close the font that was used
	TTF_CloseFont( font );
}

void Highscore_Menu::load_temporary_texture(string message, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, message.c_str(), textColor);
	temp_score = SDL_CreateTextureFromSurface(renderer, textSurface);
	int text_width = textSurface->w;
	int text_height = textSurface->h;
	SDL_FreeSurface(textSurface);
	renderQuad = { x,  y, text_width, text_height};

	SDL_RenderCopy(renderer, temp_score, nullptr, &renderQuad);
	SDL_DestroyTexture(temp_score);
	temp_score = nullptr;
}

void Highscore_Menu::draw_score_list()
{
	int x{200};
	int y{200};

	for(pair<string, string>& p : scores)
		{
			load_temporary_texture(p.first, x, y);
			load_temporary_texture(p.second, x + 200, y);
			y += 100;
		}
}

void Highscore_Menu::handle_inputs()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}
}

void Highscore_Menu::read_from_file()
{
	ifstream file(highscore_file.c_str());
	string line{""};
	string name;
	string score;

	while (getline(file, line))
	{
		istringstream iss(line);
		iss >> name >> score;

	    if(iss.fail())
	    {
	      iss.clear();
	      iss.ignore(4711, '\n');
	      cerr << "Error: high score read from bad file" << endl;
	      exit(1);
	    }

		scores.push_back(make_pair(name, score));

	}
	file.close();
}

void Highscore_Menu::add_score(int time, double accuracy)
{
	string score = to_string(time * 10 * accuracy);
	scores.push_back(make_pair("joagy", score));
	cout << "NU" << endl;
}


string Highscore_Menu::run()
{
	running = true;
	gamestate = "menu";

	const Uint32 targetFrameDelay = 10;
	Uint32 startTime = SDL_GetTicks();
	Uint32 lastFrameTime = startTime;
	read_from_file();

	while (running)
	{
		Uint32 frameDelay = SDL_GetTicks() - lastFrameTime;
		lastFrameTime += frameDelay;

		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		draw_score_list();
		handle_inputs();

		//show the newly drawn things
		SDL_RenderPresent(renderer);

		// wait before drawing the next frame
		frameDelay = SDL_GetTicks() - lastFrameTime;
		if (targetFrameDelay > frameDelay)
		{
			// only wait if it's actually needed
			Uint32 sleepTime = targetFrameDelay - frameDelay;
			SDL_Delay(sleepTime);
		}
	}
//	scores.clear();

	return gamestate;
}

