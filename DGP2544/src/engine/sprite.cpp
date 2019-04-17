#include "sprite.h"

Sprite::Sprite() { 

	flip = SDL_FLIP_NONE;

	imageWidth = NULL;
	imageHeight = NULL;

}

Sprite::~Sprite() {

	SDL_DestroyTexture(spriteImage);
	spriteImage = NULL;

}

int Sprite::getPosX() {

	return displayRect.x;

}

int Sprite::getPosY() {

	return displayRect.y;

}

int Sprite::getImgX() {

	return spriteRect.x;

}

int Sprite::getImgY() {

	return spriteRect.y;

}

int Sprite::getDisplayW() {

	return displayRect.w;

}

int Sprite::getDisplayH() {

	return displayRect.h;

}

int Sprite::getImgW() {

	return spriteRect.w;

}

int Sprite::getImgH() {

	return spriteRect.h;

}

SDL_RendererFlip Sprite::getFlip() {

	return flip;

}

SDL_Texture* Sprite::getImage() { return spriteImage; }

SDL_Rect Sprite::getSpriteRect() {

	return spriteRect;

}

SDL_Rect Sprite::getDisplayRect() {

	return displayRect;

}


void Sprite::setPosX(int x) {

	displayRect.x = x;

}

void Sprite::setPosY(int y) {

	displayRect.y = y;

}

void Sprite::setImgX(int x) {

	spriteRect.x = x;

}

void Sprite::setImgY(int y) {

	spriteRect.y = y;

}

void Sprite::setDisplayW(int w) {

	displayRect.w = w;

}

void Sprite::setDisplayH(int h) {

	displayRect.h = h;

}

void Sprite::setImgW(int w) {

	spriteRect.w = w;

}

void Sprite::setImgH(int h) {

	spriteRect.h = h;

}

void Sprite::setDisplayRect(int x, int y, int w, int h) {

	displayRect.x = x;
	displayRect.y = y;
	displayRect.w = w;
	displayRect.h = h;

}

void Sprite::setSpriteRect(int x, int y, int w, int h) {

	spriteRect.x = x;
	spriteRect.y = y;
	spriteRect.w = w;
	spriteRect.h = h;

}

void Sprite::setFlip(SDL_RendererFlip flip) {

	this->flip = flip;

}

void Sprite::setImage(SDL_Texture* spriteImage) {

	this->spriteImage = spriteImage;

	SDL_QueryTexture(spriteImage, NULL, NULL, &imageWidth, &imageHeight);

}

void Sprite::display(GameWindow& wnd) {

	SDL_RenderCopy(wnd.renderer, spriteImage, &spriteRect, &displayRect);

}

void Sprite::display(GameWindow& wnd, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(wnd.renderer, spriteImage, &spriteRect, &displayRect, 0.0, NULL, flip);

}

void Sprite::display(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(wnd.renderer, spriteImage, &spriteRect, &displayRect, angle, center, flip);

}

void Sprite::clean() {

	SDL_DestroyTexture(spriteImage);

}