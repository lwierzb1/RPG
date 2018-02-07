#pragma once
#include "stdafx.h"

class CollisionRectangle
{
public:
	CollisionRectangle();
	CollisionRectangle(int x, int y, int w, int h);
	~CollisionRectangle();
	
	void setRectangle(int x, int y, int w, int h);
	SDL_Rect getRectangle();
	void setRectangleX(int x);
	void setRectangleY(int y);
	int getRectangleX();
	int getRectangleY();
private:
	int offsetX;
	int offsetY;
	SDL_Rect collisionRect;
};

