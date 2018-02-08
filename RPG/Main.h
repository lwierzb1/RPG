#pragma once
#include "SDL_setup.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include "Character.h"
#include "Fight.h"
#include "stdafx.h"
class Main
{
public:
	Main(int passedScreenWidth, int passedScreenHeight);
	Main();
	~Main();
	void loadFromFile();
	void saveToFile();
	void GameLoop();
	bool getQuit();
	void setQuit(bool updateQuit);
	

private:
	Properties properties;
	int screenWidth;
	int screenHeight;
	int cameraX;
	int cameraY;
protected:
	bool quit;
	SDL_setup *sdlSetup;
	MainCharacter *character;
	vector<Character*> enemies;
	//Character *enemy;
	Environment *forestArea;
};

