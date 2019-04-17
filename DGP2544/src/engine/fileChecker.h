#pragma once

#include <iostream>
#include <fstream>

#include "logger.h"
#include "../game.h"

struct FileList {

	int totalFilesCount = TOTAL_FILES;

	std::string directory;
	std::ifstream file;

	void font();
	void graphic();
	void music();
	void sound();

	void result();

	FileList(Logger& log);

	private:
		Logger& log;

};

FileList::FileList(Logger& log) : log(log) { }

void FileList::result() {

	if (totalFilesCount != TOTAL_FILES) {

		std::cerr << "\nIncomplete files, the program will now terminate" << std::endl;

		std::cout << "Press ENTER to exit" << std::endl;
		std::cin.get();

		exit(-1);

	}

	std::cout << "All files validated" << std::endl;

}

void FileList::font() {

	// ** FONT FILES ** //

	directory = "asset/font/";

	file = std::ifstream((directory + "consolas.ttf").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "consolas.ttf" << std::endl;
		totalFilesCount--;
	}

}

void FileList::graphic() {

	// ** GRAPHIC FILES ** //

	directory = "asset/graphic/";

	file = std::ifstream((directory + "background.bmp").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "background.bmp" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "background2_scroll.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "background2_scroll.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "background3_scroll.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "background3_scroll.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "background3_scroll.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "background3_scroll.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "miniEnemyAnimation.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "miniEnemy.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "miniEnemy_bullet.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "miniEnemy_bullet.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "player.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "player.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "player_shields.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "player_shields.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "playerBulletAnimation.bmp").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "playerBulletAnimation.bmp" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "gameOver.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "gameOver.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "gameEnd.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "gameEnd.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "gamePause.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "gamePause.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "powerUp_shield.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "powerUp_shield.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "quitGame_button.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "quitGame_button.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "quitGame_buttonSelected.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "quitGame_buttonSelected.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "startGame_button.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "startGame_button.png" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "startGame_buttonSelected.png").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "startGame_buttonSelected.png" << std::endl;
		totalFilesCount--;
	}

}

void FileList::music() {

	// ** MUSIC FILES ** //

	directory = "asset/music/";

	file = std::ifstream((directory + "stage1.flac").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "stage1.flac" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "stage2.flac").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "stage2.flac" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "stage3.flac").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "stage3.flac" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "gameOver.flac").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "gameOver.flac" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "victory.flac").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "victory.flac" << std::endl;
		totalFilesCount--;
	}

}

void FileList::sound() {

	// ** SOUND FILES ** //

	directory = "asset/sound/";

	file = std::ifstream((directory + "enemyBulletHit.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "enemyBulletHit.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "enemyExplode.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "enemyExplode.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "enemyShoot.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "enemyShoot.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "playerBulletHit.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "playerBulletHit.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "playerExplode.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "playerExplode.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "playerShieldUp.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "playerShieldUp.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "playerShoot.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "playerShoot.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "powerUpHit.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "powerUpHit.wav" << std::endl;
		totalFilesCount--;
	}

	file = std::ifstream((directory + "buttonNavigate.wav").c_str());
	if (!file.is_open()) {
		std::cerr << "Missing file: " << directory + "buttonNavigate.wav" << std::endl;
		totalFilesCount--;
	}

}

void fileChecker(Logger& log) {

	FileList* fl = new FileList(log);

	fl->font();
	fl->graphic();
	fl->music();
	fl->sound();

	fl->result();

	delete fl;

}