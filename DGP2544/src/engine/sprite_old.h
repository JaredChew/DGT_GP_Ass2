#pragma once

#include <iostream>
#include <SDL.h>

#include "gameWindow.h"

class Sprite {

protected:

	SDL_Texture* spriteImage;

	SDL_Rect sourceRect;
	SDL_Rect destRect;

	public:

		Sprite();
		~Sprite();

		int getX();
		int getY();

		int getSourceW();
		int getSourceH();

		int getDestW();
		int getDestH();

		SDL_Rect getSourceRect();
		SDL_Rect getDestRect();

		SDL_Texture* getSprite();

		void setX(int x);
		void setY(int y);

		void setSourceW(int w);
		void setSourceH(int h);

		void setDestW(int w);
		void setDestH(int h);

		void setSourceRect(int w, int h);
		void setDestRect(int w, int h);

		void setImageRenderW(int w);
		void setImageRenderH(int h);
		void setImageRenderDimension(int w, int h, int x, int y);

		void setSprite(SDL_Texture* spriteImage);

		void display(GameWindow& wnd);
		void display(GameWindow& wnd, SDL_RendererFlip flip);
		void display(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip);
		
		void clean();

};