#include <iostream>
#include "PlayState.h"
#include "GameScreen.h"


using namespace std;

int main(int argc, char* argv[])
{
	// Creates a window and destroys the window when main is done.
	Game_Screen G(SCREEN_WIDTH, SCREEN_HEIGHT);

	// CLASS INIT
	Play_State Play(G.get_renderer());

	// MAIN LOOP
	Play.play_game();

	return 0;
}
