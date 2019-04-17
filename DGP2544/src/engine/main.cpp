#include <iostream>
#include <SDL.h>

#include "logger.h"
#include "gameWindow.h"
#include "../game.h"
#include "fileChecker.h"

int main(int argc, char* args[]) {

	std::cout << "Initialising logger\n" << std::endl;

	Logger* log = new Logger();

	fileChecker(*log);

	GameWindow* wnd = new GameWindow(*log);
	Game* game = new Game(*wnd, *log);

	std::cout << "\nRunning game loop" << std::endl;

	//Game loop
	while (wnd->getGameLoop()) {

		// ** Direct flow between game and window here ** //

		wnd->frameStart = SDL_GetTicks();

		game->gameFlow();
		game->FPScounter();

		wnd->eventHandler();
		wnd->fpsCounter();
		wnd->update();

	}

	delete game;
	game = NULL;

	delete wnd;
	wnd = NULL;

	delete log;
	log = NULL;

	std::cout << "\n\nDone! Press ENTER to exit" << std::endl;
	std::cin.get();

	return 0;

}