#pragma once

#include "gameWindow.h"

class Keyboard {

private:
	GameWindow& wnd;

	int lastKeyState;

public:
	Keyboard(GameWindow& wnd);
	~Keyboard();

	bool isPressed(int keyCode);
	bool isHold(int KeyCode);
	bool checkInput(int keyCode);
	void update();

};