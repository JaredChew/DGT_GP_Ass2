#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "../engine/gameWindow.h"
#include "../engine/keyboard.h"
#include "../engine/resourceLoader.h"
#include "../engine/audio.h"

#define MAX_BUTTONS 2
#define MM_START_GAME 1
#define MM_QUIT_GAME 2

class MainMenu {

private:
	GameWindow& wnd;
	Keyboard& kbd;
	ResourceLoader& rseLoad;
	Audio& audio;

private:
	int button;
	int buttonSelect;
	int buttonPressDelay;
	int buttonPressDelayCount;

	SDL_Texture* background;
	//SDL_Rect background_rect;

	SDL_Texture* strtGameButton;
	SDL_Texture* strtGameButtonSelected;
	SDL_Rect strtGameButton_rect;

	SDL_Texture* quitGameButton;
	SDL_Texture* quitGameButtonSelected;
	SDL_Rect quitGameButton_rect;

	Mix_Music* bgm;
	Mix_Chunk* navigateSound;

private:
	void display();
	void naviagte();

public:
	MainMenu(GameWindow& wnd, Keyboard& kbd, ResourceLoader& rseLoad, Audio& audio);
	~MainMenu();

	int flow();

};