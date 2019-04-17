#include "bullet.h"

int Bullet::getBulletSpeed() {
	return bulletSpeed;
}

bool Bullet::getBeingShot() {
	return beingShot;
}

bool Bullet::getCollider() {
	return collider;
}

void Bullet::setBulletSpeed(int bulletSpeed) {
	this->bulletSpeed = bulletSpeed;
}

void Bullet::setBeingShot(bool beingShot) {
	this->beingShot = beingShot;
}

void Bullet::setCollider(bool collider) {
	this->collider = collider;
}

void Bullet::bulletClamp() {

	if (beingShot && (bulletSprite.getPosX() < (0 - bulletSprite.getDisplayW()) || bulletSprite.getPosX() > (WIDTH + bulletSprite.getDisplayW()))) {
		beingShot = false;
		collider = false;
	}
	else if (beingShot && (bulletSprite.getPosY() < (0 - bulletSprite.getDisplayH()) || bulletSprite.getPosY() > (HEIGHT + bulletSprite.getDisplayH()))) {
		beingShot = false;
		collider = false;
	}

}

void Bullet::clear() {

	bulletSprite.clean();

	beingShot = false;
	collider = false;

}