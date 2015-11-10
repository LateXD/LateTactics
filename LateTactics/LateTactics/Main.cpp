#include "Game.h"
#include "Map.h"
#include "MainMenu.h"

int main()
{
	srand(time(NULL));
	Game game;
	game.pushState(new MainMenu(&game));
	game.gameLoop();
	return 0;
}