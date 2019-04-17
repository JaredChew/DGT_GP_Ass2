#include "sprite_old.h"

Sprite::Sprite() {

	spriteImage = NULL;

	sourceRect.x = NULL;
	sourceRect.y = NULL;
	sourceRect.w = NULL;
	sourceRect.h = NULL;

	destRect.x = NULL;
	destRect.y = NULL;
	destRect.w = NULL;
	destRect.h = NULL;

}

Sprite::~Sprite() {

	SDL_DestroyTexture(spriteImage);
	spriteImage = NULL;

}

int Sprite::getX() {return destRect.x; }

int Sprite::getY() { return destRect.y; }

void Sprite::setX(int x) {
	destRect.x = x;
}

void Sprite::setY(int y) {
	destRect.y = y;
}

void Sprite::setSourceW(int w) {
	destRect.w = sourceRect.w = w;
}

void Sprite::setSourceH(int h) {
	destRect.h = sourceRect.h;
}

void Sprite::setDestW(int w) {
	destRect.w = w;
}

void Sprite::setDestH(int h) {
	destRect.h = h;
}

void Sprite::setImageRenderW(int w) {
	destRect.w = w;
}

void Sprite::setImageRenderH(int h) {
	destRect.h = h;
}

void Sprite::setImageRenderDimension(int w, int h, int x, int y) {

	//destRect.w = w;
	//destRect.h = h;

	sourceRect.y = y;
	sourceRect.x = x;

}

int Sprite::getSourceW() {
	return sourceRect.w;
}

int Sprite::getSourceH() {
	return sourceRect.h;
}

int Sprite::getDestW() {
	return destRect.w;
}

int Sprite::getDestH() {
	return destRect.h;
}

void Sprite::setSourceRect(int w, int h) {
	sourceRect.w = w;
	sourceRect.h = h;
}

void Sprite::setDestRect(int w, int h) {
	destRect.w = w;
	destRect.h = h;
}

SDL_Rect Sprite::getSourceRect() {
	return sourceRect;
}

SDL_Rect Sprite::getDestRect() {
	return destRect;
}

SDL_Texture* Sprite::getSprite() { return spriteImage; }

void Sprite::setSprite(SDL_Texture* spriteImage) {
	this->spriteImage = spriteImage;
	SDL_QueryTexture(spriteImage, NULL, NULL, &sourceRect.w, &sourceRect.h);
}

void Sprite::display(GameWindow& wnd) {
	SDL_RenderCopy(wnd.renderer, spriteImage, NULL, &destRect);
}

void Sprite::display(GameWindow& wnd, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &destRect, 0.0, NULL, flip);
}

void Sprite::display(GameWindow& wnd, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(wnd.renderer, spriteImage, &sourceRect, &destRect, angle, center, flip);
}

void Sprite::clean() {

	SDL_DestroyTexture(spriteImage);
	//spriteImage = NULL;

}