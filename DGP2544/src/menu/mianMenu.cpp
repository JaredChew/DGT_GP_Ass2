#include "mainMenu.h"

MainMenu::MainMenu(GameWindow& wnd, Keyboard& kbd, ResourceLoader& rseLoad, Audio& audio) : wnd(wnd), kbd(kbd), rseLoad(rseLoad), audio(audio) {

	button = 1;
	buttonSelect = 0;
	buttonPressDelay = 10;
	buttonPressDelayCount = 0;

	background = rseLoad.loadTextureImage("asset/graphic/mainMenu.png");
	
	strtGameButton = rseLoad.loadTextureImage("asset/graphic/startGame_button.png"); 
	strtGameButtonSelected = rseLoad.loadTextureImage("asset/graphic/startGame_buttonSelected.png");

	quitGameButton = rseLoad.loadTextureImage("asset/graphic/quitGame_button.png");
	quitGameButtonSelected = rseLoad.loadTextureImage("asset/graphic/quitGame_buttonSelected.png");

	strtGameButton_rect.x = 20;
	strtGameButton_rect.y = HEIGHT / 2;
	strtGameButton_rect.w = 213;
	strtGameButton_rect.h = 50;

	quitGameButton_rect.x = 20;
	quitGameButton_rect.y = (strtGameButton_rect.y + strtGameButton_rect.h) + 10;
	quitGameButton_rect.w = 213;
	quitGameButton_rect.h = 50;

	bgm = rseLoad.loadMusic("asset/music/mainMenu.flac");
	audio.music.playMusic(bgm, -1);

	navigateSound = rseLoad.loadSound("asset/sound/buttonNavigate.wav"); 

}

MainMenu::~MainMenu() {

	SDL_DestroyTexture(strtGameButton);
	strtGameButton = NULL;

	SDL_DestroyTexture(strtGameButtonSelected);
	strtGameButtonSelected = NULL;

	SDL_DestroyTexture(quitGameButton);
	quitGameButton = NULL;

	SDL_DestroyTexture(quitGameButtonSelected);
	quitGameButtonSelected = NULL;

	Mix_FreeMusic(bgm);
	bgm = NULL;

	Mix_FreeChunk(navigateSound);
	navigateSound = NULL;

}

void MainMenu::display() {

	SDL_RenderCopy(wnd.renderer, background, NULL, NULL);

	//Controls which button image to show when hovered and not hovered

	if (button == MM_START_GAME) { SDL_RenderCopy(wnd.renderer, strtGameButtonSelected, NULL, &strtGameButton_rect); }
	else { SDL_RenderCopy(wnd.renderer, strtGameButton, NULL, &strtGameButton_rect); }

	if(button == MM_QUIT_GAME) { SDL_RenderCopy(wnd.renderer, quitGameButtonSelected, NULL, &quitGameButton_rect); }
	else { SDL_RenderCopy(wnd.renderer, quitGameButton, NULL, &quitGameButton_rect); }

}

int MainMenu::flow() {

	naviagte();
	display();

	if (buttonSelect == MM_QUIT_GAME) {
		return -2;
	}

	return buttonSelect;

}

void MainMenu::naviagte() {

	if ((kbd.isPressed(SDL_SCANCODE_W) || kbd.isPressed(SDL_SCANCODE_UP)) && buttonPressDelayCount == 0) { //Moves up
		buttonPressDelayCount++;
		audio.sound.playSound(navigateSound, 0);
		button--;
	}
	else if ((kbd.isPressed(SDL_SCANCODE_S) || kbd.isPressed(SDL_SCANCODE_DOWN)) && buttonPressDelayCount == 0) { //Moves down
		buttonPressDelayCount++;
		audio.sound.playSound(navigateSound, 0);
		button++; 
	}
	else if (kbd.isPressed(SDL_SCANCODE_RETURN) && buttonPressDelayCount == 0) { //Selects button //(kbd.isPressed(SDL_SCANCODE_SPACE)) || 
		buttonSelect = button;
	}

	//Control button navigation within number of buttons
	if (button == 0) {
		button = MAX_BUTTONS;
	}
	else if (button > MAX_BUTTONS) {
		button = 1;
	}

	if (buttonPressDelayCount == buttonPressDelay) { buttonPressDelayCount = 0; }
	else if (buttonPressDelayCount != 0) { buttonPressDelayCount++; }

}