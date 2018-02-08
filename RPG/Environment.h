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
	Environment(SDL_setup *sdlSetup, int screenWidth, int screenHeight, int *cameraX, int *cameraY);
	~Environment();
	void drawBack();
	void drawFront(int characterY);
	void drawArena();
	void update();
	void saveToFile();
	void loadFromFile();
	vector<Tree*> getTrees();
private:
	vector<Tree*> trees;

	bool keyPressed;
	int mode;
	int *cameraX;
	int *cameraY;
	int amountOfGrassColumns;
	int amountOfGrassRows;
	Sprite *arena;
	Sprite *grass[COLUMNS_GRASS][ROWS_GRASS];
	SDL_setup *sdlSetup;
	Properties properties;
	enum gameMode {
		gamePlay,
		levelCreation
	};
};

