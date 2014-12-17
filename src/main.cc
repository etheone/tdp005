#include <iostream>
#include "PlayState.h"
#include "GameScreen.h"
#include "Menu.h"
#include "HighscoreMenu.h"



using namespace std;

int main(int argc, char* argv[])
{
	// Creates a window and destroys the window when main is done.
	Game_Screen g(SCREEN_WIDTH, SCREEN_HEIGHT);

	// CLASS INIT
	Menu menu(g.get_renderer());
	Highscore_Menu* highscore = new Highscore_Menu(g.get_renderer(), "Highscores");
	Play_State game(g.get_renderer(), highscore);

	string state{"menu"};

	// MAIN LOOP
	while (state != "exit")
	{
		if (state == "highscore")
		{
			state = highscore->run();
		}
		else if (state == "menu")
		{
			state = menu.run();
		}
		else if (state == "play_state")
		{
			state = game.run();
		}
	}

	delete highscore;
	highscore = nullptr;
	return 0;
}
