#pragma once
#include "stdafx.h"
class SDL_setup
{
public:
	SDL_setup(bool *quit, int screenWidth, int screenHeight);
	~SDL_setup();

	SDL_Renderer *getRenderer();
	SDL_Event *getMainEvent();
	
	void beginRender();
	void endRender();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;
};

