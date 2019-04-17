#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../engine/gameWindow.h"
#include "../engine/resourceLoader.h"
#include "../engine/audio.h"
#include "../engine/physics.h"
#include "../engine/animatedSprite.h"

#include "bullet.h"
#include "powerUp.h"

#define ENEMY_MAX_BULLET 10

class MiniEnemy {

private:

	GameWindow& wnd;
	ResourceLoader& rseLoad;
	Audio& audio;
	Physics& physics;

private:

	AnimatedSprite enemySprite;
	Bullet bullet[ENEMY_MAX_BULLET];
	PowerUp powerUp;

	Mix_Chunk* shipDestroyedSound;
	Mix_Chunk* bulletShootSound;
	Mix_Chunk* bulletHitSound;

	bool isDead;

	int health;
	int speed;
	int killScore;

	int shootDelay;
	int shootDelayCounter;

	bool autoMoveLeft;
	bool autoMoveRight;
	bool autoMoveUp;
	bool autoMoveDown;

	bool holdingPowerUp;

public:

	MiniEnemy(GameWindow& wnd, ResourceLoader& rseLoad, Audio& audio, Physics& physics);
	~MiniEnemy();

	void update();

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void powerUpHitsPlayer();
	void enemyIsHit(int damageTaken);
	void bulletHitsPlayer(int i);

	int getHP();
	int getKillScore();
	bool getIsDead();
	bool getIsHoldingPowerUp();

	void setAutoMoveLeft(bool autoMoveLeft);
	void setAutoMoveRight(bool autoMoveRight);
	void setAutoMoveUp(bool autoMoveUp);
	void setAutoMoveDown(bool autoMoveDown);

	bool getAutoMoveLeft();
	bool getAutoMoveRight();
	bool getAutoMoveUp();
	bool getAutoMoveDown();

	int getWidth();
	int getHeight();

	int getPosX();
	int getPosY();

	void setPosX(int x);
	void setPosY(int y);
	void setPosition(int x, int y);

	SDL_Rect getEnemyRect();
	SDL_Rect getBulletRect(int i);
	SDL_Rect getPowerUpRect();

	bool getIsBulletColliderOn(int i);

	//Power Up
	void initPowerUp(int powerUpType);
	int getPowerUpType();
	void setPowerUpType(int type);
	bool getPowerUpIsDeployed();

	void setEnemySpeed(int speed);

private:

	void enemyManager();
	void bulletManager();

};