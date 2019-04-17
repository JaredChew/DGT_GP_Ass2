#include "game.h"

Game::Game(GameWindow& wnd, Logger& log) : wnd(wnd), log(log) {

	// ** Initialise everything here ** //

	std::cout << "\nInitialising Game object" << std::endl;

	//Initialise essential obbjects
	kbd = new Keyboard();
	std::cout << "Keyboard initialised" << std::endl;

	mse = new Mouse();
	std::cout << "Mouse initialised" << std::endl;

	rseLoad = new ResourceLoader(wnd);
	std::cout << "ResourceLoader initialised" << std::endl;

	audio = new Audio(wnd);
	std::cout << "Audio initialised" << std::endl;

	physics = new Physics();
	std::cout << "Physics initialised" << std::endl;

	font = new Font(wnd);
	font->setFont(rseLoad->loadFont("asset/font/Consolas.ttf", 10));

	//Initialise player
	player = new Player(wnd, *kbd, *mse, *rseLoad, *audio, *physics);
	std::cout << "Player initialised" << std::endl;

	currentStage = MAIN_MENU;
	stageStatus = CONTINUE_STAGE;

	//NULL stages
	//testStage = NULL;
	stage1 = NULL;
	stage2 = NULL;
	stage3 = NULL;

}

Game::~Game() { 

	// ** Destroy all objects' data ** //

	std::cout << "\nDestroying game objects" << std::endl;

	if (stage1 != NULL) {
		std::cout << "\nDeleting TestStage object" << std::endl;
		delete stage1;
		stage1 = NULL;
	}

	if (stage2 != NULL) {
		std::cout << "\nDeleting TestStage object" << std::endl;
		delete stage2;
		stage2 = NULL;
	}

	if (stage3 != NULL) {
		std::cout << "\nDeleting TestStage object" << std::endl;
		delete stage3;
		stage3 = NULL;
	}

	std::cout << "\nDeleting MainMenu object" << std::endl;
	delete mainMenu;
	mainMenu = NULL;

	std::cout << "\nDeleting Player object" << std::endl;
	delete player;
	player = NULL;

	std::cout << "\nDeleting ResourceLoader object" << std::endl;
	delete rseLoad;
	rseLoad = NULL;

	std::cout << "Deleting Physics object" << std::endl;
	delete physics;
	physics = NULL;

	std::cout << "Deleting Audio object" << std::endl;
	delete audio;
	audio = NULL;

	std::cout << "Deleting FPS counter Font object" << std::endl;
	delete font;
	font = NULL;

	std::cout << "\nGame object cleaned" << std::endl;

}

void Game::FPScounter() {

	// ** Displays average fps ** //

	//Count average FPS

	avgFPS = countedFrames / (SDL_GetTicks() / 1000.f);

	if (avgFPS > 2000000) { avgFPS = 0; }

	countedFrames++;

	//Display in-game top left

	fpsText.str("");
	fpsText << "FPS: " << (int)avgFPS;

	font->drawFont(fpsText.str(), 5, 5, 50, 15, 255, 255, 255);

	fpsText.clear();

}

void Game::stageController() {

	//Controls flow of stages
	if (stageStatus == NEXT_STAGE) { //proceeds to next stage
		currentStage++;
	}
	else if (stageStatus == RETURN_MAIN_MENU && currentStage == MAIN_MENU) { //proceeds to testStage
		currentStage = TEST_STAGE;
		stageStatus = CONTINUE_STAGE;
	}
	else if (stageStatus == RETURN_MAIN_MENU) { //return to main menu
		currentStage = MAIN_MENU;
		stageStatus = CONTINUE_STAGE;
	}
	else if (stageStatus == QUIT_GAME) {
		wnd.setGameLoop(false);
	}

}

void Game::stageInitialiser() {

	if (currentStage == MAIN_MENU && mainMenu == NULL) {
		mainMenu = new MainMenu(wnd, *kbd, *rseLoad, *audio);
		std::cout << "\nMain Menu initialised" << std::endl;
		std::cout << "Running Main Menu" << std::endl;
	}
	else if (currentStage == STAGE_1 && stage1 == NULL) {
		stage1 = new Stage_1(wnd, *rseLoad, *player, *audio, *physics, *kbd);
		std::cout << "\nStage 1 initialised" << std::endl;
		std::cout << "Running Stage 1" << std::endl;
	}
	else if (currentStage == STAGE_2 && stage2 == NULL) {
	stage2 = new Stage_2(wnd, *rseLoad, *player, *audio, *physics, *kbd);
	std::cout << "\nStage 2 initialised" << std::endl;
	std::cout << "Running Stage 2" << std::endl;
	}
	else if (currentStage == STAGE_3 && stage3 == NULL) {
	stage3 = new Stage_3(wnd, *rseLoad, *player, *audio, *physics, *kbd);
	std::cout << "\nStage 3 initialised" << std::endl;
	std::cout << "Running Stage 3" << std::endl;
	}
	/*
	else if (currentStage == BOSS_STAGE && bossStage == NULL) {
	//bossStage = new BossStage(wnd, *rseLoad, *player, *audio, *physics);
	std::cout << "\nBoss Stage initialised" << std::endl;
	std::cout << "Running Boss Stage" << std::endl;
	}
	*/
}

void Game::stageManager() {

	if (currentStage == MAIN_MENU) {
		stageStatus = mainMenu->flow();
	}
	else if (currentStage == STAGE_1) {
		stageStatus = stage1->flow();
	}
	else if (currentStage == STAGE_2) {
		stageStatus = stage2->flow();
	}
	else if (currentStage == STAGE_3) {
		stageStatus = stage3->flow();
	}
	else if (currentStage == BOSS_STAGE) {
		//stageStatus = bossStage->flow();
	}

}

void Game::stageDestroyer() {

	//delete stage if initialised || when stage is done, not in use (main menu, etc), next stage
	if (currentStage != MAIN_MENU && mainMenu != NULL) {
		std::cout << "\nDeleting MainMenu object" << std::endl;
		delete mainMenu;
		mainMenu = NULL;
	}
	else if (currentStage != STAGE_1 && stage1 != NULL) {
		std::cout << "\nDeleting Stage1 object" << std::endl;
		delete stage1;
		stage1 = NULL;
	}
	else if (currentStage != STAGE_2 && stage2 != NULL) {
		std::cout << "\nDeleting Stage2 object" << std::endl;
		delete stage2;
		stage2 = NULL;
	}
	else if (currentStage != STAGE_3 && stage3 != NULL) {
		std::cout << "\nDeleting Stage3 object" << std::endl;
		delete stage3;
		stage3 = NULL;
	}
	/*
	else if (currentStage != BOSS_STAGE && bossStage != NULL) {
		std::cout << "\nDeleting BossStage object" << std::endl;
		//delete bossStage;
		//bossStage = NULL;
	}
	*/
}

void Game::gameFlow() {

	// ** Insert game's functions code here ** //
	
	stageController();
	stageDestroyer();
	stageInitialiser();
	stageManager();

}

int Game::randAboveNum(int startNum) {

	int rng = 0;

	do {

		rng = rand();

	} while (rng < startNum);

	return rng;

}

int Game::randAboveNum(int startNum, int notMore) {

	int rng = 0;

	do {

		rng = rand() % notMore;

	} while (rng < startNum);

	return rng;

}

// ########### ARCHIVE ########### //
/*
void Game::clean() {

	// ** Destroy all objects' data ** //

	std::cout << "\n\nDestroying game objects\n" << std::endl;

	rseLoad->clean();
	//delete rseLoad;

	//physics->clean();
	//delete physics;

	audio->clean();
	//delete audio;

	std::cout << "Cleaning level objects" << std::endl;
	testStage->clean();
	//delete testStage;

	std::cout << "Cleaning palyer object" << std::endl;
	player->clean();
	//delete player;

	font->close();
	//delete font;

}
*/