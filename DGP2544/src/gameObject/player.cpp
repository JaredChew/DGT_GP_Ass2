#include "player.h"

Player::Player(GameWindow& wnd, Keyboard& kbd, Mouse& mse, ResourceLoader& rseLoad, Audio& audio, Physics& physics) : wnd(wnd), kbd(kbd), mse(mse), rseLoad(rseLoad), audio(audio), physics(physics) {

	// ** Initialise everything here ** //

	font = new Font(wnd);
	font->setFont(rseLoad.loadFont("asset/font/consolas.ttf", 100));

	shipDestroyedSound = rseLoad.loadSound("asset/sound/playerExplode.wav");
	bulletShootSound = rseLoad.loadSound("asset/sound/playerShoot.wav");
	bulletHitSound = rseLoad.loadSound("asset/sound/playerBulletHit.wav");
	powerUpHitSound = rseLoad.loadSound("asset/sound/powerUpHit.wav");
	shieldSound = rseLoad.loadSound("asset/sound/playerShieldUp.wav");

	plyrSpriteDir = "asset/graphic/player.png"; //playerAnimation
	plyrShieldDir = "asset/graphic/player_shieldsAnimation.png";
	plyrBulletDir = "asset/graphic/playerBulletAnimation.bmp"; 

	playerSprite.setImage(rseLoad.loadTextureImage(plyrSpriteDir));

	playerSprite.setSpriteRect(0, 0, 50, 50);
	playerSprite.setDisplayRect(0, 0, 50, 50);
	playerSprite.setAnimationProperties(50, 50, 4, 5, 0);

	playerSprite.setPosX((WIDTH / 2) - playerSprite.getDisplayW());
	playerSprite.setPosY(HEIGHT);

	score = 0;
	lives = 5;
	maxLives = 5;
	shields = 3;
	maxShields = 3;
	shootDelay = 10;
	shieldDuration = 320;
	bulletDamage = 100;
	shootDelayCount = 0;
	bulletShotCount = 0;
	shieldFrameCount = 0;

	flipDelay = 60;
	flipDelayCount = 0;

	isDead = false;
	shieldsOn = false;

	for (int i = 0; i < PLAYER_MAX_BULLET; i++) {
		bullet[i].bulletSprite.setImage(rseLoad.loadTextureImage(plyrBulletDir));
		bullet[i].bulletSprite.setSpriteRect(0, 0, 40, 42);
		bullet[i].bulletSprite.setDisplayRect(0, 0, 40, 42);
		bullet[i].bulletSprite.setAnimationProperties(40, 42, 6, 10, 1);
		bullet[i].setBulletSpeed(10);
	}

}

Player::~Player() { 

	// ** Destroy all objects' data ** //

	playerSprite.clean();

	for (int i = 0; i < PLAYER_MAX_BULLET; i++) {
		bullet[i].clear();
	}

	Mix_FreeChunk(shipDestroyedSound);
	shipDestroyedSound = NULL;

	Mix_FreeChunk(bulletShootSound);
	bulletShootSound = NULL;

	Mix_FreeChunk(bulletHitSound);
	bulletHitSound = NULL;

	Mix_FreeChunk(powerUpHitSound);
	powerUpHitSound = NULL;

	Mix_FreeChunk(shieldSound);
	shieldSound = NULL;

	plyrSpriteDir = NULL;
	plyrShieldDir = NULL;
	plyrBulletDir = NULL;
	plyrExpolodeDir = NULL;

	std::cout << "Deleting Player Font object" << std::endl;

	delete font;
	font = NULL;

	std::cout << "Player resources cleaned" << std::endl;

}

void Player::reset() {

	//Resets player stats

	lives = 3;
	shields = 0;
	shieldsOn = false;
	shieldFrameCount = 0;

}

void Player::clampInWindow() {

	// Player gets set back to X position 1 at the most left
	if (playerSprite.getPosX() <= 0 ) { playerSprite.setPosX(WIDTH); }

	// Player gets set back to the end of the X position at the most right factoring the size of the drone
	if (playerSprite.getPosX() > WIDTH) {
		playerSprite.setPosX(0);
	}

	// Player gets set back to Y position 1 at the most top
	if (playerSprite.getPosY() <= 0) { playerSprite.setPosY(HEIGHT); }

	// Player gets set back to the end of the Y position at the most bottom factoring the size of the drone
	if (playerSprite.getPosY() > HEIGHT) {
		playerSprite.setPosY(0);
	}

}

void Player::shieldManager() {

	//Changes sprite when shield is activated
	if (shieldsOn && shieldFrameCount == 1) {
		playerSprite.setImage(rseLoad.loadTextureImage(plyrShieldDir));
	}
	else if (shieldFrameCount == shieldDuration && shieldsOn) {
		playerSprite.setImage(rseLoad.loadTextureImage(plyrSpriteDir));
		shieldsOn = false;
		shieldFrameCount = 0;
	}
	else if (!shieldsOn && shieldFrameCount != shieldDuration) {
		playerSprite.setImage(rseLoad.loadTextureImage(plyrSpriteDir));
		shieldsOn = false;
		shieldFrameCount = 0;
	}

	if (shieldsOn) {
		shieldFrameCount++;
	}

}

void Player::bulletManager() {

	//Moves bullet
	for (int i = 0; i < PLAYER_MAX_BULLET; i++) {

		//Continue bullet travel if shot
		if (bullet[i].getBeingShot() && bullet[i].getCollider()) {

			//bullet[i].bulletSprite.setX(bullet[i].bulletSprite.getX() + bullet[i].getBulletSpeed());
			if (bullet[i].bulletSprite.getFlip() == SDL_FLIP_VERTICAL) {
				bullet[i].bulletSprite.setPosY(bullet[i].bulletSprite.getPosY() + bullet[i].getBulletSpeed());
			}
			else {
				bullet[i].bulletSprite.setPosY(bullet[i].bulletSprite.getPosY() - bullet[i].getBulletSpeed());
			}

			bullet[i].bulletClamp();
			bullet[i].bulletSprite.display(wnd, bullet[i].bulletSprite.getFlip());

		}

	}

	//Maintain cycle of bullets to shoot
	if (bulletShotCount == PLAYER_MAX_BULLET - 1) {
		bulletShotCount = 0;
	}

}

void Player::powerUpManager(int type) {

	if (type == LIVES && lives <= maxLives) {
		lives++;
	}
	else if (type == SHIELD && shields <= maxShields) {
		shields++;
	}

}

void Player::playerManager() {

	//Adjust bullet fire delay
	if (shootDelayCount == shootDelay) { shootDelayCount = 0; }
	else if (shootDelayCount != 0) { shootDelayCount++; }

	if (lives <= 0) {
		//playerSprite.displayAnimation(wnd);
		audio.sound.playSound(shipDestroyedSound, 0);
		isDead = true;
	}

	if (flipDelayCount == flipDelay) {
		flipDelayCount = 0;
	}
	else if (flipDelayCount != 0) {
		flipDelayCount++;
	}

}

void Player::hud() {

	// ** Displays  number of lives and shield ** //

	livesText.str("");
	livesText << "Lives: " << lives;

	font->drawFont(livesText.str(), WIDTH - 100, 10, 80, 30, 255, 255, 255);

	shieldText.str("");
	shieldText << "Shield: " << shields;

	font->drawFont(shieldText.str(), WIDTH - 100, 45, 80, 30, 255, 255, 255);

	scoreText.str("");
	scoreText << "Score: " << score;

	font->drawFont(scoreText.str(), WIDTH - 100, 80, 80, 30, 255, 255, 255);

	livesText.clear();
	shieldText.clear();
	scoreText.clear();

}

void Player::playerControls() {

	// ** Set player controls here ** //

	if ((kbd.isPressed(SDL_SCANCODE_W) || kbd.isPressed(SDL_SCANCODE_UP)) && (kbd.isPressed(SDL_SCANCODE_D) || kbd.isPressed(SDL_SCANCODE_RIGHT))) { //North-east
		playerSprite.setPosX(playerSprite.getPosX() + (int)(PLAYER_SPEED / 1.5));
		playerSprite.setPosY(playerSprite.getPosY() - (int)(PLAYER_SPEED / 1.5));
	}
	else if ((kbd.isPressed(SDL_SCANCODE_D) || kbd.isPressed(SDL_SCANCODE_RIGHT)) && (kbd.isPressed(SDL_SCANCODE_S) || kbd.isPressed(SDL_SCANCODE_DOWN))) { //South-east
		playerSprite.setPosX(playerSprite.getPosX() + (int)(PLAYER_SPEED / 1.5));
		playerSprite.setPosY(playerSprite.getPosY() + (int)(PLAYER_SPEED / 1.5));
	}
	else if ((kbd.isPressed(SDL_SCANCODE_S) || kbd.isPressed(SDL_SCANCODE_DOWN)) && (kbd.isPressed(SDL_SCANCODE_A) || kbd.isPressed(SDL_SCANCODE_LEFT))) { //South-west
		playerSprite.setPosX(playerSprite.getPosX() - (int)(PLAYER_SPEED / 1.5));
		playerSprite.setPosY(playerSprite.getPosY() + (int)(PLAYER_SPEED / 1.5));
	}
	else if ((kbd.isPressed(SDL_SCANCODE_A) || kbd.isPressed(SDL_SCANCODE_LEFT)) && (kbd.isPressed(SDL_SCANCODE_W) || kbd.isPressed(SDL_SCANCODE_UP))) { //North-west
		playerSprite.setPosX(playerSprite.getPosX() - (int)(PLAYER_SPEED / 1.5));
		playerSprite.setPosY(playerSprite.getPosY() - (int)(PLAYER_SPEED / 1.5));
	}
	else if ((kbd.isPressed(SDL_SCANCODE_W) || kbd.isPressed(SDL_SCANCODE_UP))) { //North
		playerSprite.setPosY(playerSprite.getPosY() - PLAYER_SPEED);
	}
	else if ((kbd.isPressed(SDL_SCANCODE_A) || kbd.isPressed(SDL_SCANCODE_LEFT))) { //West
		playerSprite.setPosX(playerSprite.getPosX() - PLAYER_SPEED);
	}
	else if ((kbd.isPressed(SDL_SCANCODE_S) || kbd.isPressed(SDL_SCANCODE_DOWN))) { //South
		playerSprite.setPosY(playerSprite.getPosY() + PLAYER_SPEED);
	}
	else if ((kbd.isPressed(SDL_SCANCODE_D) || kbd.isPressed(SDL_SCANCODE_RIGHT))) { //East
		playerSprite.setPosX(playerSprite.getPosX() + PLAYER_SPEED);
	}

	if (kbd.isPressed(SDL_SCANCODE_SPACE) && shootDelayCount == 0) { //Shoot bullet

		//Flip bullet if player flips
		if (playerSprite.getFlip() == SDL_FLIP_VERTICAL && bullet[bulletShotCount].bulletSprite.getFlip() != playerSprite.getFlip()) {
			bullet[bulletShotCount].bulletSprite.setFlip(SDL_FLIP_VERTICAL);
		}
		else if (playerSprite.getFlip() == SDL_FLIP_NONE && bullet[bulletShotCount].bulletSprite.getFlip() != playerSprite.getFlip()) {
			bullet[bulletShotCount].bulletSprite.setFlip(SDL_FLIP_NONE);
		}

		if (playerSprite.getFlip() == SDL_FLIP_VERTICAL) {
			bullet[bulletShotCount].bulletSprite.setPosX(playerSprite.getPosX()); // + playerSprite.geDisplaytW()
			bullet[bulletShotCount].bulletSprite.setPosY(playerSprite.getPosY() + playerSprite.getDisplayH());
		}
		else {
			bullet[bulletShotCount].bulletSprite.setPosX(playerSprite.getPosX()); // + playerSprite.getW()
			bullet[bulletShotCount].bulletSprite.setPosY(playerSprite.getPosY() - playerSprite.getDisplayH());
		}

		bullet[bulletShotCount].setBeingShot(true);
		bullet[bulletShotCount].setCollider(true);

		audio.sound.playSound(bulletShootSound, 0);

		bulletShotCount++;
		shootDelayCount++;

	}

	if (kbd.isPressed(SDL_SCANCODE_LSHIFT) && !shieldsOn) { //Activate shield

		if (shields != 0) {
			shieldsOn = true;
			shields--;
			shieldFrameCount++;
			audio.sound.playSound(shieldSound, 0);
		}

	}

	if (kbd.isPressed(SDL_SCANCODE_F)) {

		if (playerSprite.getFlip() == SDL_FLIP_VERTICAL && flipDelayCount == 0) {
			playerSprite.setFlip(SDL_FLIP_NONE);
			flipDelayCount++;
		}
		else if(flipDelayCount == 0) {
			playerSprite.setFlip(SDL_FLIP_VERTICAL);
			flipDelayCount++;
		}

	}

}

void  Player::update() {

	// ** Acts as a flow controller and updater ** //

	hud();
	playerControls();
	shieldManager();
	clampInWindow(); //Prevents player from flying away from window
	playerSprite.display(wnd); //Update player on screen to be displayed
	//playerSprite.displayAnimation(wnd); //not working
	bulletManager();
	playerManager();

}

bool Player::playerEntrance() {

	//quick solution, tired of coding this game

	playerSprite.display(wnd);

	if (playerSprite.getPosY() >= HEIGHT - 100) {
		playerSprite.setPosY(playerSprite.getPosY() - PLAYER_SPEED);
	}

	if (playerSprite.getPosY() <= HEIGHT - 100) {
		return false;
	}

	return true;

}

bool Player::playerExit() {

	//quick solution, tired of coding this game

	playerSprite.display(wnd);

	if (playerSprite.getPosY() >= (0 - playerSprite.getDisplayH())) {
		playerSprite.setPosY(playerSprite.getPosY() - PLAYER_SPEED);
	}

	else if (playerSprite.getPosY() <= (0 - playerSprite.getDisplayH())) {
		return true;
	}

	return false;

}

void Player::positionReset() {
	playerSprite.setPosX((WIDTH / 2) - playerSprite.getDisplayW());
	playerSprite.setPosY(HEIGHT);
}

void Player::bulletHitsEnemy(int i) {

	bullet[i].setCollider(false);
	bullet[i].bulletSprite.displayAnimationOnce(wnd);

}

bool Player::getIsBulletColliderOn(int i) {
	return bullet[i].getCollider();
}

void Player::playerGetsPowerUp(int powerUpType) {

	audio.sound.playSound(powerUpHitSound, 0);

	powerUpManager(powerUpType);

}

void Player::playerIsHit() {

	if (shieldsOn) {
		shieldsOn = false;
	}
	else {
		audio.sound.playSound(bulletHitSound, 0);
		lives -= 1;
	}

	//bltCollide.setCollider(false);
	//bltCollide.hitAnimation(wnd);

}

int Player::getLives() {
	return lives;
}

int Player::getShields() {
	return shields;
}

int Player::getPlayerScore() {
	return score;
}

void Player::updatePlayerScore(int playerScore) {
	score += playerScore;
}

bool Player::getIsDead() {
	return isDead;
}

SDL_Rect Player::getPlayerRect() {
	return playerSprite.getDisplayRect();
}

int Player::getBulletDamage() {
	return bulletDamage;
}
SDL_Rect Player::getBulletRect(int i) {
	return bullet[i].bulletSprite.getDisplayRect();
}

int Player::getPosX() {
	return playerSprite.getPosX();
}

int Player::getPosY() {
	return playerSprite.getPosY();
}

// ########### ARCHIVE ########### //
/*
void Player::clean() {

// ** Destroy all objects' data ** //

std::cout << "Cleaning player resources" << std::endl;
playerSprite.clean();
std::cout << "Player texture cleanned" << std::endl;

for (int i = 0; i < PLAYER_MAX_BULLET; i++) {
bullet[i].clear();
}

std::cout << "Player bullets texture cleanned" << std::endl;

font->close();
//delete font;

}
*/