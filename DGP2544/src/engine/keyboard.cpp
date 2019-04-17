#include "keyboard.h"

Keyboard::Keyboard() {

	// ** Initialise everything here ** //

	kbdInput = (Uint8*)SDL_GetKeyboardState(NULL);

	lastKeyState = NULL;
	lastHoldState = NULL;

	delayPress = 10;
	delayPressCounter = 0;

}

Keyboard::~Keyboard() {

	kbdInput = NULL;

	std::cout << "Keyboard object cleaned" << std::endl;

}

bool Keyboard::isPressed(int keyCode) {

	// ** Checks if key is being pressed ** //

	if (kbdInput[keyCode]) {
		lastKeyState = keyCode;
		return true;
	}

	return false;

}

bool Keyboard::isHold(int keyCode) {

	// ** Checks if key is being hold ** //

	if (kbdInput[keyCode] && lastHoldState == keyCode) {
		//std::cout << keyCode + "key is being hold" << std::endl;
		return true;
	}

	lastHoldState = keyCode;

	return false;

}