#pragma once
#include "stdafx.h"
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include "Character.h"
#include <ctime>
class Fight 
{
public:
	Fight(SDL_setup *sdlSetup, MainCharacter *mainCharacter, Character *enemyCharacter, Environment *environment);
	~Fight();
	bool fightLoop();
	void configFightMenu();
	void updateFightMenu();
	void performAttack(Character *aggressor, Character *victim);
	void performDefence(Character *defencer, int extraDefence);
	void drawBattleMessages();
	void viewFightResult(Character *winner);
private:
	Properties properties;
	const Uint8 *keyboardState;
	//The font that's going to be used 
	TTF_Font *font = NULL;
	//The color of the font 
	SDL_Color White = { 255, 255, 255 };
	SDL_Color Red = { 255, 0, 0 };
	SDL_Surface* surfaceMessage[5];
	SDL_Texture* battleMessage[5];
	SDL_Rect battleMessageRect[5];
	int amountOfMenuRects;
	int amountOfAllBattleRects;
	string playerHp;
	string enemyHp;
	string availableActions[3] = { "Attack", "Defence", "Flee" };
	int currentOption = 0;
	enum CurrentAction {
		ATTACK,
		DEFENCE ,
		FLEE
	} ;
	CurrentAction currentAction;
	bool quit;
	SDL_setup *sdlSetup;
	MainCharacter *character;
	Character *enemy;
	Environment *forestArea;
	friend inline CurrentAction& operator++(CurrentAction& eDOW, int)
	{
		const int i = static_cast<int>(eDOW) + 1;
		eDOW = static_cast<CurrentAction>((i) % 3);
		return eDOW;
	}
	friend inline CurrentAction& operator--(CurrentAction& type, int)
	{
		const int i = static_cast<int>(type) - 1;

		if (i < 0) // Check whether to cycle to last item if number goes below 0
		{
			type = static_cast<CurrentAction>(2);
		}
		else // Else set it to current number -1
		{
			type = static_cast<CurrentAction>((i) % 3);
		}
		return type;
	}
};

