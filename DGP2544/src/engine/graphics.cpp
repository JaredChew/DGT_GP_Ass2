#include "graphics.h"

Graphics::Graphics(GameWindow& wnd) : wnd(wnd) {

	surface = NULL;
	colour = NULL;

}

Graphics::~Graphics() {

	surface = NULL;

	std::cout << "Graphics object cleaned" << std::endl;

}

void Graphics::setColour(int colour) {
	this->colour = colour;
	reInit();
}

int Graphics::getColour() {
	return colour;
}

void Graphics::setOpacity(int opacity) {
	this->opacity = opacity;
	reInit();
}

int Graphics::getOpacity() {
	return opacity;
}

void Graphics::setX(int x) {
	rect.x = x;
}

void Graphics::setY(int y) {
	rect.y = y;
}

void Graphics::setW(int w) {
	rect.w = w;
	SDL_FreeSurface(surface);
	reInit();
}

void Graphics::setH(int h) {
	rect.h = h;
	SDL_FreeSurface(surface);
	reInit();
}

void Graphics::setDimension(int w, int h) {
	rect.w = w;
	rect.h = h;
}

void Graphics::setPos(int x, int y) {
	rect.x = x;
	rect.y = y;
}

int Graphics::getX() {
	return rect.x;
}

int Graphics::getY() {
	return rect.y;
}

int Graphics::getW() {
	return rect.w;
}

int Graphics::getH() {
	return rect.h;
}

void Graphics::reInit() {
	SDL_FreeSurface(surface);
	surface = SDL_CreateRGBSurface(NULL, rect.w, rect.h, 32, r_Mask, g_Mask, b_Mask, opacity);
}

void Graphics::putPixel() {

	SDL_FillRect(surface, NULL, colour);

	SDL_RenderCopy(wnd.renderer, SDL_CreateTextureFromSurface(wnd.renderer, surface), NULL, &rect);

}

void Graphics::createPixel(int w, int h, Uint8 r_Mask, Uint8 g_Mask, Uint8 b_Mask, int opacity) {

	rect.w = w;
	rect.h = h;

	this->r_Mask = r_Mask;
	this->g_Mask = g_Mask;
	this->b_Mask = b_Mask;

	this->opacity = opacity;

	surface = SDL_CreateRGBSurface(NULL, w, h, 32, r_Mask, g_Mask, b_Mask, opacity);

}