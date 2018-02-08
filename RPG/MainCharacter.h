#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_setup.h"
#include "Environment.h"
#include "CollisionRectangle.h"
#include "Character.h"
#define GO_DOWN 0
#define GO_UP 1
#define GO_LEFT 2
#define GO_RIGHT 3
class MainCharacter : public Character
{
public:
	MainCharacter(SDL_Renderer *passedRenderer, string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect);
	~MainCharacter();
	void brushAsideCharacter(int epsilon);
	void update(Environment *environment);
	void setExperience(int exp);
	int getExperience();
	bool checkIfEnemyisColidingCharacter(Character *enemyCharacter);
	void ResetKeyState();
	void levelUp();
private:
	Properties properties;
	void scanKeys();
	void moveCharacter();
	void CheckCollision(Environment *environment);
	
	int experienceNeededToNextLevel;
	int initialHealth;
	int experience;
	
	int beginX;
	int beginY;
	int timeCheck;
	//char param
	//keyboard input
	const Uint8 *keyboardState;
	enum keys
	{
		idle,
		moveRight,
		moveLeft,
		moveUp,
		moveDown
	};
	keys key;
};

