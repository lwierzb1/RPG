#include "stdafx.h"
#include "Tree.h"


Tree::Tree(SDL_Setup *sdlSetup, int x, int y, int *cameraX, int *cameraY)
{
	this->x = x;
	this->y = y;

	this->cameraX = cameraX;
	this->cameraY = cameraY;
	trunk = new Sprite(sdlSetup->GetRenderer(), "data/environment/treeTrunk.png", x, y, 50, 80, cameraX, cameraY, CollisionRectangle(0,80*0.5,50,80*0.5));
	branch = new Sprite(sdlSetup->GetRenderer(), "data/environment/treeBranch.png", x -(250-50)/2*0.71 , y - (325-90), 250*0.75, 325*0.75, cameraX, cameraY, CollisionRectangle(0, 0, 250 * 0.75, 325 * 0.75));
}
void Tree::DrawTree()
{
	trunk->Draw();
	branch->Draw();
}
int Tree::GetX()
{
	return x;
}
int Tree::GetY()
{
	return y;
}
Sprite* Tree::GetTrunk()
{
	return trunk;
}
Sprite* Tree::GetBranch()
{
	return branch;
}
Tree::~Tree()
{
	delete trunk;
	delete branch;
}
