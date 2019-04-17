#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

#include "gameWindow.h"

class Font {
	
	public:

		GameWindow& wnd;

	private:

		TTF_Font* font;
		SDL_Surface* renderedText;

		SDL_Color color;
		SDL_Rect textRect;
		SDL_Texture* text;

	public:

		Font(GameWindow& wnd);
		~Font();

		void setFont(TTF_Font* font);
		void drawFont(std::string msg, int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b);

		//void close();

};