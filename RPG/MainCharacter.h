#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "SDL_Setup.h"
#include "Environment.h"
#include "CollisionRectangle.h"
#include "Character.h"
class MainCharacter : public Character
{
public:
	MainCharacter(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect,SDL_Setup *passedSDL);
	~MainCharacter();
	
	void Update(Environment *environment);
	void SetExperience(int exp);
	int GetExperience();
	bool CheckIfEnemyIsColidingCharacter(Character *enemyCharacter);

private:
	void scanKeys();
	void moveCharacter();
	void CheckCollision(Environment *environment);
	//sdl and timing
	SDL_Setup *sdlSetup;
	
	int beginX;
	int beginY;
	int timeCheck;
	//char param
	int level;
	int experience;
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

