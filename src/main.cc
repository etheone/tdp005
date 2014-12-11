#include <iostream>
#include "PlayState.h"
#include "GameScreen.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Creates a window and destroys the window when main is done.
	Game_Screen g(SCREEN_WIDTH, SCREEN_HEIGHT);

	// CLASS INIT
	Play_State play(g.get_renderer());

	// MAIN LOOP
	play.run();

	return 0;
}
