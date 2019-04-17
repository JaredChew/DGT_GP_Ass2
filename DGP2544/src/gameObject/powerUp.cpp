#include "powerUp.h"

void PowerUp::setType(int type) {
	this->type = type;
}

int PowerUp::getType() {
	return type;
}

int PowerUp::getMoveSpeed() {
	return xVel || yVel;
}

bool PowerUp::getDeployed() {
	return deployed;
}

void PowerUp::setMoveSpeed(int moveSpeed) {
	xVel = moveSpeed;
	yVel = moveSpeed;
}

void PowerUp::setDeployed(bool deployed) {
	this->deployed = deployed;
}

void PowerUp::setMoveSpeedX(int moveSpeedX) {
	xVel = moveSpeedX;
}

void PowerUp::setMoveSpeedY(int moveSpeedY) {
	yVel = moveSpeedY;
}

int PowerUp::getMoveSpeedX() {
	return xVel;
}

int PowerUp::getMoveSpeedY() {
	return yVel;
}

void PowerUp::hitAnimation(GameWindow& wnd) {
	powerUpSprite.displayAnimation(wnd);
}

void PowerUp::autoMove(GameWindow& wnd) {
	powerUpSprite.setPosX(powerUpSprite.getPosX() + xVel);
	powerUpSprite.setPosY(powerUpSprite.getPosY() + yVel);
	powerUpClamp();
	powerUpSprite.display(wnd);
}

void PowerUp::powerUpClamp() {

	if (powerUpSprite.getPosX() <= 0 || powerUpSprite.getPosX() + powerUpSprite.getDisplayW() >= WIDTH) {
		xVel = -xVel;
	}
	
	if (powerUpSprite.getPosY() <= 0) {
		yVel = -yVel;
	}
	else if (powerUpSprite.getPosY() >= HEIGHT) {
		clear();
	}
	
}

void PowerUp::clear() {

	powerUpSprite.clean();

	deployed = false;

}