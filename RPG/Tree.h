#pragma once
#include "SDL_Setup.h"
#include "Sprite.h"
class Tree
{
public:
	Tree(SDL_Setup *sdlSetup, int x, int y, int *cameraX, int *cameraY);
	~Tree();
	void DrawTree();
	int GetX();
	int GetY();
	Sprite* GetTrunk();
	Sprite* GetBranch();
private:
	int x;
	int y;
	int *cameraX;
	int *cameraY;
	Sprite *trunk;
	Sprite *branch;
};

