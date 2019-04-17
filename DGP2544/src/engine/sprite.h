#pragma once

#include <iostream>
#include <SDL.h>

#include "gameWindow.h"

class Sprite {

protected:

	SDL_Texture* spriteImage;

	int imageWidth;
	int imageHeight;

	SDL_Rect spriteRect;
	SDL_Rect displayRect;

	SDL_RendererFlip flip;

public:

	Sprite();
	~Sprite();

	int getPosX();
	int getPosY();

	int getImgX();
	int getImgY();

	int getDisplayW();
	int getDisplayH();

	int getImgW();
	int getImgH();

	SDL_RendererFlip getFlip();

	SDL_Texture* getImage();

	SDL_Rect getSpriteRect();
	SDL_Rect getDisplayRect();

	void setPosX(int x);
	void setPosY(int y);

	void setImgX(int x);
	void setImgY(int y);

	void setDisplayW(int w);
	void setDisplayH(int h);

	void setImgW(int w);
	void setImgH(int h);

	void setDisplayRect(int x, int y, int w, int h);
	void setSpriteRect(int x, int y, int w, int h);

	void setFlip(SDL_RendererFlip flip);

	void setImage(SDL_Texture* spriteImage);

	void display(GameWindow& wnd);
	void display(GameWindow& wnd, SDL_RendererFlip flip);
	void display(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip);

	void clean();

};