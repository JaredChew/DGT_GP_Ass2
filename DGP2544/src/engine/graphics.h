#pragma once

#include <SDL.h>

#include "gameWindow.h"

class Graphics {

private:
	GameWindow& wnd;

	SDL_Surface* surface;
	SDL_Rect rect;

	Uint8 r_Mask;
	Uint8 g_Mask;
	Uint8 b_Mask;

	int colour;
	int opacity;

public:
	Graphics(GameWindow& wnd);
	~Graphics();

	void setColour(int colour);
	int getColour();

	void setOpacity(int opacity);
	int getOpacity();

	void setX(int x);
	void setY(int y);
	void setW(int w);
	void setH(int h);

	int getX();
	int getY();
	int getW();
	int getH();

	void setPos(int x, int y);
	void setDimension(int w, int h);

	void reInit();
	void putPixel();
	void createPixel(int w, int h, Uint8 r_Mask, Uint8 g_Mask, Uint8 b_Mask, int opacity);

};