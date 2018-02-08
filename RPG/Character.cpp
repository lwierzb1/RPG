#include "Character.h"

Character::Character(SDL_Renderer *passedRenderer, string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	Properties properties = PropertiesParser::Read("GameConfig.properties");
	level = 1;
	isAttacking = properties.stringToBool(properties.getProperty("EnemyCharacterIsAttacking"));
	strength = level * stoi(properties.getProperty("EnemyCharacterStrengthFactor"));
	defence = level * stoi(properties.getProperty("EnemyCharacterDefenceFactor"));
	mayAttack = properties.stringToBool(properties.getProperty("EnemyCharacterMayAttack"));
	luck = stoi(properties.getProperty("EnemyCharacterLuckFactorial")) * level;
	health = stoi(properties.getProperty("EnemyCharacterInitialHealth")) + 
			 level * stoi(properties.getProperty("EnemyCharacterHealthFactor"));
}	
Character::Character(SDL_Renderer *passedRenderer, string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, int level)
	:Sprite(passedRenderer, FilePath, x, y, w, h, passedCameraX, passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	Properties properties = PropertiesParser::Read("GameConfig.properties");
	this->level = level;
	isAttacking = properties.stringToBool(properties.getProperty("EnemyCharacterIsAttacking"));;
	strength = level * stoi(properties.getProperty("EnemyCharacterStrengthFactor"));
	defence = level * stoi(properties.getProperty("EnemyCharacterDefenceFactor"));
	mayAttack = properties.stringToBool(properties.getProperty("EnemyCharacterMayAttack"));
	luck = stoi(properties.getProperty("EnemyCharacterLuckFactorial")) * level;
	health = stoi(properties.getProperty("EnemyCharacterInitialHealth")) + 
			 level * stoi(properties.getProperty("EnemyCharacterHealthFactor"));
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
