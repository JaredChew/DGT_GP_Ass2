#pragma once

#include <SDL.h>

#include "sprite_old.h"

//Sub class of Sprite2D class
class AnimatedSprite : public Sprite {

	private:

		//int animFrameWidth;        //sprite frame width
		//int animFrameHeight;       //sprite frame height
		int animMaxFrame;     //total sprite in an image
		int animFrameDelay; //existing frame draw to the screen
		int animCurrentFrame;   //how long to change to next frame
		int animFrameCounter; //incremental purpose
		int animDirection;    //forward or backward

	private:
		void extractImageFrame(int frame, GameWindow& wnd);

	public:

		AnimatedSprite();
		~AnimatedSprite();

		void setDirection(int animDirection);
		void setAnimationProperies(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection); //int animFrameWidth, int animFrameHeight, 

		int getDirection();
		//int getFrameWidth();
		//int getFrameHeight();

		//use to extract and draw an individual frame to the screen
		void displayAnimation(GameWindow& wnd);
		void displayAnimation(GameWindow& wnd, SDL_RendererFlip flip);
		void displayAnimation(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip);
		void extractImageFrame(int frame, GameWindow& wnd, SDL_RendererFlip flip);
		void extractImageFrame(int frame, GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip);


};