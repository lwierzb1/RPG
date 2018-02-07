#pragma once
#include "stdafx.h"
#include "SDL_setup.h"
#include <SDL_ttf.h>
#include "Sprite.h"
#include "MainCharacter.h"
#include "Environment.h"
#include "Character.h"
class Fight 
{
public:
	Fight(SDL_setup *sdlsetup, MainCharacter *mainCharacter, Character *enemyCharacter, Environment *environment);
	~Fight();
	bool fightLoop();
	void configFightMenu();
	void updateFightMenu();
	void giveExperienceToMainCharacter();
	void performAttack(Character *aggressor, Character *victim);
private:
	const Uint8 *keyboardState;
	//The font that's going to be used 
	TTF_Font *font = NULL;
	//The color of the font 
	SDL_Color White = { 255, 255, 255 };
	SDL_Color RED = { 255, 0, 0 };
	SDL_Surface* surfaceMessage[5];
	SDL_Texture* Message[5];
	SDL_Rect Message_rect[5];
	std::string playerHp;
	std::string enemyHp;
	std::string availableActions[3] = { "Attack", "Defence", "Flee" };
	int currentOption = 0;
	enum CurrentAction {
		ATTACK,
		DEFENCE ,
		FLEE
	} ;
	CurrentAction currentAction;
	bool quit;
	SDL_setup *sdlsetup;
	MainCharacter *character;
	Character *enemy;
	Environment *forestArea;
	friend inline CurrentAction& operator++(CurrentAction& eDOW, int)  // <--- note -- must be a reference
	{
		const int i = static_cast<int>(eDOW) + 1;
		eDOW = static_cast<CurrentAction>((i) % 3);
		return eDOW;
	}
	friend inline CurrentAction& operator--(CurrentAction& type, int)  // <--- note -- must be a reference
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

