#pragma once
#include "Sprite.h"
#include "Environment.h"
class Character : public Sprite
{
public:
	Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, SDL_Setup *passedSDL);
	~Character();

	void SetX(int x);
	void SetY(int y);
	int GetX();
	int GetY();
	int GetHealth();
	int GetStrength();
	int GetDefence();
	void SetDefence(int def);
	void SetHealth(int hp);
	bool isAttacking;
	bool mayAttack;
protected:
	int speed;
	int health;
	int strength;
	int defence;
};

