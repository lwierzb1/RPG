#include "stdafx.h"
#include "Character.h"


Character::Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	level = 1;
	isAttacking = false;
	strength = level * 5;
	defence = level * 5 + 2;
	health = 100;
	mayAttack = false;
	luck = 5 * level;
}
Character::Character(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, int level)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	this->level = level;
	isAttacking = false;
	strength = level * 5;
	defence = level * 5 + 2;
	health = 100 + level * 10;
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
int Character::getLuck()
{
	return luck;
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
int Character::getLevel()
{
	return level;
}
void Character::setHealth(int hp)
{
	health = hp;
}
Character::~Character()
{
}
