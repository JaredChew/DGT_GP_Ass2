#include <SDL.h>
#include <iostream>

#include "keyboard_old.h"

Keyboard::Keyboard(GameWindow& wnd) : wnd(wnd) {

	// ** Initialise everything here ** //

	lastKeyState = NULL;

}

Keyboard::~Keyboard() { }

bool Keyboard::isPressed(int keyCode) {

	// ** Checks if key is being pressed ** //

	if (checkInput(keyCode)) {
		lastKeyState = keyCode;
		return true;
	}

	return false;
	
}

bool Keyboard::isHold(int keyCode) {

	// ** Checks if key is being hold ** //

	if (checkInput(keyCode)) {

		if (lastKeyState == keyCode) {
			//std::cout << keyCode + "key is being hold" << std::endl;
			return true;
		}

		lastKeyState = keyCode;

	}

	return false;

}

bool Keyboard::checkInput(int keyCode) {

	// ** Checks if pressed key matches the intended key to be pressed ** //

	while (SDL_PollEvent(&wnd.event)) {

		if (wnd.event.key.keysym.sym == keyCode) {
			return true;
		}

	}

	return false;

}

void Keyboard::update() {

	// ** Checks if key is still being pressed ** //

	while (SDL_PollEvent(&wnd.event)) {

		if (wnd.event.key.keysym.sym != lastKeyState) {
			lastKeyState = NULL;
		}

	}

}