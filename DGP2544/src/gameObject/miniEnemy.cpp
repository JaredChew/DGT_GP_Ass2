#include "miniEnemy.h"

MiniEnemy::MiniEnemy(GameWindow& wnd, ResourceLoader& rseLoad, Audio& audio, Physics& physics) : wnd(wnd), rseLoad(rseLoad), audio(audio), physics(physics) {

	// ** Initialise everything here ** //

	isDead = false;

	health = 500;
	speed = 2;
	killScore = 100;

	shipDestroyedSound = NULL;
	bulletShootSound = NULL;
	bulletHitSound = NULL;

	autoMoveLeft = false;
	autoMoveRight = false;
	autoMoveUp = false;
	autoMoveDown = false;

	shootDelay = 30 + (rand() % 60);
	shootDelayCounter = 0;

	holdingPowerUp = false;

	enemySprite.setImage(rseLoad.loadTextureImage("asset/graphic/miniEnemyAnimation.png"));
	enemySprite.setDisplayRect(0, 0, 60, 50);
	enemySprite.setSpriteRect(0, 0, 60, 50);
	enemySprite.setAnimationProperties(60, 50, 13, 3, 1);

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
		bullet[i].bulletSprite.setImage(rseLoad.loadTextureImage("asset/graphic/miniEnemy_bullet.png"));
		bullet[i].bulletSprite.setDisplayRect(0, 0, 16, 30);
		bullet[i].bulletSprite.setSpriteRect(0, 0, 16, 30);
		bullet[i].setBulletSpeed(10);
	}

	shipDestroyedSound = rseLoad.loadSound("asset/sound/enemyExplode.wav");
	bulletShootSound = rseLoad.loadSound("asset/sound/enemyShoot.wav");
	bulletHitSound = rseLoad.loadSound("asset/sound/enemyBulletHit.wav");

}

MiniEnemy::~MiniEnemy() {

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

void MiniEnemy::bulletManager() {

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		//Auto start bullet
		if (bullet[i].getBeingShot() == false && shootDelayCounter == 0) {

			//Flip bullet if enemy is flipped
			if (enemySprite.getFlip() == SDL_FLIP_VERTICAL && bullet[i].bulletSprite.getFlip() != enemySprite.getFlip()) {
				bullet[i].bulletSprite.setFlip(SDL_FLIP_VERTICAL);
			}
			else if (enemySprite.getFlip() == SDL_FLIP_NONE && bullet[i].bulletSprite.getFlip() != enemySprite.getFlip()) {
				bullet[i].bulletSprite.setFlip(SDL_FLIP_NONE);
			}

			if (enemySprite.getFlip() == SDL_FLIP_VERTICAL) {
				bullet[i].bulletSprite.setPosX(enemySprite.getPosX());
				bullet[i].bulletSprite.setPosY(enemySprite.getPosY() + enemySprite.getDisplayH());
			}
			else {
				bullet[i].bulletSprite.setPosX(enemySprite.getPosX());
				bullet[i].bulletSprite.setPosY(enemySprite.getPosY() - enemySprite.getDisplayH());
			}

			//bullet[i].bulletSprite.setSprite(bulletSpriteImg);
			audio.sound.playSound(bulletShootSound, 0);

			bullet[i].setBeingShot(true);
			bullet[i].setCollider(true);
			shootDelayCounter++;

		}

		//Continue bullet travel if shot
		if (bullet[i].getBeingShot() && bullet[i].getCollider()) {
			bullet[i].bulletSprite.setPosY(bullet[i].bulletSprite.getPosY() + bullet[i].getBulletSpeed());
			bullet[i].bulletSprite.display(wnd);
		}

		//Prevent bullet from travelling forever
		bullet[i].bulletClamp();

	}

	//Adjust bullet fire delay
	if (shootDelayCounter == shootDelay) { shootDelayCounter = 0; }
	else if (shootDelayCounter != 0) { shootDelayCounter++; }

}

void MiniEnemy::enemyManager() {

	//Destroy enemy ships when HP is below 1

	if (health <= 0 && !isDead) {

		audio.sound.playSound(shipDestroyedSound, 0);

		//enemySprite.setImage(NULL);

		speed = 0;
		shootDelay = -1;

		for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

			bullet[i].bulletSprite.clean();

			bullet[i].bulletSprite.setPosX(0);
			bullet[i].bulletSprite.setPosY(0);

			bullet[i].setBeingShot(false);

		}

		isDead = true;

		powerUp.powerUpSprite.setPosX(enemySprite.getPosX());
		powerUp.powerUpSprite.setPosY(enemySprite.getPosY());
		powerUp.setDeployed(true);

	}

}

void MiniEnemy::update() {

	// ** Acts as a flow controller and updater ** //

	if (!isDead) {
		enemySprite.display(wnd); //Update enemy on screen to be displayed
		bulletManager();
		enemyManager();
	}
	else {
		enemySprite.displayAnimationOnce(wnd);
	}

	if (isDead && holdingPowerUp && powerUp.getDeployed()) {
		powerUp.autoMove(wnd);
	}

}

bool MiniEnemy::getIsBulletColliderOn(int i) {
	return bullet[i].getCollider();
}

void MiniEnemy::enemyIsHit(int damageTaken) {

	health -= damageTaken;
}

void MiniEnemy::bulletHitsPlayer(int i) {

	audio.sound.playSound(bulletHitSound, 0);
	bullet[i].setCollider(false);
	//bullet[i].bulletSprite.displayAnimation(wnd);

}

int MiniEnemy::getHP() {
	return health;
}

bool MiniEnemy::getIsDead() {
	return isDead;
}

int MiniEnemy::getKillScore() {
	return killScore;
}

bool MiniEnemy::getIsHoldingPowerUp() {
	return holdingPowerUp;
}

void MiniEnemy::setAutoMoveLeft(bool autoMoveLeft) {
	this->autoMoveLeft = autoMoveLeft;
}

void MiniEnemy::setAutoMoveRight(bool autoMoveRight) {
	this->autoMoveRight = autoMoveRight;
}

void MiniEnemy::setAutoMoveUp(bool autoMoveUp) {
	this->autoMoveUp = autoMoveUp;
}

void MiniEnemy::setAutoMoveDown(bool autoMoveDown) {
	this->autoMoveDown = autoMoveDown;
}

bool MiniEnemy::getAutoMoveLeft() {
	return autoMoveLeft;
}

bool MiniEnemy::getAutoMoveRight() {
	return autoMoveRight;
}

bool MiniEnemy::getAutoMoveUp() {
	return autoMoveUp;
}

bool MiniEnemy::getAutoMoveDown() {
	return autoMoveDown;
}

int MiniEnemy::getPosX() {
	return enemySprite.getPosX();
}

int MiniEnemy::getPosY() {
	return enemySprite.getPosY();
}

void MiniEnemy::setPosition(int x, int y) {
	enemySprite.setPosX(x);
	enemySprite.setPosY(y);
}

void MiniEnemy::setPosX(int x) {
	enemySprite.setPosX(x);
}

void MiniEnemy::setPosY(int y) {
	enemySprite.setPosY(y);
}

int MiniEnemy::getWidth() {
	return enemySprite.getDisplayW();
}

int MiniEnemy::getHeight() {
	return enemySprite.getDisplayH();
}

void MiniEnemy::moveLeft() {
	enemySprite.setPosX(enemySprite.getPosX() - speed);
}

void MiniEnemy::moveRight() {
	enemySprite.setPosX(enemySprite.getPosX() + speed);
}

void MiniEnemy::moveUp() {
	enemySprite.setPosY(enemySprite.getPosY() - speed);
}

void MiniEnemy::moveDown() {
	enemySprite.setPosY(enemySprite.getPosY() + speed);
}

SDL_Rect MiniEnemy::getEnemyRect() {
	return enemySprite.getDisplayRect();
}

SDL_Rect MiniEnemy::getBulletRect(int i) {
	return bullet[i].bulletSprite.getDisplayRect();
}

SDL_Rect MiniEnemy::getPowerUpRect() {
	return powerUp.powerUpSprite.getDisplayRect();
}

void MiniEnemy::initPowerUp(int powerUpType) {

	holdingPowerUp = true;

	powerUp.powerUpSprite.setImage(rseLoad.loadTextureImage("asset/graphic/powerUp_shield.png"));
	powerUp.powerUpSprite.setDisplayRect(0, 0, 25, 25);
	powerUp.powerUpSprite.setSpriteRect(0, 0, 25, 25);
	powerUp.setMoveSpeed(2);
	powerUp.setType(SHIELD);

}

int MiniEnemy::getPowerUpType() {
	return powerUp.getType();
}

void MiniEnemy::setPowerUpType(int type) {
	powerUp.setType(type);
}

void MiniEnemy::powerUpHitsPlayer() {

	powerUp.setDeployed(false);
	//powerUp.clear();

}

bool MiniEnemy::getPowerUpIsDeployed() {
	return powerUp.getDeployed();
}

void MiniEnemy::setEnemySpeed(int speed) {
	this->speed = speed;
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

void Enemy::setFlip(SDL_RendererFlip flip) {

	this->flip = flip;

	for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

		if (bullet[i].getBeingShot() == false) {
			bullet[i].setBeingShot(flip);
		}

	}

}
*/