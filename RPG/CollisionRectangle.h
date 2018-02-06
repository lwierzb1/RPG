#pragma once
#include "stdafx.h"

class CollisionRectangle
{
public:
	CollisionRectangle();
	CollisionRectangle(int x, int y, int w, int h);
	~CollisionRectangle();
	
	void SetRectangle(int x, int y, int w, int h);
	SDL_Rect GetRectangle();
	void SetRectangleX(int x);
	void SetRectangleY(int y);
	int GetRectangleX();
	int GetRectangleY();
private:
	int offsetX;
	int offsetY;
	SDL_Rect collisionRect;
};

