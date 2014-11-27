#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <emilen>

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;

using namespace std;


/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren){
	// Initialize to nullptr to avoid dangling pointer issues
	SDL_Texture *texture = nullptr;
	// Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	// If the loading went ok, convert to texture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		// Make sure converting went ok too
		if (texture == nullptr){
			logSDLError(std::cout, "CreateTextureFromSurface");
		}
	}
	else {
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}


int main(int argc, char* argv[])
{
	// initializing SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cerr << "Error initializing SDL" << endl;
		exit(1);
	}

	//create the window
	SDL_Window* window = SDL_CreateWindow("SDL_Test",SDL_WINDOWPOS_UNDEFINED,
													SDL_WINDOWPOS_UNDEFINED,
													SCREEN_WIDTH,SCREEN_HEIGHT,
													0);
	// Standard error-handling and cleanup for creating a window.
	if (window == nullptr)
		{
		cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);  // 0 gives ACCELERATED flag?.

	// Standard error-handling and cleanup for the renderer
	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//MAKE THE SCALE RENDERING SMOOTHER
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	//render at a virtual resolution then stretch to actual resolution
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	// load draft
		SDL_Texture* draft{nullptr};
		int draftWidth{0};
		int draftHeight{0};
		{
			SDL_Surface* temp = IMG_Load("draft.png");
			if (temp == nullptr)
				// Error-handling ... again.
			{
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				cerr << "SDL_LoadBMP Error: " << SDL_GetError() << endl;
				SDL_Quit();
				return 1;
			}

			draft = SDL_CreateTextureFromSurface(renderer, temp);
			// ERROR_HANDLER! EVERYWHERE!!!:O
			if (draft == nullptr)
			{
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				cerr << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << endl;
				SDL_Quit();
				return 1;
			}

			draftWidth = temp->w;
			draftHeight = temp->h;

			SDL_FreeSurface(temp);
		}

		// Create a rectangle!
		SDL_Rect draftRect;

		SDL_Rect draftRect2;
		draftRect2.x = -100;
		draftRect2.y = -100;
		draftRect2.w = draftWidth;
		draftRect2.h = draftHeight;

	int count{0};
	int angle{0};

	//main loop
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
					draftRect.w = draftWidth;
					draftRect.h = draftHeight;
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
