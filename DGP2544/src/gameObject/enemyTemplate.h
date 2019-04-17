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

class Enemy {

	private:

		GameWindow& wnd;
		ResourceLoader& rseLoad;
		Audio& audio;
		Physics& physics;

	public:

		//Temperory solution
		Bullet bullet[ENEMY_MAX_BULLET];
		PowerUp powerUp;

	private:

		AnimatedSprite enemySprite;

		Mix_Chunk* shipDestroyedSound;
		Mix_Chunk* bulletShootSound;
		Mix_Chunk* bulletHitSound;

		bool isDead;

		int health;
		int speed;
		int killScore;
		//int xVel;
		//int yVel;

		SDL_RendererFlip flip;

		bool autoMoveLeft;
		bool autoMoveRight;
		bool autoMoveUp;
		bool autoMoveDown;

		int shootDelay;
		int shootDelayCount;

		bool holdingPowerUp;

	public:

		Enemy(GameWindow& wnd, ResourceLoader& rseLoad, Audio& audio, Physics& physics);
		~Enemy();

		//void clean();
		void update();

		//void updatePos(bool x, bool y, bool inverseX, bool inverseY);
		bool colisionDetection(SDL_Rect colidder, int damage, Bullet& bltCollide);

		int getHP();
		int getKillScore();
		bool getIsDead();
		Bullet getBullet(int i);
		SDL_Rect getBulletRect(int i);
		bool getHoldingPowerUp();

		void setHP(int health);
		void setKillScore(int killScore);
		void setShootDelay(int shootDelay);
		void setSpeed(int speed);
		void setHoldingPowerUp(bool holdingPowerUp);

		void setAutoMoveLeft(bool autoMoveLeft);
		void setAutoMoveRight(bool autoMoveRight);
		void setAutoMoveUp(bool autoMoveUp);
		void setAutoMoveDown(bool autoMoveDown);

		bool getAutoMoveLeft();
		bool getAutoMoveRight();
		bool getAutoMoveUp();
		bool getAutoMoveDown();

		int getPosX();
		int getPosY();
		void setPosX(int x);
		void setPosY(int y);

		int getWidth();
		int getHeight();
		void setWidth(int w);
		void setHeight(int h);

		void setFlip(SDL_RendererFlip flip);
		SDL_RendererFlip getFlip();

		void moveLeft();
		void moveRight();
		void moveUp();
		void moveDown();

		void setShipDestroySound(Mix_Chunk* shipDestroyedSound);
		void setShootSound(Mix_Chunk* bulletShootSound);
		void setHitSound(Mix_Chunk* bulletHitSound);

		Mix_Chunk* getShipDestroySound();
		Mix_Chunk* getShootSound();
		Mix_Chunk* getHitSound();

		//int getShootSoundChannel();
		//int getHitSoundChannel();

		//void setShootSoundChannel(int shootChnl);
		//void setHitSoundChannel(int hitChnl);

		void setEnemySprite(SDL_Texture* sprite);
		void setEnemyPosition(int x, int y);
		void setEnemyDimensions(int sourceW, int sourceH);
		void setEnemyRenderDimensions(int maxW, int maxH, int startW, int startY);
		void setEnemyProperties(int x, int y, int sourceW, int sourceH, int destW, int destH);
		void setEnemyProperties(SDL_Texture* sprite, int sourceW, int sourceH, int destW, int destH);
		void setEnemyProperties(SDL_Texture* sprite, int x, int y, int sourceW, int sourceH, int destW, int destH);
		void setEnemyAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection);

		void setBulletSpeed(int bulletSpeed);
		void setBulletSprite(SDL_Texture* bulletSprite);
		void setBulletProperties(int sourceW, int sourceH, int destW, int destH, int bulletSpeed);
		void setBulletProperties(SDL_Texture* bulletSprite, int sourceW, int sourceH, int destW, int destH, int bulletSpeed);
		void setBulletAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection);

		void setPowerUpType(int type);
		void setPowerUpSprite(SDL_Texture* powerUpSprite);
		void setPowerUpSpeed(int speed);
		void setPowerUpSpeed(int speedX, int speedY);
		void setPowerUpDimensons(int sourceW, int sourceH, int destW, int destH);
		void setPowerUpAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection);

		void playEnemyExplodeAnimation();

	private:

		void enemyManager();
		void bulletManager();

};