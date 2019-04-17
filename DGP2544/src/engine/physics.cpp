#include "physics.h"

Physics::Physics() { }

Physics::~Physics() {
	std::cout << "Physics object cleaned" << std::endl;
}

bool Physics::aabb(SDL_Rect colidded, SDL_Rect colidder) {

	//Function to perform colison detection using AABB aproach

	//perform 4 sides checking
	if (colidded.x >= colidder.x + colidder.w) { //Main object at left hitting object at right 
		return false;
	}
	if (colidded.y >= colidder.y + colidder.h) { //Main object at top hitting object at bottom
		return false;
	}
	if (colidder.x >= colidded.x + colidded.w) { //Main object at right hitting object at left
		return false;
	}
	if (colidder.y >= colidded.y + colidded.h) { //Main object at bottom hitting object at top
		return false;
	}

	return true;

}

int Physics::boundingSphere(int mainPosX, int mainPosY, int clashPosX, int clashPosY) {

	// Computes a circular distance
	return (int)sqrt((float)((mainPosX - clashPosX) * (mainPosX - clashPosX) + (mainPosY - clashPosY) * (mainPosY - clashPosY)));

}