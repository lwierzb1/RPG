#pragma once
#include "SDL_setup.h"
#include "Sprite.h"
class Tree
{
public:
	Tree(SDL_setup *sdlsetup, int x, int y, int *cameraX, int *cameraY);
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

