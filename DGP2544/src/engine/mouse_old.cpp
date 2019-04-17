#include <SDL.h>

#include "mouse_old.h"

Mouse::Mouse() {

	// ** Initialise everything here ** //

	lastClickState = NULL;

	mousePos.last_xPos = 0;
	mousePos.last_yPos = 0;

}

Mouse::~Mouse() { }

bool Mouse::mouseClick(int clickCode) {

	// ** Checks if mouse button is being pressed ** //

	//event.type == SDL_KEYDOWN

	if (checkInput(clickCode)) {
		//std::cout << keyCode + "mouse button is being pressed" << std::endl;
		return true;
	}

	return false;

}

bool Mouse::mouseHold(int clickCode) {

	// ** Checks if mouse button is being hold ** //

	//event.type == SDL_KEYDOWN

	if (checkInput(clickCode)) {

		if (lastClickState == clickCode) {
			//std::cout << keyCode + "mouse button is being hold" << std::endl;
			return true;
		}

		lastClickState = clickCode;

	}

	return false;

}

bool Mouse::checkInput(int clickCode) {

	// ** Checks if pressed mouse button matches the intended mouse button to be pressed ** //

	//event.type == SDL_KEYUP

	while (SDL_PollEvent(&event)) {

		if (event.button.button == clickCode) {
			return true;
		}

	}

	return false;

}

void Mouse::update() {

	// ** Checks if mouse button is still being pressed ** //

	while (SDL_PollEvent(&event)) {

		if (event.button.button != lastClickState) {
			lastClickState = NULL;
		}

	}

}

bool Mouse::mouseMove() {

	// ** Detect any mouse movement changes ** //

	//event.type == SDL_MOUSEMOTION

	while (SDL_PollEvent(&event)) {

		if (mousePos.last_xPos != event.motion.x || mousePos.last_yPos != event.motion.y) {
			return true;
		}

	}

	return false;

}