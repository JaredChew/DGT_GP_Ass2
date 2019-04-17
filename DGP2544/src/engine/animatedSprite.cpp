#include "animatedSprite.h"

AnimatedSprite::AnimatedSprite() : Sprite() {

	columns = NULL;

	animWidth = NULL;
	animHeight = NULL;
	maxFrame = NULL;
	frameDelay = NULL;
	currentFrame = NULL;
	frameCounter = NULL;
	direction = NULL;

}

AnimatedSprite::~AnimatedSprite() { }

int AnimatedSprite::getDirection() {

	return direction;

}

void AnimatedSprite::setDirection(int direction) {

	this->direction = direction;

}

int AnimatedSprite::getFrameWidth() {

	return animWidth;

}

int AnimatedSprite::getFrameHeight() {

	return animHeight;

}

void AnimatedSprite::setAnimationProperties(int animWidth, int animHeight, int maxFrame, int frameDelay, int direction) {

	this->animWidth = animWidth;
	this->animHeight = animHeight;
	this->maxFrame = maxFrame;
	this->frameDelay = frameDelay;
	currentFrame = 0; //the first frame
	frameCounter = 0; //starting counter
	this->direction = direction;

}

void AnimatedSprite::setAnimationProperties(int animWidth, int animHeight, int maxFrame, int frameDelay, int currentFrame, int frameCounter, int direction) {

	this->animWidth = animWidth;
	this->animHeight = animHeight;
	this->maxFrame = maxFrame;
	this->frameDelay = frameDelay;
	this->currentFrame = currentFrame;
	this->frameCounter = frameCounter;
	this->direction = direction;

}

void AnimatedSprite::displayAnimationOnce(GameWindow& wnd) {

	//use to extract and draw an individual frame to the screen

	frameCounter++;

	if (frameCounter > frameDelay) {
		frameCounter = 0;

		if (direction == 1)
			currentFrame++; //forward to next frame
		else
			currentFrame--; //backward to previous frame
	}

	// !! Easy solution, too tired of coding this game !! //

	if (direction == 1) {
		if (currentFrame < maxFrame - 1) //currentFrame > maxFrame - 1
			extractImageFrame(wnd, currentFrame);
		//currentFrame = 0;
	}
	else {
		if (currentFrame > 0) //currentFrame < 0
			extractImageFrame(wnd, currentFrame);
		//currentFrame = maxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	//extractImageFrame(wnd, currentFrame);

}

void AnimatedSprite::displayAnimation(GameWindow& wnd) {

	//use to extract and draw an individual frame to the screen

	frameCounter++;

	if (frameCounter > frameDelay) {
		frameCounter = 0;

		if (direction == 1)
			currentFrame++; //forward to next frame
		else
			currentFrame--; //backward to previous frame
	}

	if (direction == 1) {
		if (currentFrame < maxFrame - 1) //currentFrame > maxFrame - 1
		currentFrame = 0;
	}
	else {
		if (currentFrame > 0) //currentFrame < 0
		currentFrame = maxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	extractImageFrame(wnd, currentFrame);

}

void AnimatedSprite::displayAnimation(GameWindow& wnd, double angle, SDL_Point* center) {

	//use to extract and draw an individual frame to the screen

	frameCounter++;

	if (frameCounter > frameDelay) {
		frameCounter = 0;

		if (direction == 1)
			currentFrame++; //forward to next frame
		else
			currentFrame--; //backward to previous frame
	}

	if (direction == 1) {
		if (currentFrame < maxFrame - 1) //currentFrame > maxFrame - 1
			currentFrame = 0;
	}
	else {
		if (currentFrame > 0) //currentFrame < 0
			currentFrame = maxFrame - 1;
	}

	//use algorithm to extract the image out from sprite image
	extractImageFrame(wnd, currentFrame);

}

void AnimatedSprite::extractImageFrame(GameWindow& wnd, int frame) {

	//get total column from the sprite image
	columns = imageWidth / animWidth;

	//key part to extract the image from sprite sheet
	sourceRect.y = (frame / columns) * spriteRect.h;
	sourceRect.x = (frame % columns) * spriteRect.w;
	sourceRect.w = spriteRect.w;
	sourceRect.h = spriteRect.h;

	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &displayRect, 0.0, NULL, flip);

}

void AnimatedSprite::extractImageFrame(GameWindow& wnd, int frame, double angle, SDL_Point* center) {

	//get total column from the sprite image
	columns = imageWidth / animWidth;

	//key part to extract the image from sprite sheet
	sourceRect.y = (frame / columns) * spriteRect.h;
	sourceRect.x = (frame % columns) * spriteRect.w;
	sourceRect.w = spriteRect.w;
	sourceRect.h = spriteRect.h;

	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &displayRect, angle, center, flip);

}