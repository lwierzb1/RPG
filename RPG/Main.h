#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include "Character.h"
#include "Fight.h"

class Main
{
public:
	Main(int passedScreenWidth, int passedScreenHeight);
	Main();
	~Main();

	void GameLoop();
	bool GetQuit();
	void SetQuit(bool updateQuit);
	

private:
	int screenWidth;
	int screenHeight;
	int cameraX;
	int cameraY;
protected:
	bool quit;
	SDL_Setup *sdlSetup;
	MainCharacter *character;
	Character *enemy;
	Environment *forestArea;
};

