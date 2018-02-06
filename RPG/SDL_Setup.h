#pragma once
#include "stdafx.h"
class SDL_Setup
{
public:
	SDL_Setup(bool *quit, int screenWidth, int screenHeight);
	~SDL_Setup();

	SDL_Renderer *GetRenderer();
	SDL_Event *GetMainEvent();
	
	void BeginRender();
	void EndRender();
private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event *mainEvent;
};

