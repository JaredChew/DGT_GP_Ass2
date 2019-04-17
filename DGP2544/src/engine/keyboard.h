#pragma once

#include <SDL.h>
#include <iostream>

class Keyboard {

private:
	Uint8* kbdInput;

	int lastKeyState;
	int lastHoldState;

	int delayPress;
	int delayPressCounter;

public:
	Keyboard();
	~Keyboard();

	bool isPressed(int keyCode);
	bool isHold(int KeyCode);

};