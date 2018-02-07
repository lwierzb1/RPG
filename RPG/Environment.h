#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_setup.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "PropertiesParser.h"
class Environment
{
public:
	Environment(SDL_setup *sdlsetup, int screenWidth, int screenHeight, int *cameraX, int *cameraY);
	~Environment();
	void drawBack();
	void drawFront(int characterY);
	void drawArena();
	void update();
	void saveToFile();
	void loadFromFile();
	std::vector<Tree*> getTrees();
private:
	std::vector<Tree*> trees;

	bool keyPressed;
	int mode;
	int *cameraX;
	int *cameraY;
	Sprite *arena;
	Sprite *grass[COLUMNS_GRASS][ROWS_GRASS];
	SDL_setup *sdlsetup;

	enum gameMode {
		gamePlay,
		levelCreation
	};
};

