#include <iostream>
#include "PlayState.h"
#include "GameScreen.h"
#include "Menu.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Creates a window and destroys the window when main is done.
	Game_Screen g(SCREEN_WIDTH, SCREEN_HEIGHT);

	// CLASS INIT
	Menu menu(g.get_renderer());
	Play_State game(g.get_renderer());
	string state{"menu"};

	// MAIN LOOP
	while(state == "menu")
	{
		state = menu.run();
		if (state == "play_state")
		{
			state = game.run();
		}

		cout << state << endl;
	}


	return 0;
}
