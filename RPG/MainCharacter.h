#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_setup.h"
#include "Environment.h"
#include "CollisionRectangle.h"
#include "Character.h"
class MainCharacter : public Character
{
public:
	MainCharacter(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect);
	~MainCharacter();
	void brushAsideCharacter(int epsilon);
	void update(Environment *environment);
	void setExperience(int exp);
	int getExperience();
	bool checkIfEnemyisColidingCharacter(Character *enemyCharacter);
	void ResetKeyState();
	void levelUp();
private:
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

