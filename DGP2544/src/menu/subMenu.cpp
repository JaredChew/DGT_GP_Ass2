#include "subMenu.h"

SubMenu::SubMenu(GameWindow& wnd, Keyboard& kbd, ResourceLoader& rseLoad) : wnd(wnd), kbd(kbd), rseLoad(rseLoad) {

	navigation = 0;

	pressDelay = 10;
	pressDelayCount = 1;

	background = rseLoad.loadTextureImage("asset/graphic/gamePause.png");

}

SubMenu::~SubMenu() {

	SDL_DestroyTexture(background);
	background = NULL;

}

int SubMenu::flow() {

	SDL_RenderCopy(wnd.renderer, background, NULL, NULL);

	//Proceeds to testStage for quick testing and debug
	if (kbd.isPressed(SDL_SCANCODE_ESCAPE) && pressDelayCount == 0) {
		navigation = -1; //return to main menu
	}
	else if (kbd.isPressed(SDL_SCANCODE_BACKSPACE) && pressDelayCount == 0) {
		navigation = 1; //resume game
	}

	if (pressDelayCount == pressDelay) { pressDelayCount = 0; }
	else if (pressDelayCount != 0) { pressDelayCount++; }

	return navigation;

}

void SubMenu::reset() {
	pressDelayCount = 1;
	navigation = 0;
}