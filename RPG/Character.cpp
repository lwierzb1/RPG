#include "stdafx.h"
#include "Character.h"


Character::Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, SDL_Setup *passedSDL)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	isAttacking = false;
	strength = 10;
	defence = 5;
	health = 100;
	mayAttack = false;
}
void Character::SetX(int x)
{
	this->x = x;
}
void Character::SetY(int y)
{
	this->y = y;
}
int Character::GetX()
{
	return x;
}
int Character::GetY()
{
	return y;
}
int Character::GetHealth()
{
	return health;
}
int Character::GetStrength()
{
	return strength;
}
int Character::GetDefence()
{
	return defence;
}
void Character::SetDefence(int def)
{
	defence = def;
}
void Character::SetHealth(int hp)
{
	health = hp;
}
Character::~Character()
{
}
