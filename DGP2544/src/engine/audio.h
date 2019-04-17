#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

#include "gameWindow.h"

class Audio {

private:
	GameWindow& wnd;

public:
	struct Sound {

		int playSound(Mix_Chunk* playSound, int loop);
		int playSound(Mix_Chunk* playSound, int loop, int channel);
		void pauseSound(int channel);
		void resumeSound(int channel);
		void stopSound(int channel);
		
	};

	struct Music {
		
		void playMusic(Mix_Music* playMusic, int loop);
		void pauseMusic();
		void resumeMusic();
		void stopMusic();
		
	};

	Sound sound;
	Music music;

public:
	Audio(GameWindow& wnd);
	~Audio();

	//void clean();

};