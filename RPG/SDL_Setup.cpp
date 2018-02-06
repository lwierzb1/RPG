#include "stdafx.h"
#include "SDL_Setup.h"


SDL_Setup::SDL_Setup(bool *quit, int screenWidth, int screenHeight)
{
	SDL_Init(SDL_INIT_VIDEO);
	window = NULL;
	window = SDL_CreateWindow("RPG", 100, 100, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Window couldn't be created" << std::endl;
		*quit = true;
	}
	renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	mainEvent = new SDL_Event();
}
SDL_Renderer* SDL_Setup::GetRenderer()
{
	return renderer;
}
SDL_Event* SDL_Setup::GetMainEvent()
{
	return mainEvent;
}
void SDL_Setup::BeginRender()
{
	SDL_PollEvent(mainEvent);
	SDL_RenderClear(renderer);
}
void SDL_Setup::EndRender()
{
	SDL_RenderPresent(renderer);
}
SDL_Setup::~SDL_Setup()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	delete mainEvent;
}



