#pragma once

#include <iostream>
#include <SDL.h>

#define FPS 60
#define WINDOW_TITLE "Assignment 2"
#define WIDTH 640
#define HEIGHT 480

#include "logger.h"

class GameWindow {

	private:
		Logger& log;

	private:

		bool gameloop;

		//int width;
		//int height;
		//int fps;
		//int fullScreen;

		int frameDelay;
		int frameTime;

		SDL_Event event;

		float avgFPS;
		int countedFrames;

		char dynamicWindowTitle[80];

	public:
		SDL_Window* window;
		SDL_Surface* backbuffer;
		SDL_Renderer* renderer;

		Uint32 frameStart;

	private:
		int init();

	public:
		GameWindow(Logger& log);
		~GameWindow();

		//void destroy();
		void eventHandler();
		void update();
		void fpsCounter();
		void forceQuit();

		bool getGameLoop();
		void setGameLoop(bool gameloop);

};
