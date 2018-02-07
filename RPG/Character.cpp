#include "stdafx.h"
#include "Character.h"


Character::Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, SDL_setup *passedSDL)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	isAttacking = false;
	strength = 10;
	defence = 5;
	health = 100;
	mayAttack = false;
}
void Character::setX(int x)
{
	this->x = x;
}
void Character::setY(int y)
{
	this->y = y;
}
int Character::getX()
{
	return x;
}
int Character::getY()
{
	return y;
}
int Character::getHealth()
{
	return health;
}
int Character::getStrength()
{
	return strength;
}
int Character::getDefence()
{
	return defence;
}
void Character::setDefence(int def)
{
	defence = def;
}
void Character::setHealth(int hp)
{
	health = hp;
}
Character::~Character()
{
}
