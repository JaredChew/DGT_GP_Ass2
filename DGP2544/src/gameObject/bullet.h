#pragma once

#include <SDL.h>

#include "../engine/gameWindow.h"
#include "../engine/animatedSprite.h"

struct Bullet {

	AnimatedSprite bulletSprite;

	int getBulletSpeed();
	bool getBeingShot();
	bool getCollider();

	void setBulletSpeed(int bulletSpeed);
	void setBeingShot(bool beingShot);
	void setCollider(bool collider);

	void bulletClamp();
	void clear();

	private:

		SDL_RendererFlip flip = SDL_FLIP_NONE;

		bool beingShot = false;
		bool collider = false;

		int bulletSpeed = NULL;

};