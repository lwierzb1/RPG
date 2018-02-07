#pragma once
#include "Sprite.h"
#include "Environment.h"
class Character : public Sprite
{
public:
	Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, SDL_setup *passedSDL);
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
	bool isAttacking;
	bool mayAttack;
protected:
	int speed;
	int health;
	int strength;
	int defence;
};

