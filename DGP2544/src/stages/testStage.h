#pragma once

#include <iostream>
#include <ctime>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../engine/gameWindow.h"
#include "../engine/resourceLoader.h"
#include "../engine/physics.h"
#include "../engine/graphics.h"

#include "../gameObject/enemyTemplate.h"
#include "../gameObject/player.h"

#include "../menu/subMenu.h"

#define MAX_TEST_ENEMY 10

class TestStage {

	private:

		GameWindow& wnd;
		ResourceLoader& rseLoad;
		Audio& audio;
		Physics& physics;
		Keyboard& kbd;

		Player& player;

	private:

		SubMenu* subMenu;

		Mix_Music* bgm;

		Enemy* testEnemy[MAX_TEST_ENEMY];
		bool moveLeft;
		bool moveRight;

		int enemyDead;
		bool stageClear;
		bool gamePaused;
		bool stageOpening;
		bool stageEnding;

		struct Background {

			SDL_Texture* bgImg;
			SDL_Rect bgRect;

			int bgWidth = 640;
			int bgHeight = 1920;

			//The background scrolling offset
			int scrollingOffset = 0;

			void scroll(GameWindow& wnd);
			void render(int x, int y, GameWindow& wnd);
			void clean();

		};

		Background background;

	public:

		TestStage(GameWindow& wnd, ResourceLoader& rseLoad, Player& player, Audio& audio, Physics& physics, Keyboard& kbd);
		~TestStage();

		//void clean();
		int flow();

		bool getStageClear();

	private:

		void update();
		void enemyAI();
		void collisionDetection();

};