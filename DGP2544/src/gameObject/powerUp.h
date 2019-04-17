#pragma once

#include <SDL.h>

#include "../engine/gameWindow.h"
#include "../engine/animatedSprite.h"

#define LIVES 1
#define SHIELD 2

struct PowerUp {

	AnimatedSprite powerUpSprite;

	void setType(int type);
	int getType();

	int getMoveSpeed();
	bool getDeployed();

	void setMoveSpeed(int moveSpeed);
	void setDeployed(bool deployed);

	void setMoveSpeedX(int moveSpeedX);
	void setMoveSpeedY(int moveSpeedY);
	
	int getMoveSpeedX();
	int getMoveSpeedY();

	void hitAnimation(GameWindow& wnd);
	void powerUpClamp();
	void autoMove(GameWindow& wnd);
	void clear();

private:

	int type = NULL;

	int xVel = NULL;
	int yVel = NULL;

	bool deployed = false;

};