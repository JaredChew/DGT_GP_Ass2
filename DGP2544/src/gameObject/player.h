#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include <sstream>

#include "../engine/gameWindow.h"
#include "../engine/resourceLoader.h"
#include "../engine/audio.h"
#include "../engine/physics.h"
#include "../engine/animatedSprite.h"
#include "../engine/font.h"
#include "../engine/keyboard.h"
#include "../engine/mouse.h"

#include "bullet.h"
#include "powerUp.h"

#define PLAYER_MAX_BULLET 50
#define PLAYER_SPEED 3

class Player {

	private:

		GameWindow& wnd;
		ResourceLoader& rseLoad;
		Audio& audio;
		Physics& physics;
		Keyboard& kbd;
		Mouse& mse;

	private:

		AnimatedSprite playerSprite;
		Bullet bullet[PLAYER_MAX_BULLET];

		Font* font;

		Mix_Chunk* shipDestroyedSound;
		Mix_Chunk* bulletShootSound;
		Mix_Chunk* bulletHitSound;
		Mix_Chunk* powerUpHitSound;
		Mix_Chunk* shieldSound;

		int flipDelay;
		int flipDelayCount;

		int lives;
		int score;
		int maxLives;
		int shields;
		int maxShields;
		int shootDelay;
		int shieldDuration;
		int bulletDamage;
		int shootDelayCount;
		int bulletShotCount;
		int shieldFrameCount;

		bool isDead;
		bool shieldsOn;

		char* plyrSpriteDir;
		char* plyrShieldDir;
		char* plyrBulletDir;
		char* plyrExpolodeDir;

		std::stringstream livesText;
		std::stringstream shieldText;
		std::stringstream scoreText;

	private:

		void hud();
		void reset();

		void playerManager();
		void bulletManager();
		void powerUpManager(int type);
		void shieldManager();
		void playerControls();
		void clampInWindow();

	public:

		Player(GameWindow& wnd, Keyboard& kbd, Mouse& mse, ResourceLoader& rseLoad, Audio& audio, Physics& physics);
		~Player();

		void update();

		bool playerEntrance();
		bool playerExit();
		void positionReset();

		void playerIsHit();
		void bulletHitsEnemy(int i);
		bool getIsBulletColliderOn(int i);
		void playerGetsPowerUp(int powerUpType);

		int getLives();
		int getShields();
		int getPlayerScore();
		void updatePlayerScore(int playerScore);

		bool getIsDead();
		SDL_Rect getPlayerRect();

		int getBulletDamage();
		SDL_Rect getBulletRect(int i);

		int getPosX();
		int getPosY();

};