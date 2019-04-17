#include "testStage.h"

TestStage::TestStage(GameWindow& wnd, ResourceLoader& rseLoad, Player& player, Audio& audio, Physics& physics, Keyboard& kbd) : wnd(wnd), rseLoad(rseLoad), player(player), audio(audio), physics(physics), kbd(kbd) {

	// ** Initialise everything here ** //

	std::cout << "\nSetting up TestStage" << std::endl;

	//Initialise stage controlling variables

	srand(unsigned(time(NULL)));

	enemyDead = 0;
	stageClear = false;
	gamePaused = false;
	stageOpening = true;
	stageEnding = false;

	//Initialise pause menu

	subMenu = new SubMenu(wnd, kbd, rseLoad);

	//Load background music

	bgm = rseLoad.loadMusic("asset/music/testStage.flac");
	audio.music.playMusic(bgm, -1);

	//Load background
	background.bgImg = rseLoad.loadTextureImage("asset/graphic/backgroundScroll.bmp");

	//Initialise enemy

	int xPosCount = 0, yPosCount = 5;

	for (int i = 0; i < MAX_TEST_ENEMY; i++) {

		testEnemy[i] = new Enemy(wnd, rseLoad, audio, physics);

		testEnemy[i]->setShipDestroySound(rseLoad.loadSound("asset/sound/enemyExplode_test.wav"));
		testEnemy[i]->setShootSound(rseLoad.loadSound("asset/sound/enemyShoot_test.wav"));
		testEnemy[i]->setHitSound(rseLoad.loadSound("asset/sound/enemyBulletHit_test.wav"));

		testEnemy[i]->setHP(500);
		testEnemy[i]->setSpeed(2);
		testEnemy[i]->setKillScore(100);
		testEnemy[i]->setShootDelay(30 + (rand() % 32));

		testEnemy[i]->setEnemySprite(rseLoad.loadTextureImage("asset/graphic/miniEnemyAnimation.png"));
		//testEnemy[i]->setEnemyDimensions(780, 50);
		testEnemy[i]->setEnemyRenderDimensions(60, 50, 0, 0);
		testEnemy[i]->setEnemyPosition(xPosCount, yPosCount);

		testEnemy[i]->setBulletProperties(20, 25, 20, 25, 10);
		testEnemy[i]->setBulletSprite(rseLoad.loadTextureImage("asset/graphic/miniEnemy_bullet.png"));

		testEnemy[i]->setEnemyAnimationProperties(13, 30, 0, 0, 1);

		if (i == 4) {
			testEnemy[i]->setHoldingPowerUp(true);
			testEnemy[i]->setPowerUpSprite(rseLoad.loadTextureImage("asset/graphic/powerUp_test.png"));
			testEnemy[i]->setPowerUpDimensons(25, 25, 25, 25);
			testEnemy[i]->setPowerUpSpeed(2);
			testEnemy[i]->setPowerUpType(SHIELD);
		}

		if (i == 4) {
			yPosCount += (testEnemy[i]->getHeight()) + 50;
			xPosCount += testEnemy[i]->getWidth() + 30;
			testEnemy[i]->setAutoMoveRight(true);
		}
		else if (i > 4) {
			xPosCount -= (testEnemy[i]->getWidth() + 30);
			testEnemy[i]->setAutoMoveLeft(true);
		}
		else {
			xPosCount += testEnemy[i]->getWidth() + 30;
			testEnemy[i]->setAutoMoveRight(true);
		}

	}

}

TestStage::~TestStage() { 

	// ** Destroy all objects' data ** //

	delete subMenu;

	background.clean();

	Mix_FreeMusic(bgm);
	bgm = NULL;

	for (int i = 0; i < MAX_TEST_ENEMY; i++) {
		delete testEnemy[i];
		testEnemy[i] = NULL;
	}

	std::cout << "Test_Stage objects cleaned" << std::endl;

}

void TestStage::update() {

	// ** Update anything related to this class only ** //

	background.scroll(wnd);

}

void TestStage::enemyAI() {

	for (int i = 0; i < MAX_TEST_ENEMY; i++) {

		//Changes direction when touch window border
		if ((testEnemy[i]->getPosX() + testEnemy[i]->getWidth()) > WIDTH || testEnemy[i]->getPosX() < 0) {
			testEnemy[i]->setAutoMoveLeft(!testEnemy[i]->getAutoMoveLeft());
			testEnemy[i]->setAutoMoveRight(!testEnemy[i]->getAutoMoveRight());
		}

		//Moves enemy
		if (testEnemy[i]->getAutoMoveRight()) {
			testEnemy[i]->moveRight();
		}
		else if (testEnemy[i]->getAutoMoveLeft()) {
			testEnemy[i]->moveLeft();
		}

		//Display position update and shoots bullet
		testEnemy[i]->update();

	}

}

void TestStage::collisionDetection() {

	enemyDead = 0;

	for (int enmy = 0; enmy < MAX_TEST_ENEMY; enmy++) {

		//checks if enemy is being hit
		for (int i = 0; i < PLAYER_MAX_BULLET; i++) {
			if (testEnemy[enmy]->colisionDetection(player.bullet[i].bulletSprite.getDestRect(), player.getBulletDamage(), player.bullet[i])) {
				player.updatePlayerScore(testEnemy[enmy]->getKillScore());
			}
			//testEnemy->colisionDetection(player.getBulletRect(i) , player.getBulletDamage(), player.getBullet(i));
		}

		//checks if player is being hit
		for (int i = 0; i < ENEMY_MAX_BULLET; i++) {
			//player.colisionDetection(testEnemy[enmy]->bullet[i].bulletSprite.getRect(), testEnemy[enmy]->bullet[i]);
			//player.colisionDetection(testEnemy->getBulletRect(i), testEnemy->getBullet(i));
		}

		if (testEnemy[enmy]->powerUp.getDeployed()) { //Checks if power up hits player
			player.colisionDetection(testEnemy[enmy]->powerUp);
		}

		//game over when enemy is dead
		if (testEnemy[enmy]->getIsDead()) {
			enemyDead++;
		}

	}

	if (player.getIsDead()) {
		audio.music.stopMusic();
		background.bgImg = rseLoad.loadTextureImage("asset/graphic/testStage_died.png");
		bgm = rseLoad.loadMusic("asset/music/testStage_died.ogg");
		audio.music.playMusic(bgm, -1);
	}

	if (enemyDead == MAX_TEST_ENEMY) {
		stageEnding = true;
	}

}

int TestStage::flow() {

	// ** Acts as a flow controller ** //

	update();

	if (!stageClear && !player.getIsDead()) {

		if(!gamePaused) {

			if (stageOpening) {
				stageOpening = player.playerEntrance();
			}
			else if (stageEnding) {
				if (player.playerExit()) {
					stageClear = true;
					audio.music.stopMusic();
					background.bgImg = rseLoad.loadTextureImage("asset/graphic/testStage_end.png");
					bgm = rseLoad.loadMusic("asset/music/testStage_end.flac");
					audio.music.playMusic(bgm, -1);
				}
			}
			else {
				enemyAI();
				player.update();
				collisionDetection();
			}

			if (kbd.isPressed(SDL_SCANCODE_ESCAPE)) {
				gamePaused = true;
			}

		}
		else {

			//quick solution, tired of coding this game

			int check = subMenu->flow();

			if (check == 1) {
				gamePaused = false;
				subMenu->reset();
			}
			else if (check == -1) {
				subMenu->reset();
				return -1;
			}

		}

	}
	else if (player.getIsDead()) {

		SDL_RenderCopy(wnd.renderer, background.bgImg, NULL, NULL);
		
		if (kbd.isPressed(SDL_SCANCODE_ESCAPE)) {
			return -1;
		}

	}
	else if (stageClear && !player.getIsDead()) {

		SDL_RenderCopy(wnd.renderer, background.bgImg, NULL, NULL);
		
		if (kbd.isPressed(SDL_SCANCODE_ESCAPE)) {
			return -1;
		}

	}

	return 0; //Continue stage

}

bool TestStage::getStageClear() {
	return stageClear;
}

void TestStage::Background::scroll(GameWindow& wnd) {

	//Scrolls background
	scrollingOffset += 3;

	if (scrollingOffset > bgHeight) {
		scrollingOffset = 0;
	}

	render(0, scrollingOffset, wnd);
	render(0, scrollingOffset - bgHeight, wnd);

}

void TestStage::Background::render(int x, int y, GameWindow& wnd) {

	//Display background

	bgRect.x = x;
	bgRect.y = y;
	bgRect.w = bgWidth;
	bgRect.h = bgHeight;

	SDL_RenderCopy(wnd.renderer, bgImg, NULL, &bgRect);

}

void TestStage::Background::clean() {
	SDL_DestroyTexture(bgImg);
	bgImg = NULL;
}

// ########### ARCHIVE ########### //
/*
void TestStage::clean() {

	// ** Destroy all objects' data ** //

	std::cout << "Cleaning enemy objects" << std::endl;

	testEnemy->clean();
	delete testEnemy;

	player.clean();

	background.clean();

}
*/