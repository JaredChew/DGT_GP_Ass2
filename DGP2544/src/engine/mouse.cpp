#include "mouse.h"

Mouse::Mouse() {

	// ** Initialise everything here ** //

	mouseX = NULL;
	mouseY = NULL;

	lastClickState = NULL;
	lastHoldState = NULL;

	mousePos.last_xPos = 0;
	mousePos.last_yPos = 0;

}

Mouse::~Mouse() {
	std::cout << "Mouse object cleaned" << std::endl;
}

bool Mouse::mouseClick(int clickCode) {

	// ** Checks if mouse button is being pressed ** //

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(clickCode)) {
		lastClickState = clickCode;
		return true;
	}

	return false;

}

bool Mouse::mouseHold(int clickCode) {

	// ** Checks if mouse button is being hold ** //

	if ( ( SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(clickCode) ) && (lastHoldState == clickCode) ) {
		return true;
	}

	lastHoldState = clickCode;

	return false;

}

bool Mouse::mouseMove() {

	// ** Detect any mouse movement changes ** //

	//Gets mouse coordinates and saves them
	SDL_GetMouseState(&mouseX, &mouseY);

	if (mousePos.last_xPos != mouseX || mousePos.last_yPos != mouseY) {
		mousePos.last_xPos = mouseX;
		mousePos.last_yPos = mouseY;
		return true;
	}

	mousePos.last_xPos = mouseX;
	mousePos.last_yPos = mouseY;

	return false;

}

bool Mouse::mouseAtPos(int x, int y) {

	SDL_GetMouseState(&mouseX, &mouseY);

	mousePos.last_xPos = mouseX;
	mousePos.last_yPos = mouseY;

	if (mouseX == x && mouseY == y) {
		return true;
	}

	return false;

}

bool Mouse::mouseAtPosX(int x) {

	SDL_GetMouseState(&mouseX, NULL);

	mousePos.last_xPos = mouseX;

	if (mouseX == x) {
		return true;
	}

	return false;

}

bool Mouse::mouseAtPosY(int y) {

	SDL_GetMouseState(NULL, &mouseY);

	mousePos.last_yPos = mouseY;

	if (mouseY == y) {
		return true;
	}

	return false;

}


int Mouse::getMouseX() {
	return mouseX;
}

int Mouse::getMouseY() {
	return mouseY;
}