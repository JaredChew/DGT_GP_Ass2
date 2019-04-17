#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

#include "engine/logger.h"
#include "engine/gameWindow.h"
#include "engine/keyboard.h"
#include "engine/mouse.h"
#include "engine/resourceLoader.h"
#include "engine/font.h"
#include "engine/audio.h"
#include "engine/physics.h"

#include "gameObject/player.h"

//#include "stages/testStage.h"
#include "stages/stage1.h"
#include "stages/stage2.h"
#include "stages/stage3.h"

#include "menu/mainMenu.h"

#define TOTAL_FILES 20

//For currentStage
#define TEST_STAGE -1
#define MAIN_MENU 0
#define STAGE_1 1
#define STAGE_2 2
#define STAGE_3 3
#define BOSS_STAGE 4

//For stageStatus
#define NEXT_STAGE 1
#define CONTINUE_STAGE 0
#define RETURN_MAIN_MENU -1
#define QUIT_GAME -2

class Game{

	public:

		Logger& log;
		GameWindow& wnd;
		Keyboard* kbd;
		Mouse* mse;
		ResourceLoader* rseLoad;
		Audio* audio;
		Physics* physics;

	private:

		Font* font;

		Player* player;

		//TestStage* testStage;
		Stage_1* stage1;
		Stage_2* stage2;
		Stage_3* stage3;

		MainMenu* mainMenu;

		int currentStage;
		int stageStatus;

		float avgFPS;
		int countedFrames;
		std::stringstream fpsText;

	public:

		Game(GameWindow& wnd, Logger& log);
		~Game();

		//void clean();
		void gameFlow();
		void FPScounter();

		int randAboveNum(int startNum);
		int randAboveNum(int startNum, int notMore);

private:
	void stageController();
	void stageManager();
	void stageInitialiser();
	void stageDestroyer();

};
