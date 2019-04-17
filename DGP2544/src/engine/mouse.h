#pragma once

#include <SDL.h>

#include "gameWindow.h"

#define SDL_MOUSE_RIGHT 0
#define SDL_MOUSE_MIDDLE 1
#define SDL_MOUSE_LEFT 2

class Mouse {

private:
	SDL_Event event;

	int mouseX;
	int mouseY;

	int lastClickState;
	int lastHoldState;

	struct MousePos {

		int last_xPos;
		int last_yPos;

	};

	MousePos mousePos;

public:
	Mouse();
	~Mouse();

	bool mouseClick(int clickCode);
	bool mouseHold(int clickCode);
	bool mouseMove();

	bool mouseAtPos(int x, int y);
	bool mouseAtPosX(int x);
	bool mouseAtPosY(int y);

	int getMouseX();
	int getMouseY();

};