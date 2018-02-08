#pragma once
#include "Sprite.h"
#include "Environment.h"
#include "stdafx.h"
class Character : public Sprite
{
public:
	Character(SDL_Renderer *passedRenderer, string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect);
	Character::Character(SDL_Renderer *passedRenderer, string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, int level);
	~Character();

	void setX(int x);
	void setY(int y);
	int getX();
	int getY();
	int getHealth();
	int getStrength();
	int getDefence();
	void setDefence(int def);
	void setHealth(int hp);
	int getLuck();
	int getLevel();
	bool isAttacking;
	bool mayAttack;

protected:
	int level;
	int speed;
	int health;
	int strength;
	int defence;
	int luck;
};

