#include "enemyTemmplate.h"

Enemy::Enemy(GameWindow& wnd, ResourceLoader& rseLoad, Audio& audio, Physics& physics) : wnd(wnd), rseLoad(rseLoad), audio(audio), physics(physics) {

	// ** Initialise everything here ** //

	isDead = false;

	health = NULL;
	speed = NULL;
	killScore = NULL;
	//xVel = 0;
	//yVel = 0;

	shipDestroyedSound = NULL;
	bulletShootSound = NULL;
	bulletHitSound = NULL;

	flip = SDL_FLIP_NONE;

	autoMoveLeft = false;
	autoMoveRight = false;
	autoMoveUp = false;
	autoMoveDown = false;

	shootDelay = NULL;
	shootDelayCount = NULL;

	holdingPowerUp = false;

}

Enemy::~Enemy() {

	// ** Destroy all objects' data ** //

	enemySprite.clean();

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		bullet[i].clear();
	}

	Mix_FreeChunk(shipDestroyedSound);
	shipDestroyedSound = NULL;
	
	Mix_FreeChunk(bulletShootSound);
	bulletShootSound = NULL;

	Mix_FreeChunk(bulletHitSound);
	bulletHitSound = NULL;

	std::cout << "Eenemy resources cleaned" << std::endl;

}

void Enemy::bulletManager() {

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		//Auto start bullet
		if (bullet[i].getBeingShot() == false && shootDelayCount == 0) {

			//Flip bullet if enemy is flipped
			if (flip == SDL_FLIP_VERTICAL && bullet[i].getBulletFlip() != flip) {
				bullet[i].setBulletFlip(SDL_FLIP_VERTICAL);
			}
			else if (flip == SDL_FLIP_NONE && bullet[i].getBulletFlip() != flip) {
				bullet[i].setBulletFlip(SDL_FLIP_NONE);
			}

			if (flip == SDL_FLIP_VERTICAL) {
				bullet[i].bulletSprite.setX(enemySprite.getX());
				bullet[i].bulletSprite.setY(enemySprite.getY() + enemySprite.getDestH());
			}
			else {
				bullet[i].bulletSprite.setX(enemySprite.getX());
				bullet[i].bulletSprite.setY(enemySprite.getY() - enemySprite.getDestH());
			}

			//bullet[i].bulletSprite.setSprite(bulletSpriteImg);
			audio.sound.playSound(bulletShootSound, 0);

			bullet[i].setBeingShot(true);
			bullet[i].setCollider(true);
			shootDelayCount++;

		}

		//Continue bullet travel if shot
		if (bullet[i].getBeingShot() && bullet[i].getCollider()) {
			bullet[i].bulletSprite.setY(bullet[i].bulletSprite.getY() + bullet[i].getBulletSpeed());
			bullet[i].bulletSprite.display(wnd);
		}

		//Prevent bullet from travelling forever
		bullet[i].bulletClamp();

	}

	//Adjust bullet fire delay
	if (shootDelayCount == shootDelay) { shootDelayCount = 0; }
	else if (shootDelayCount != 0) { shootDelayCount++; }

}

void Enemy::enemyManager() {

	//Destroy enemy ships when HP is below 1

	if (health <= 0 && !isDead) {

		playEnemyExplodeAnimation();

		audio.sound.playSound(shipDestroyedSound, 0);

		enemySprite.setSprite(NULL);

		speed = 0;
		shootDelay = -1;

		for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

			bullet[i].bulletSprite.clean();

			bullet[i].bulletSprite.setX(0);
			bullet[i].bulletSprite.setY(0);

			bullet[i].setBeingShot(false);

		}

		isDead = true;

		powerUp.powerUpSprite.setX(enemySprite.getX());
		powerUp.powerUpSprite.setY(enemySprite.getY());
		powerUp.setDeployed(true);

	}

}

void Enemy::update() {

	// ** Acts as a flow controller and updater ** //

	enemySprite.display(wnd); //Update enemy on screen to be displayed
	//enemySprite.displayAnimation(wnd);

	bulletManager();
	enemyManager();

	if (isDead && holdingPowerUp && powerUp.getDeployed()) {
		powerUp.autoMove(wnd);
	}

}

bool Enemy::colisionDetection(SDL_Rect colidder, int damage, Bullet& bltCollide) {

	//To be used outside of this class (use in stage.cpp)

	if (!isDead) {

		if (physics.aabb(enemySprite.getDestRect(), colidder) && bltCollide.getCollider()) {
			audio.sound.playSound(bulletHitSound, 0);
			health -= damage;
			bltCollide.setCollider(false);
			//bltCollide.clear();
			//bltCollide.hitAnimation(wnd);
			return true;
		}

	}

	return false;

}

int Enemy::getHP() {
	return health;
}

bool Enemy::getIsDead() {
	return isDead;
}

int Enemy::getKillScore() {
	return killScore;
}

Bullet Enemy::getBullet(int i) {
	return bullet[i];
}

SDL_Rect Enemy::getBulletRect(int i) {
	return bullet[i].bulletSprite.getDestRect();
}

bool Enemy::getHoldingPowerUp() {
	return holdingPowerUp;
}

void Enemy::setHP(int health) {
	this->health = health;
}

void Enemy::setShootDelay(int shootDelay) {
	this->shootDelay = shootDelay;
}

void Enemy::setSpeed(int speed) {
	this->speed = speed;
}

void Enemy::setKillScore(int killScore) {
	this->killScore = killScore;
}

void Enemy::setHoldingPowerUp(bool holdingPowerUp) {
	this->holdingPowerUp = holdingPowerUp;
}

void Enemy::setFlip(SDL_RendererFlip flip) {

	this->flip = flip;

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		if (bullet[i].getBeingShot() == false) {
			bullet[i].setBeingShot(flip);
		}

	}

}

SDL_RendererFlip Enemy::getFlip() {
	return flip;
}

void Enemy::setAutoMoveLeft(bool autoMoveLeft) {
	this->autoMoveLeft = autoMoveLeft;
}

void Enemy::setAutoMoveRight(bool autoMoveRight) {
	this->autoMoveRight = autoMoveRight;
}

void Enemy::setAutoMoveUp(bool autoMoveUp) {
	this->autoMoveUp = autoMoveUp;
}

void Enemy::setAutoMoveDown(bool autoMoveDown) {
	this->autoMoveDown = autoMoveDown;
}

bool Enemy::getAutoMoveLeft() {
	return autoMoveLeft;
}

bool Enemy::getAutoMoveRight() {
	return autoMoveRight;
}

bool Enemy::getAutoMoveUp() {
	return autoMoveUp;
}

bool Enemy::getAutoMoveDown() {
	return autoMoveDown;
}

int Enemy::getPosX() {
	return enemySprite.getX();
}

int Enemy::getPosY() {
	return enemySprite.getY();
}

void Enemy::setPosX(int x) {
	enemySprite.setX(x);
}

void Enemy::setPosY(int y) {
	enemySprite.setY(y);
}

int Enemy::getWidth() {
	return enemySprite.getDestW();
}

int Enemy::getHeight() {
	return enemySprite.getDestH();
}

void Enemy::setWidth(int w) {
	enemySprite.setDestW(w);
}

void Enemy::setHeight(int h) {
	enemySprite.setDestH(h);
}

void Enemy::moveLeft() {
	enemySprite.setX(enemySprite.getX() - speed);
}

void Enemy::moveRight() {
	enemySprite.setX(enemySprite.getX() + speed);
}

void Enemy::moveUp() {
	enemySprite.setY(enemySprite.getX() - speed);
}

void Enemy::moveDown() {
	enemySprite.setY(enemySprite.getX() + speed);
}

void Enemy::setShipDestroySound(Mix_Chunk* shipDestroyedSound) {
	this->shipDestroyedSound = shipDestroyedSound;
}

void Enemy::setShootSound(Mix_Chunk* bulletShootSound) {
	this->bulletShootSound = bulletShootSound;
}

void Enemy::setHitSound(Mix_Chunk* bulletHitSound) {
	this->bulletHitSound = bulletHitSound;
}

Mix_Chunk* Enemy::getShipDestroySound() {
	return shipDestroyedSound;
}

Mix_Chunk* Enemy::getShootSound() {
	return bulletShootSound;
}

Mix_Chunk* Enemy::getHitSound() {
	return bulletHitSound;
}

void Enemy::setEnemySprite(SDL_Texture* sprite) {
	enemySprite.setSprite(sprite);
}

void Enemy::setEnemyPosition(int x, int y) {
	enemySprite.setX(x);
	enemySprite.setY(y);
}

void Enemy::setEnemyDimensions(int sourceW, int sourceH) {
	enemySprite.setSourceW(sourceW);
	enemySprite.setSourceH(sourceH);
}

void Enemy::setEnemyRenderDimensions(int maxW, int maxH, int startW, int startY) {
	enemySprite.setImageRenderDimension(maxW, maxH, startW, startY);
}

void Enemy::setEnemyProperties(int x, int y, int sourceW, int sourceH, int destW, int destH) {
	enemySprite.setX(x);
	enemySprite.setY(y);
	enemySprite.setSourceW(sourceW);
	enemySprite.setSourceH(sourceH);
	enemySprite.setDestW(destW);
	enemySprite.setDestH(destH);
}

void Enemy::setEnemyProperties(SDL_Texture* sprite, int sourceW, int sourceH, int destW, int destH) {
	enemySprite.setSprite(sprite);
	enemySprite.setSourceW(sourceW);
	enemySprite.setSourceH(sourceH);
	enemySprite.setDestW(destW);
	enemySprite.setDestH(destH);
}

void Enemy::setEnemyProperties(SDL_Texture* sprite, int x, int y, int sourceW, int sourceH, int destW, int destH) {
	enemySprite.setSprite(sprite);
	enemySprite.setX(x);
	enemySprite.setY(y);
	enemySprite.setSourceW(sourceW);
	enemySprite.setSourceH(sourceH);
	enemySprite.setDestW(destW);
	enemySprite.setDestH(destH);
}

void Enemy::setEnemyAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection) {
	enemySprite.setAnimationProperies(animMaxFrame, animFrameDelay, animCurrentFrame, animFrameCounter, animDirection);
}

void Enemy::setBulletSpeed(int bulletSpeed) {
	
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		bullet[i].setBulletSpeed(bulletSpeed);
	}

}

void Enemy::setBulletSprite(SDL_Texture* bulletSpriteImg) {

	//this->bulletSpriteImg = bulletSpriteImg;
	
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		bullet[i].bulletSprite.setSprite(bulletSpriteImg);
	}
	
}

void Enemy::setBulletProperties(int sourceW, int sourceH, int destW, int destH, int bulletSpeed) {

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		bullet[i].bulletSprite.setSourceW(sourceW);
		bullet[i].bulletSprite.setSourceH(sourceH);
		bullet[i].bulletSprite.setDestW(destW);
		bullet[i].bulletSprite.setDestH(destH);
		bullet[i].setBulletSpeed(bulletSpeed);

	}

}

void Enemy::setBulletProperties(SDL_Texture* bulletSprite, int sourceW, int sourceH, int destW, int destH, int bulletSpeed) {

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		bullet[i].bulletSprite.setSprite(bulletSprite);
		bullet[i].bulletSprite.setSourceW(sourceW);
		bullet[i].bulletSprite.setSourceH(sourceH);
		bullet[i].bulletSprite.setDestW(destW);
		bullet[i].bulletSprite.setDestH(destH);
		bullet[i].setBulletSpeed(bulletSpeed);

	}

}

void Enemy::setBulletAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection) {
	
	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		bullet[i].bulletSprite.setAnimationProperies(animMaxFrame, animFrameDelay, animCurrentFrame, animFrameCounter, animDirection);

	}

}

void Enemy::setPowerUpType(int type) {
	powerUp.setType(type);
}

void Enemy::setPowerUpSprite(SDL_Texture* powerUpSprite) {
	powerUp.powerUpSprite.setSprite(powerUpSprite);
}

void Enemy::setPowerUpSpeed(int speed) {
	powerUp.setMoveSpeed(speed);
}

void Enemy::setPowerUpSpeed(int speedX, int speedY) {
	powerUp.setMoveSpeedX(speedX);
	powerUp.setMoveSpeedY(speedY);
}

void Enemy::setPowerUpDimensons(int sourceW, int sourceH, int destW, int destH) {
	powerUp.powerUpSprite.setSourceW(sourceW);
	powerUp.powerUpSprite.setSourceH(sourceH);
	powerUp.powerUpSprite.setDestW(destW);
	powerUp.powerUpSprite.setDestH(destH);
}

void Enemy::setPowerUpAnimationProperties(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection) {
	powerUp.powerUpSprite.setAnimationProperies(animMaxFrame, animFrameDelay, animCurrentFrame, animFrameCounter, animDirection);
}

void Enemy::playEnemyExplodeAnimation() {
	enemySprite.displayAnimation(wnd);
}

// ########### ARCHIVE ########### //
/*
void Enemy::clean() {

	// ** Destroy all objects' data ** //

	std::cout << "Cleaning enemy resources" << std::endl;
	enemySprite.clean();
	std::cout << "Enemy texture cleanned" << std::endl;

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		bullet[i].clear();
	}

	std::cout << "Enemy bullets texture cleanned" << std::endl;

}

void Enemy::setShootSoundChannel(int soundChnl) {
this->shootChnl;
}

void Enemy::setHitSoundChannel(int hitChnl) {
this->hitChnl = hitChnl;
}

int Enemy::getShootSoundChannel() {
return shootChnl;
}

int Enemy::getHitSoundChannel() {
return hitChnl;
}

void Enemy::updatePos(bool x, bool y, bool inverseX, bool inverseY) {

	//Moves the enemy

	if (x) {
		if (inverseX) {
			enemySprite.setX(enemySprite.getX() - speed);
		}
		else {
			enemySprite.setX(enemySprite.getX() + speed);
		}
	}
	if (y) {
		if (inverseY) {
			enemySprite.setY(enemySprite.getY() - speed);
		}
		else {
			enemySprite.setY(enemySprite.getY() + speed);
		}
	}

}
*/