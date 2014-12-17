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
	font = TTF_OpenFont("FreeSans.ttf", 36);
	if(font == nullptr)
	{
		cerr << "OpenFont error" << endl;
	}
    textColor = { 255, 255, 255, 0 };

	SDL_Surface* temp = IMG_Load("textures/start_button.png");
	textures["button1"] = SDL_CreateTextureFromSurface(renderer, temp);
	SDL_FreeSurface(temp);

	buttons["done"] = new Button(500, 600, 187, 85, textures["button1"]);
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
	int x{440};
	int y{110};
	int place{1};

	load_temporary_texture("HIGHSCORE", x + 35, y - 70 );
	for(pair<string, string>& p : scores)
		{
			load_temporary_texture(to_string(place) + ".", x, y);
			load_temporary_texture(p.first, x+70, y);
			load_temporary_texture(p.second, x + 200, y);
			y += 50;
			++place;
		}
	draw_buttons();
}

void Highscore_Menu::draw_buttons()
{
	for (map<string, Button*>::iterator i = buttons.begin();
						i != buttons.end(); ++i)
	{
		i->second->render_copy(renderer);
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
			gamestate = "exit";
		}
		else if(event.type == SDL_MOUSEBUTTONDOWN &&
				buttons["done"]->in_button_area(event.motion.x, event.motion.y))
		{
			running = false;
		}
	}
}

void Highscore_Menu::read_from_file()
{
	ifstream file{highscore_file.c_str()};
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
	      cerr << "Error: high score read from bad or empty file" << endl;
	    }
	    else
	    {
	    	scores.push_back(make_pair(name, score));
	    }
	}
	file.close();
}

void Highscore_Menu::overwrite_file()
{
	sort(scores.begin(), scores.end(),
			[](pair<string, string> current, pair<string, string> next )
			{
				return current.second > next.second;
			});
	if (scores.size() > 9)
	{
	    scores.pop_back();
	}

	ofstream out_file{highscore_file.c_str()};
	for(pair<string,string> p : scores)
	{
		out_file << p.first << " " << p.second << endl;
	}
	out_file.close();
	scores.clear();
}


void Highscore_Menu::add_score(int time, double accuracy)
{
	string first_letter{"a"};
	string second_letter{"a"};
	string third_letter{"a"};
	string fourth_letter{"a"};
	string fifth_letter{"a"};

	int current_char{0};
	bool done{false};

	std::string score = to_string(int(time * 10 * accuracy));

	SDL_Event event;
	while(!done)
	{
		char keypress;
		while( SDL_PollEvent( &event ) != 0)
		{
			if(event.type == SDL_QUIT)
			{
				return;
			}
			else if(event.type == SDL_MOUSEBUTTONDOWN &&
					buttons["done"]->in_button_area(event.motion.x, event.motion.y))
			{
				done = true;
			}

			else if(event.type == SDL_KEYDOWN)
			{
				SDL_RenderClear(renderer);

				keypress = (char)event.key.keysym.sym;
				if(isdigit(keypress) || isalpha(keypress))
				{
					++current_char;
					switch(current_char)
					{
						case 1 :
							first_letter = keypress;
							break;
						case 2 :
							second_letter = keypress;
							break;
						case 3 :
							third_letter = keypress;
							break;
						case 4 :
							fourth_letter = keypress;
							break;
						case 5 :
							fifth_letter = keypress;
							current_char = 0;
							break;
					}
				}
			}
		}
		draw_buttons();

		load_temporary_texture("_", 490 + (40 * current_char), 300);
		load_temporary_texture(first_letter, 490, 300);
		load_temporary_texture(second_letter, 530, 300);
		load_temporary_texture(third_letter, 570, 300);
		load_temporary_texture(fourth_letter, 610, 300);
		load_temporary_texture(fifth_letter, 650, 300);

		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}

	read_from_file();
	string name{first_letter +
				second_letter +
				third_letter +
				fourth_letter +
				fifth_letter};
	scores.push_back(make_pair(name, score));
	overwrite_file();
}


string Highscore_Menu::run()
{
	running = true;
	gamestate = "menu";

	read_from_file();

	while (running)
	{

		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		draw_score_list();
		handle_inputs();

		//show the newly drawn things
		SDL_RenderPresent(renderer);

		SDL_Delay(100);
	}
	scores.clear();

	return gamestate;
}

