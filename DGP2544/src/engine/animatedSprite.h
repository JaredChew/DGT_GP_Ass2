#pragma once

#include "sprite.h"

//Sub class of Sprite2D class
class AnimatedSprite : public Sprite {

private:
	//SDL_Rect destRect;
	SDL_Rect sourceRect;

	int columns;

	int animWidth;    //sprite frame width
	int animHeight;   //sprite frame height
	int maxFrame;     //total sprite in an image
	int currentFrame; //existing frame draw to the screen
	int frameDelay;   //how long to change to next frame
	int frameCounter; //incremental purpose
	int direction;    //forward or backward

public:

	//overloaded constructor
	AnimatedSprite();
	~AnimatedSprite();

	int getDirection();
	void setDirection(int d);

	int getFrameWidth();
	int getFrameHeight();

	void setAnimationProperties(int animWidth, int animHeight, int maxFrame, int frameDelay, int direction);
	void setAnimationProperties(int animWidth, int animHeight, int maxFrame, int frameDelay, int currentFrame, int frameCounter, int direction);

	//use to extract and draw an individual frame to the screen
	void displayAnimationOnce(GameWindow& wnd);
	void displayAnimation(GameWindow& wnd);
	void displayAnimation(GameWindow& wnd, double angle, SDL_Point* center);

private:
	void extractImageFrame(GameWindow& wnd, int frame);
	void extractImageFrame(GameWindow& wnd, int frame, double angle, SDL_Point* center);

};