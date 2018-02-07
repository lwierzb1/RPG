#pragma once
#include "SDL_setup.h"
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
	bool getQuit();
	void setQuit(bool updateQuit);
	

private:
	int screenWidth;
	int screenHeight;
	int cameraX;
	int cameraY;
protected:
	bool quit;
	SDL_setup *sdlsetup;
	MainCharacter *character;
	Character *enemy;
	Environment *forestArea;
};

