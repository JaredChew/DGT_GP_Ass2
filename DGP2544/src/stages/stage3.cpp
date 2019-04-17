#include "stage3.h"

Stage_3::Stage_3(GameWindow& wnd, ResourceLoader& rseLoad, Player& player, Audio& audio, Physics& physics, Keyboard& kbd) : wnd(wnd), rseLoad(rseLoad), player(player), audio(audio), physics(physics), kbd(kbd) {

	// ** Initialise everything here ** //

	std::cout << "\nSetting up Stage 3" << std::endl;

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

	bgm = rseLoad.loadMusic("asset/music/stage3.flac");
	audio.music.playMusic(bgm, -1);

	victory_bgm = rseLoad.loadMusic("asset/music/victory.flac");
	gameOver_bgm = rseLoad.loadMusic("asset/music/gameOver.flac");

	//Load background
	background.bgImg = rseLoad.loadTextureImage("asset/graphic/background3_scroll.png");

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

	for (int i = 0; i < MAX_MINI_ENEMY; i += 2) {

		if (miniEnemy[i]->getAutoMoveRight()) {
			miniEnemy[i]->setAutoMoveRight(false);
		}
		else {
			miniEnemy[i]->setAutoMoveLeft(false);
		}

		miniEnemy[i]->setAutoMoveDown(true);
		//miniEnemy[i]->setEnemySpeed(5);

	}

	for (int i = 3; i < MAX_MINI_ENEMY; i += 3) {

		if (i == 3) {
			miniEnemy[i]->setAutoMoveRight(true);
		}
		else {
			miniEnemy[i]->setAutoMoveLeft(true);
		}

		miniEnemy[i]->setAutoMoveDown(true);
		//miniEnemy[i]->setEnemySpeed(5);

	}

	font = new Font(wnd);
	font->setFont(rseLoad.loadFont("asset/font/consolas.ttf", 100));

	player.positionReset();

}

Stage_3::~Stage_3() {

	// ** Destroy all objects' data ** //

	delete subMenu;
	subMenu = NULL;

	background.clean();

	Mix_FreeMusic(bgm);
	bgm = NULL;

	Mix_FreeMusic(victory_bgm);
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

	std::cout << "Stage 3 objects cleaned" << std::endl;

}

void Stage_3::update() {

	// ** Update anything related to this class only ** //

	background.scroll(wnd);

}

void Stage_3::enemyAI() {

	for (int i = 0; i < MAX_MINI_ENEMY; i++) {

		if (i == 3 || i == 9) {
			//change enemy direction when touches border
			if ((miniEnemy[i]->getPosX() + miniEnemy[i]->getWidth()) > WIDTH || miniEnemy[i]->getPosX() < 0) {
				miniEnemy[i]->setAutoMoveLeft(!miniEnemy[i]->getAutoMoveLeft());
				miniEnemy[i]->setAutoMoveRight(!miniEnemy[i]->getAutoMoveRight());
			}
		}
		else {
			//reposition enemy when out of border
			if (miniEnemy[i]->getPosX() > WIDTH) {
				miniEnemy[i]->setPosX(0);
			}
			else if (miniEnemy[i]->getPosX() + miniEnemy[i]->getWidth() < 0) {
				miniEnemy[i]->setPosX(WIDTH);
			}
		}

		if (miniEnemy[i]->getPosY() > HEIGHT) {
			miniEnemy[i]->setPosition(rand() % (WIDTH - miniEnemy[i]->getWidth()), 0 - miniEnemy[i]->getHeight());
			miniEnemy[i]->setEnemySpeed(3);
		}

		//Moves enemy
		if (miniEnemy[i]->getAutoMoveRight()) {
			miniEnemy[i]->moveRight();
		}
		else if (miniEnemy[i]->getAutoMoveLeft()) {
			miniEnemy[i]->moveLeft();
		}

		if (miniEnemy[i]->getAutoMoveDown()) {
			miniEnemy[i]->moveDown();
		}

		//Mini enemy flys away faster after passing player
		if (miniEnemy[i]->getPosY() >= player.getPosY() && miniEnemy[i]->getAutoMoveDown()) {
			miniEnemy[i]->setEnemySpeed(15);
		}

		//Display position update and shoots bullet
		miniEnemy[i]->update();

	}

}

void Stage_3::collisionDetection() {

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

int Stage_3::flow() {

	// ** Acts as a flow controller ** //

	update();

	if (!stageClear && !player.getIsDead()) {

		if (!gamePaused) {

			if (stageOpening) {
				stageOpening = player.playerEntrance();
			}
			else if (stageEnding) {

				if (player.playerExit()) {

					stageClear = true;
					audio.music.stopMusic();
					background.bgImg = rseLoad.loadTextureImage("asset/graphic/gameEnd.png");
					audio.music.playMusic(victory_bgm, -1);

					scoreText.str("");
					scoreText << "Final Score: " << (player.getPlayerScore() + (player.getLives() * 1000) + (player.getShields() * 500));

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

		font->drawFont(scoreText.str(), (WIDTH / 2) - 150, (HEIGHT / 2) - 10 + 25, 300, 110, 255, 255, 255);

		if (kbd.isPressed(SDL_SCANCODE_ESCAPE)) {
			return -1;
		}

	}
	else if (stageClear && !player.getIsDead()) {

		SDL_RenderCopy(wnd.renderer, background.bgImg, NULL, NULL);

		font->drawFont(scoreText.str(), (WIDTH / 2) - 150, (HEIGHT / 2) + 10, 300, 110, 255, 255, 255);

		if (kbd.isPressed(SDL_SCANCODE_SPACE)) {
			return -1;
		}

	}

	return 0; //Continue stage

}

bool Stage_3::getStageClear() {
	return stageClear;
}

void Stage_3::Background::scroll(GameWindow& wnd) {

	//Scrolls background
	scrollingOffset += 4;

	if (scrollingOffset > bgHeight) {
		scrollingOffset = 0;
	}

	render(0, scrollingOffset, wnd);
	render(0, scrollingOffset - bgHeight, wnd);

}

void Stage_3::Background::render(int x, int y, GameWindow& wnd) {

	//Display background

	bgRect.x = x;
	bgRect.y = y;
	bgRect.w = bgWidth;
	bgRect.h = bgHeight;

	SDL_RenderCopy(wnd.renderer, bgImg, NULL, &bgRect);

}

void Stage_3::Background::clean() {
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