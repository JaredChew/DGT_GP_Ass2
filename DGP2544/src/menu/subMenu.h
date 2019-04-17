#pragma once

#include <iostream>
#include <SDL.h>

#include "../engine/gameWindow.h"
#include "../engine/keyboard.h"
#include "../engine/resourceLoader.h"

class SubMenu {

private:
	GameWindow& wnd;
	ResourceLoader& rseLoad;
	Keyboard& kbd;

private:
	int navigation;
	int pressDelay;
	int pressDelayCount;

	SDL_Texture* background;
	//SDL_Rect background_rect;

public:
	SubMenu(GameWindow& wnd, Keyboard& kbd, ResourceLoader& rseLoad);
	~SubMenu();

	int flow();
	void reset();

};