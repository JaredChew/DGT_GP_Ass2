#include "audio.h"

Audio::Audio(GameWindow& wnd) : wnd(wnd) {

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Error", "SDL Mixer failed to initialise", NULL);
		std::cerr << "SDL failed to initialise Mixer library" << std::endl;

		wnd.forceQuit();

	}

}

Audio::~Audio() {

	Mix_CloseAudio();

	std::cout << "Audio libraries closed" << std::endl;

} 

// ** SOUND ** //

int Audio::Sound::playSound(Mix_Chunk* playSound, int loop) {

	//Plays the audio and returns the channel number
	return Mix_PlayChannel(-1, playSound, loop);

}

int Audio::Sound::playSound(Mix_Chunk* playSound, int loop, int channel) {

	//Plays the audio and returns the channel number
	return Mix_PlayChannel(channel, playSound, loop);

}

void Audio::Sound::pauseSound(int channel) {
	Mix_Pause(channel);
}

void Audio::Sound::resumeSound(int channel) {
	Mix_Resume(channel);
}

void Audio::Sound::stopSound(int channel) {
	Mix_HaltChannel(channel);
}

// ** MUSIC ** //

void Audio::Music::playMusic(Mix_Music* playMusic, int loop) {
	Mix_PlayMusic(playMusic, loop);
}

void Audio::Music::pauseMusic() {
	Mix_PauseMusic();
}

void Audio::Music::resumeMusic() {
	Mix_ResumeMusic();
}

void Audio::Music::stopMusic() {
	Mix_HaltMusic();
}

// ########### ARCHIVE ########### //
/*
void Audio::clean() {
	Mix_CloseAudio();
}
*/