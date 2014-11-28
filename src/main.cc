#include <iostream>
#include "Gameengine.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

using namespace std;



int main(int argc, char* argv[])
{

	//class init.
	Game_Engine G;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}
	//create the window
	SDL_Window* window = SDL_CreateWindow("SDL_Test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
														SCREEN_WIDTH,SCREEN_HEIGHT, 0);
	if (window == nullptr)
	{
		G.logSDLError(cerr, "SDL_CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);  // 0 gives ACCELERATED flag?.
			if (renderer == nullptr)
			{
				SDL_DestroyWindow(window);
				G.logSDLError(cerr, "SDL_CreateRenderer");
				SDL_Quit();
				return 1;
			}

	//MAKE THE SCALE RENDERING SMOOTHER
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);


	// load draft with these values
	int draftWidth{0};
	int draftHeight{0};
	int wallHeight{0};
	int wallWidth{0};
	const char* ship_img{"draft.png"};
	const char* wall_img{"wall.png"};
	SDL_Texture* draft = G.loadTexture(draftWidth, draftHeight, ship_img, renderer);
	SDL_Texture* wall = G.loadTexture(wallWidth, wallHeight, wall_img, renderer);
	if (draft == nullptr || wall == nullptr)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}


		// Create a rectangle!
		SDL_Rect draftRect;
		draftRect.w = draftWidth;
		draftRect.h = draftHeight;

		SDL_Rect draftRect2;
		draftRect2.x = -100;
		draftRect2.y = -100;
		draftRect2.w = draftWidth;
		draftRect2.h = draftHeight;

		SDL_Rect wallRect;
		wallRect.x = 0;
		wallRect.y = 0;
		wallRect.w = wallWidth;
		wallRect.h = wallHeight;

	int count{0};
	int angle{0};

	// MAIN LOOP
	bool running{true};
	while (running)
	{
		// update things
		SDL_Event event;
		while (SDL_PollEvent(&event))
			{
			++angle;
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_MOUSEMOTION)
				{
					draftRect.x = event.motion.x - (draftWidth/2);
					draftRect.y = event.motion.y - (draftHeight/2);
				}
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					draftRect2.x += 100;
					draftRect2.y += 100;
				}

			}

		//clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_RenderCopyEx(renderer, draft, nullptr, &draftRect, angle, nullptr, SDL_FLIP_HORIZONTAL); // draftRect gives size.
		SDL_RenderCopy(renderer, draft, nullptr, &draftRect2); // draftRect gives size.
		SDL_RenderCopy(renderer, wall, nullptr, &wallRect);
		//draw things

		//show the newly drawn things
		SDL_RenderPresent(renderer);

		cout << count << endl;
		if(count == 500)
		{
			count = 0;
			running = false;
		}
		++count;

		//wait before drawing the next frame
		SDL_Delay(20);
	}
	SDL_DestroyTexture(draft);
	draft = nullptr;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}
