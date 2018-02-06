#pragma once
#include "Sprite.h"
#include "stdafx.h"
#include "SDL_Setup.h"
#include "Tree.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "PropertiesParser.h"
class Environment
{
public:
	Environment(SDL_Setup *sdlSetup, int screenWidth, int screenHeight, int *cameraX, int *cameraY);
	~Environment();
	void DrawBack();
	void DrawFront(int characterY);
	void DrawArena();
	void Update();
	void SaveToFile();
	void LoadFromFile();
	std::vector<Tree*> GetTrees();
private:
	std::vector<Tree*> trees;

	bool keyPressed;
	int mode;
	int *cameraX;
	int *cameraY;
	Sprite *arena;
	Sprite *grass[COLUMNS_GRASS][ROWS_GRASS];
	SDL_Setup *sdlSetup;

	enum gameMode {
		gamePlay,
		levelCreation
	};
};

