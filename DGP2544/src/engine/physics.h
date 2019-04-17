#pragma once

#include <iostream>
#include <math.h>
#include <SDL.h>

class Physics {

public:
	Physics();
	~Physics();

	bool aabb(SDL_Rect colidded, SDL_Rect colidder);

	int boundingSphere(int mainPosX, int mainPosY, int clashPosX, int clashPosY);

};