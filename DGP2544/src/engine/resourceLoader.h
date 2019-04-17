#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "gameWindow.h"

class ResourceLoader {

	private:
		GameWindow& wnd;

		//SDL_Surface* temp_Image;
		//Uint32 colourKey;

		//Mix_Chunk* soundTemp;
		//Mix_Music* musicTemp;

		//TTF_Font* temp_font;

		//std::string fileExtension;

	public:
		ResourceLoader(GameWindow& wnd);
		~ResourceLoader();

		SDL_Surface* loadSurfaceImage(const char* imageFileDir);
		SDL_Texture* loadTextureImage(const char* imageFileDir);

		Mix_Chunk* loadSound(char* filename);
		Mix_Music* loadMusic(char* filename);

		TTF_Font* loadFont(char* fontDir, int fontSize);

		//void clean();

};