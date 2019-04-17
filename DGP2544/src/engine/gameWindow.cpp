#include "gameWindow.h"

GameWindow::GameWindow(Logger& log) : log(log) {

	// ** Initialise variables and objects here ** //

	//Initialise controlling variables
	gameloop = true;
	frameDelay = 1000 / FPS;

	avgFPS = 0;
	countedFrames = 0;

	if (init() == -1) {
		gameloop = false;
	}

}

GameWindow::~GameWindow() {

	// ** Destroy window object here ** //

	std::cout << "\nDestroying SDL renderer" << std::endl;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	std::cout << "Destroying SDL surface" << std::endl;
	SDL_FreeSurface(backbuffer);
	backbuffer = NULL;

	std::cout << "Destroying SDL window" << std::endl;
	SDL_DestroyWindow(window);
	window = NULL;

	std::cout << "Quitting SDL libraries" << std::endl;
	SDL_Quit();

}

int GameWindow::init() {

	// ** Initialise window here ** //

	std::cout << "\nInitialising SDL..." << std::endl;
	log.writeLog("Initialising SDL");

	//Initialise SDL drivers
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Quit();
		std::cerr << "Failed to intialise SDL drivers" << std::endl;
		log.writeLog("Failed to intialise SDL drivers");
		return -1;
	}

	std::cout << "SDL drivers initialised" << std::endl;
	log.writeLog("SDL drivers initialised");

	//Create main window
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL) {
		SDL_Quit();
		std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		log.writeLog("Failed to intialise SDL window");
		return -1;
	}

	//Apply window into backbuffer/surface
	backbuffer = SDL_GetWindowSurface(window);
	std::cout << "SDL window initialised" << std::endl;
	log.writeLog("SDL window initialised");

	//Initialise renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	if (renderer == NULL) {
		SDL_Quit();
		std::cerr << "Failed to intialise SDL renderer" << std::endl;
		log.writeLog("Failed to intialise SDL renderer");
		return -1;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	std::cout << "SDL renderer initialised" << std::endl;
	log.writeLog("SDL renderer initialised");

	return 0;

}

void GameWindow::eventHandler() {

	// ** Set window event listener here ** //

	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) { //Listen to 'X' button of window being clicked
		std::cout << "\nPlayer exited game" << std::endl;
			gameloop = false;
		}

	}

}

void GameWindow::fpsCounter() {

	// ** Displays average fps ** //

	//Count average FPS

	avgFPS = countedFrames / (SDL_GetTicks() / 1000.f);

	if (avgFPS > 2000000) { avgFPS = 0; }

	countedFrames++;

	//Display on window

	sprintf_s(dynamicWindowTitle, "Assignment 1 | FPS: %d", (int)avgFPS); // Dynamic text
	SDL_SetWindowTitle(window, dynamicWindowTitle);

}

void GameWindow::update() {

	// ** Set window updating here ** //

	//Update the window to display changes (texture)
	SDL_RenderPresent(renderer);

	//Update the window to display changes (surface)
	//SDL_UpdateWindowSurface(window);

	//Apply default background colour
	SDL_FillRect(backbuffer, NULL, 0);

	//Manage frame rate
	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}

	SDL_RenderClear(renderer);

}

void GameWindow::forceQuit() {

	std::cerr << "\n\nA critical error has occured, the program will now terminate" << std::endl;
	log.writeLog("A critical error has occured, the program will now terminate");

	std::cout << "Press ENTER to exit" << std::endl;
	std::cin.get();

	SDL_Quit();

	exit(-1);

}

//Returns gameloop variable status
bool GameWindow::getGameLoop() { return gameloop; }

//Set gameloop variable value
void GameWindow::setGameLoop(bool gameLoop) { this->gameloop = gameLoop; }

// ########### ARCHIVE ########### //
/*
void GameWindow::destroy() {

	// ** Destroy window object here ** //

	std::cout << "Destroying SDL renderer" << std::endl;
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	std::cout << "Destroying SDL surface" << std::endl;
	SDL_FreeSurface(backbuffer);
	backbuffer = NULL;

	std::cout << "Destroying SDL window" << std::endl;
	SDL_DestroyWindow(window);
	window = NULL;

	std::cout << "Quitting SDL libraries" << std::endl;
	SDL_Quit();

	std::cout << "\n\nDone! Press ENTER to exit\n" << std::endl;
	std::cin.get();

}
*/