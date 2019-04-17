#include "resourceLoader.h"

ResourceLoader::ResourceLoader(GameWindow& wnd) : wnd(wnd) {  }

ResourceLoader::~ResourceLoader() {

	IMG_Quit();
	TTF_Quit();

	std::cout << "ResourceLoader libraries closed" << std::endl;

}

SDL_Surface* ResourceLoader::loadSurfaceImage(const char* imageFileDir) {

	//** Load image and apply alpha masking **//

	SDL_Surface* temp_Image = IMG_Load(imageFileDir);

	std::string fileExtension = imageFileDir;

	if (temp_Image == NULL) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Failed to load image", NULL);
		std::cerr << "\nSDL failed to load image at: " << imageFileDir << std::endl;

		wnd.forceQuit();
		//return NULL;

	}

	if (fileExtension.substr(fileExtension.length() - 3) != "png") { // == "bmp"

		//create optimised image using current image
		temp_Image = SDL_ConvertSurface(temp_Image, wnd.backbuffer->format, 0);

		//Set transparency

		Uint32 colourKey = SDL_MapRGB(temp_Image->format, 255, 0, 255);

		//update system with transparency colour
		SDL_SetColorKey(temp_Image, SDL_TRUE, colourKey);

	}

	return temp_Image;

}

SDL_Texture* ResourceLoader::loadTextureImage(const char* imageFileDir) {

	//** Load image and apply alpha masking **//

	SDL_Surface* temp_Image = IMG_Load(imageFileDir);

	std::string fileExtension = imageFileDir;

	if (temp_Image == NULL) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Failed to load image", NULL);
		std::cerr << "\nSDL failed to load image at: " << imageFileDir << std::endl;

		wnd.forceQuit();
		//return NULL;

	}

	if (fileExtension.substr(fileExtension.length() - 3) != "png") { // == "bmp"

		//create optimised image using current image
		temp_Image = SDL_ConvertSurface(temp_Image, wnd.backbuffer->format, 0);

		//Set transparency

		Uint32 colourKey = SDL_MapRGB(temp_Image->format, 255, 0, 255);

		//update system with transparency colour
		SDL_SetColorKey(temp_Image, SDL_TRUE, colourKey);

		fileExtension = "";
		
	}

	return SDL_CreateTextureFromSurface(wnd.renderer, temp_Image);

}

Mix_Chunk* ResourceLoader::loadSound(char* filename) {


	Mix_Chunk* soundTemp = Mix_LoadWAV(filename);

	if (Mix_LoadWAV(filename) == NULL) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Fail to load Sound Files!", NULL);
		std::cerr << "\nSDL failed to load sound at: " << filename << std::endl;

		wnd.forceQuit();
		//return NULL;

	}

	return soundTemp;

}

Mix_Music* ResourceLoader::loadMusic(char* filename) {

	Mix_Music* musicTemp = Mix_LoadMUS(filename);

	if (musicTemp == NULL) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "Fail to load music Files!", NULL);
		std::cerr << "\nSDL failed to load music at: " << filename << std::endl;

		wnd.forceQuit();
		//return NULL;

	}

	return musicTemp;

}

TTF_Font* ResourceLoader::loadFont(char* fontDir, int fontSize) {

	TTF_Font* temp_font = TTF_OpenFont(fontDir, fontSize);

	if (temp_font == NULL) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL Font failed to load font", NULL);
		std::cerr << "\nSDL failed to load font at: " << fontDir << std::endl;

		wnd.forceQuit();
		//return NULL;

	}

	return temp_font;

}

// ########### ARCHIVE ########### //
/*
ResourceLoader::ResourceLoader(GameWindow& wnd) : wnd(wnd) {

	int imgFlags = IMG_INIT_PNG;

	if (!(IMG_Init(imgFlags) & imgFlags)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL failed to initialise Image extension library", NULL);
		std::cerr << "SDL failed to load Image Extension PNG library" << std::endl;
	}

}

void ResourceLoader::clean() {

	SDL_FreeSurface(temp_Image);
	IMG_Quit();

	Mix_FreeChunk(soundTemp);
	soundTemp = NULL;

	Mix_FreeMusic(musicTemp);
	musicTemp = NULL;

	TTF_CloseFont(temp_font);
	temp_font = NULL;

	TTF_Quit();

}
*/