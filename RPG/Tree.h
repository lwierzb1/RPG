#pragma once
#include "SDL_setup.h"
#include "Sprite.h"
#include "stdafx.h"
class Tree
{
public:
	Tree(SDL_setup *sdlSetup, int x, int y, int *cameraX, int *cameraY);
	~Tree();
	void drawTree();
	int getX();
	int getY();
	Sprite* getTrunk();
	Sprite* getBranch();
private:
	int x;
	int y;
	int *cameraX;
	int *cameraY;
	Sprite *trunk;
	Sprite *branch;
};

