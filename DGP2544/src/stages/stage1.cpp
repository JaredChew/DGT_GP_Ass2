#include "stage1.h"

Stage_1::Stage_1(GameWindow& wnd, ResourceLoader& rseLoad, Player& player, Audio& audio, Physics& physics, Keyboard& kbd) : wnd(wnd), rseLoad(rseLoad), player(player), audio(audio), physics(physics), kbd(kbd) {

	// ** Initialise everything here ** //

	std::cout << "\nSetting up Stage 1" << std::endl;

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

	bgm = rseLoad.loadMusic("asset/music/stage1.flac");
	audio.music.playMusic(bgm, -1);

	gameOver_bgm = rseLoad.loadMusic("asset/music/gameOver.flac");

	//Load background
	background.bgImg = rseLoad.loadTextureImage("asset/graphic/backgroundScroll.bmp");

	//Initialise enemy

	int xPosAuto = 0, yPosAuto = 5;

	for (int i = 0; i < MAX_MINI_ENEMY; i++) {

		miniEnemy[i] = new MiniEnemy(wnd, rseLoad, audio, physics);

		miniEnemy[i]->setPosition(xPosAuto, yPosAuto);

		if (i == 4) {
			miniEnemy[i]->initPowerUp(SHIELD);
		}

		if (i == 4) {
			yPosAuto += (miniEnemy[i]->getHeight()) + 50;
			xPosAuto += miniEnemy[i]->getWidth() + 30;
			miniEnemy[i]->setAutoMoveRight(true);
		}
		else if (i > 4) {
			xPosAuto -= (miniEnemy[i]->getWidth() + 30);
			miniEnemy[i]->setAutoMoveLeft(true);
		}
		else {
			xPosAuto += miniEnemy[i]->getWidth() + 30;
			miniEnemy[i]->setAutoMoveRight(true);
		}

	}

	font = new Font(wnd);
	font->setFont(rseLoad.loadFont("asset/font/consolas.ttf", 100));

}

Stage_1::~Stage_1() {

	// ** Destroy all objects' data ** //

	delete subMenu;
	subMenu = NULL;

	background.clean();

	Mix_FreeMusic(bgm);
	bgm = NULL;

	Mix_FreeMusic(gameOver_bgm);
	bgm = NULL;

	delete font;
	font = NULL;

	scoreText.clear();

	for (int i = 0; i < MAX_MINI_ENEMY; i++) {
		delete miniEnemy[i];
		miniEnemy[i] = NULL;
	}

	std::cout << "Stage 1 objects cleaned" << std::endl;

}

void Stage_1::update() {

	// ** Update anything related to this class only ** //

	background.scroll(wnd);

}

void Stage_1::enemyAI() {

	for (int i = 0; i < MAX_MINI_ENEMY; i++) {

		//Changes direction when touch window border
		if ((miniEnemy[i]->getPosX() + miniEnemy[i]->getWidth()) > WIDTH || miniEnemy[i]->getPosX() < 0) {
			miniEnemy[i]->setAutoMoveLeft(!miniEnemy[i]->getAutoMoveLeft());
			miniEnemy[i]->setAutoMoveRight(!miniEnemy[i]->getAutoMoveRight());
		}

		//Moves enemy
		if (miniEnemy[i]->getAutoMoveRight()) {
			miniEnemy[i]->moveRight();
		}
		else if (miniEnemy[i]->getAutoMoveLeft()) {
			miniEnemy[i]->moveLeft();
		}

		//Display position update and shoots bullet
		miniEnemy[i]->update();

	}

}

void Stage_1::collisionDetection() {

	enemyDead = 0;

	for (int enmy = 0; enmy < MAX_MINI_ENEMY; enmy++) {

		//checks if enemy is being hit
		for (int i = 0; i < PLAYER_MAX_BULLET; i++) {

			//Check if player bullet is hitting enemy
			if (physics.aabb(miniEnemy[enmy]->getEnemyRect(), player.getBulletRect(i)) && player.getIsBulletColliderOn(i) && !miniEnemy[enmy]->getIsDead()) {

				player.bulletHitsEnemy(i);
				miniEnemy[enmy]->enemyIsHit(player.getBulletDamage());

				if (miniEnemy[enmy]->getHP() <= 0) {
					player.updatePlayerScore(miniEnemy[enmy]->getKillScore()); //check if dead
				}

			}

		}

		
		for (int i = 0; i < ENEMY_MAX_BULLET; i++) {

			//checks if enemy bullet is hitting player
			if (physics.aabb(player.getPlayerRect(), miniEnemy[enmy]->getBulletRect(i)) && miniEnemy[enmy]->getIsBulletColliderOn(i)) {
				player.playerIsHit();
				miniEnemy[enmy]->bulletHitsPlayer(i);
			}

		}

		//Checks if power up hits player
		if (miniEnemy[enmy]->getPowerUpIsDeployed() && physics.aabb(player.getPlayerRect(), miniEnemy[enmy]->getPowerUpRect())) {
			player.playerGetsPowerUp(miniEnemy[enmy]->getPowerUpType());
			miniEnemy[enmy]->powerUpHitsPlayer();
		}

		//counts number of enemies dead
		if (miniEnemy[enmy]->getIsDead()) {
			enemyDead++;
		}

	}

	if (player.getIsDead()) {

		audio.music.stopMusic();
		background.bgImg = rseLoad.loadTextureImage("asset/graphic/gameOver.png");
		audio.music.playMusic(gameOver_bgm, -1);

		scoreText.str("");
		scoreText << "Final Score: " << (player.getPlayerScore() + (player.getLives() * 1000) + (player.getShields() * 500));

	}

	if (enemyDead == MAX_MINI_ENEMY) {
		stageEnding = true;
	}

}

int Stage_1::flow() {

	// ** Acts as a flow controller ** //

	update();

	if (!stageClear && !player.getIsDead()) {

		if (!gamePaused) {

			if (stageOpening) {
				stageOpening = player.playerEntrance();
			}
			else if (stageEnding) {
				if (player.playerExit()) { stageClear = true; }
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

		font->drawFont(scoreText.str(), (WIDTH / 2) - 150, (HEIGHT / 2) - 10 + 25, 300, 110, 255, 255, 255);

		if (kbd.isPressed(SDL_SCANCODE_ESCAPE)) {
			return -1; //return to main menu
		}

	}
	else if (stageClear && !player.getIsDead()) {
		return 1; //proceed to next stage
	}

	return 0; //Continue stage

}

bool Stage_1::getStageClear() {
	return stageClear;
}

void Stage_1::Background::scroll(GameWindow& wnd) {

	//Scrolls background
	scrollingOffset += 3;

	if (scrollingOffset > bgHeight) {
		scrollingOffset = 0;
	}

	render(0, scrollingOffset, wnd);
	render(0, scrollingOffset - bgHeight, wnd);

}

void Stage_1::Background::render(int x, int y, GameWindow& wnd) {

	//Display background

	bgRect.x = x;
	bgRect.y = y;
	bgRect.w = bgWidth;
	bgRect.h = bgHeight;

	SDL_RenderCopy(wnd.renderer, bgImg, NULL, &bgRect);

}

void Stage_1::Background::clean() {
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