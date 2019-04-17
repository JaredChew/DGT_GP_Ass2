#pragma once

#include "gameWindow.h"

class Mouse {

private:
	SDL_Event event;

	int lastClickState;
	
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
	bool checkInput(int clickCode);
	void update();
	bool mouseMove();

};