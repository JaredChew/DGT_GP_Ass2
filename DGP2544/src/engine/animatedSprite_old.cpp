#include "animatedSprite_old.h"

AnimatedSprite::AnimatedSprite() : Sprite() {

	//animFrameWidth = NULL;
	//animFrameHeight = NULL;
	animMaxFrame = NULL;
	animFrameDelay = NULL; //Frame delay untill next animation
	animCurrentFrame = NULL; //the first frame
	animFrameCounter = NULL; //starting counter
	animDirection = NULL; //Move animation forward or backward

}

AnimatedSprite::~AnimatedSprite() {

	clean();

}

void AnimatedSprite::setAnimationProperies(int animMaxFrame, int animFrameDelay, int animCurrentFrame, int animFrameCounter, int animDirection) { //int animFrameWidth, int animFrameHeight, 

	//this->animFrameWidth = animFrameWidth;
	//this->animFrameHeight = animFrameHeight;
	this->animMaxFrame = animMaxFrame;
	this->animFrameDelay = animFrameDelay;
	this->animCurrentFrame = animCurrentFrame; //the first frame
	this->animFrameCounter = animFrameCounter; //starting counter
	this->animDirection = animDirection;

}

void AnimatedSprite::setDirection(int animDirection) { this->animDirection = animDirection; }

int AnimatedSprite::getDirection() { return animDirection; }

//int AnimatedSprite::getFrameWidth() { return animFrameWidth; }

//int AnimatedSprite::getFrameHeight() { return animFrameHeight; }

void AnimatedSprite::displayAnimation(GameWindow& wnd) {

	//use to extract and draw an individual frame to the screen

	animFrameCounter++;

	if (animFrameCounter > animFrameDelay) {
		animFrameCounter = 0;

		if (animDirection == 1)
			animCurrentFrame++; //forward to next frame
		else
			animCurrentFrame--; //backward to previous frame
	}

	if (animDirection == 1) {
		if (animCurrentFrame > animMaxFrame - 1)
			animFrameCounter = 0;
	}
	else {
		if (animCurrentFrame < 0)
			animFrameCounter = animMaxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	extractImageFrame(animCurrentFrame, wnd);

}

void AnimatedSprite::displayAnimation(GameWindow& wnd, SDL_RendererFlip flip) {

	//use to extract and draw an individual frame to the screen

	animFrameCounter++;

	if (animFrameCounter > animFrameDelay) {
		animFrameCounter = 0;

		if (animDirection == 1)
			animCurrentFrame++; //forward to next frame
		else
			animCurrentFrame--; //backward to previous frame
	}

	if (animDirection == 1) {
		if (animCurrentFrame > animMaxFrame - 1)
			animFrameCounter = 0;
	}
	else {
		if (animCurrentFrame < 0)
			animFrameCounter = animMaxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	extractImageFrame(animCurrentFrame, wnd, flip);

}

void AnimatedSprite::displayAnimation(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip) {

	//use to extract and draw an individual frame to the screen

	animFrameCounter++;

	if (animFrameCounter > animFrameDelay) {
		animFrameCounter = 0;

		if (animDirection == 1)
			animCurrentFrame++; //forward to next frame
		else
			animCurrentFrame--; //backward to previous frame
	}

	if (animDirection == 1) {
		if (animCurrentFrame > animMaxFrame - 1)
			animFrameCounter = 0;
	}
	else {
		if (animCurrentFrame < 0)
			animFrameCounter = animMaxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	extractImageFrame(animCurrentFrame, wnd, angle, center, flip);

}

void AnimatedSprite::extractImageFrame(int frame, GameWindow& wnd) {

	//get total column from the sprite image
	int columns = sourceRect.w / destRect.w;

	//key part to extract the image from sprite sheet
	sourceRect.y = (frame / columns) * sourceRect.h;
	sourceRect.x = (frame % columns) * sourceRect.w;

	SDL_RenderCopy(wnd.renderer, spriteImage, &sourceRect, &destRect);

}

void AnimatedSprite::extractImageFrame(int frame, GameWindow& wnd, SDL_RendererFlip flip) {

	//get total column from the sprite image
	int columns = sourceRect.w / destRect.w;

	//key part to extract the image from sprite sheet
	sourceRect.y = (frame / columns) * sourceRect.h;
	sourceRect.x = (frame % columns) * sourceRect.w;

	SDL_RenderCopy(wnd.renderer, spriteImage, &sourceRect, &destRect);
	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &destRect, 0.0, NULL, flip);

}

void AnimatedSprite::extractImageFrame(int frame, GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip) {

	//get total column from the sprite image
	int columns = sourceRect.w / destRect.w;

	//key part to extract the image from sprite sheet
	sourceRect.y = (frame / columns) * sourceRect.h;
	sourceRect.x = (frame % columns) * sourceRect.w;

	SDL_RenderCopy(wnd.renderer, spriteImage, &sourceRect, &destRect);
	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &destRect, angle, center, flip);

}