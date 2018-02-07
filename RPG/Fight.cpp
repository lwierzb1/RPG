#include "Fight.h"

Fight::Fight(SDL_setup *sdlSetup, MainCharacter *mainCharacter, Character *enemyCharacter, Environment *environment)
{
	//two last are for player hp and enemy hp
	amountOfMenuRects = sizeof(battleMessage) / sizeof(battleMessage[0]) - 2;
	amountOfAllBattleRects = sizeof(battleMessage) / sizeof(battleMessage[0]);
	quit = false;
	currentAction = ATTACK;
	character = mainCharacter;
	character->changeImage("data/characterFight.png", 10, 1, 200, 300, 150, 170);
	enemy = enemyCharacter;
	enemy->changeImage("data/enemyAttack42.png", 42, 1, 250,-25, 360, 400);
	this->sdlSetup = sdlSetup;
	forestArea = environment;
	TTF_Init();
	font = TTF_OpenFont("C:/Users/Lukasz/Documents/R/win-library/3.4/rmarkdown/rmd/ioslides/ioslides-13.5.1/fonts/OpenSans.ttf", 10);
	keyboardState = SDL_GetKeyboardState(NULL);
	configFightMenu();

}
bool Fight::fightLoop()
{
	while (!quit)
	{
		sdlSetup->beginRender();
		forestArea->drawArena();
		if (character->mayAttack == true)
			switch (sdlSetup->getMainEvent()->type)
			{
				case SDL_KEYDOWN:
					switch (sdlSetup->getMainEvent()->key.keysym.sym)
					{
						case SDLK_s:
							currentAction ++;
							updateFightMenu();
							break;
						case SDLK_w:
							currentAction --;
							updateFightMenu();
							break;
						case SDLK_SPACE:
							if (currentAction == ATTACK)
								character->isAttacking = true;
							else if (currentAction == DEFENCE)
							{
								performDefence(character, 5);
								enemy->mayAttack = true;
							}
							else if (currentAction == FLEE)
								return false;
							break;
						default:
							break;
					}
					break;
				default:
					break;
			}
		drawBattleMessages();
		character->drawStady();
		enemy->drawStady();
		if (character->isAttacking == true && character->mayAttack == true)
			performAttack(character,enemy);
		else if (enemy->mayAttack == true)
			performAttack(enemy,character);
		else
		{
			//idle state animations
			enemy->playAnimation(0, 17, 0, 150);
			character->playAnimation(1, 1, 0, 100);
		}
		sdlSetup->endRender();
		if (character->getHealth() == 0)
			viewFightResult(enemy);
		else if (enemy->getHealth() == 0)
			viewFightResult(character);
	}
	return false;
}
void Fight::viewFightResult(Character *winner)
{
	bool mainCharacterWon = true;
	SDL_Surface* surfaceMessage;
	SDL_Texture* messageLost;
	SDL_Rect message_rectLost;
	std::string aggressorClassName = typeid(*winner).name();
	if (aggressorClassName.find("MainCharacter") != std::string::npos)
	{
		surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE WON press any key...", RED);
		enemy->changeImage("data/enemyLose17.png", 17, 1, 250, -25, 360, 400);
	}
	else
	{
		mainCharacterWon = false;
		surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE LOST press any key...", RED);
		enemy->changeImage("data/enemyWin25.png", 25, 1, 250, -25, 360, 400);
	}
	messageLost = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage);
	message_rectLost.x = 100;  //controls the rect's x coordinate 
	message_rectLost.y = 150;  // controls the rect's y coordinte
	message_rectLost.w = 500; // controls the width of the rect
	message_rectLost.h = 200; // controls the height of the rect
	while (enemy->playAnimation(0, enemy->getAmountOfXFrames() - 1, 0, 200))
	{
		sdlSetup->beginRender();
		character->playAnimation(0, 0, 0, 100);
		forestArea->drawArena();
		character->drawStady();
		enemy->drawStady();
		sdlSetup->endRender();
	}
	enemy->setCurrentFrame(enemy->getAmountOfXFrames() - 1);
	if (mainCharacterWon)
	{
		enemy->changeImage("data/enemyLoseIdle1.png", 1, 1, 250, -25, 360, 400);
		giveExperienceToMainCharacter();
	}
	else
		enemy->changeImage("data/enemyWinIdle5.png", 5, 1, 250, -25, 360, 400);
	while (sdlSetup->getMainEvent()->type != SDL_KEYDOWN)
	{
		sdlSetup->beginRender();
		enemy->playAnimation(0, enemy->getAmountOfXFrames() - 1, 0, 120);
		character->playAnimation(0, 0, 0, 500);
		forestArea->drawArena();
		character->drawStady();
		enemy->drawStady();
		for (int i = amountOfMenuRects; i < amountOfAllBattleRects; i++)
			SDL_RenderCopy(sdlSetup->getRenderer(), battleMessage[i], NULL, &battleMessageRect[i]);
		SDL_RenderCopy(sdlSetup->getRenderer(), messageLost, NULL, &message_rectLost);
		sdlSetup->endRender();
	}
	quit = true;
}
void Fight::drawBattleMessages()
{
	for (int i = 0; i < amountOfAllBattleRects; i++)
		SDL_RenderCopy(sdlSetup->getRenderer(), battleMessage[i], NULL, &battleMessageRect[i]);
}
void Fight::giveExperienceToMainCharacter()
{
	character->setExperience(character->getExperience()+100);
}
void Fight::performAttack(Character *aggressor, Character *victim)
{
	std::string aggressorClassName = typeid(*aggressor).name();
	victim->mayAttack = false;
	if (!aggressor->playAnimation(0, aggressor->getAmountOfXFrames() - 1, 0, 100))
	{
		aggressor->playAnimation(0, 0, 0, 100);
		aggressor->isAttacking = false;
		victim->mayAttack = true;
		aggressor->mayAttack = false;
		if(aggressor->getStrength() <= victim->getDefence())
			victim->setHealth(victim->getHealth() - 1);
		else
			victim->setHealth(victim->getHealth() - (aggressor->getStrength() - victim->getDefence()));
		if (victim->getHealth() < 0)
			victim->setHealth(0);
		updateFightMenu();
	}
	else
	{
		if (aggressorClassName.find("MainCharacter") != std::string::npos)
			victim->playAnimation(0, 17, 0, 150);
		else
			victim->playAnimation(1, 1, 0, 100);
	}
}
void Fight::performDefence(Character *defencer, int extraDefence)
{
	defencer->setDefence(defencer->getDefence() + extraDefence);
}
void Fight::configFightMenu()
{
	//two last rects are for enemy and player hp
	for (int i = 0; i < sizeof(battleMessage)/sizeof(battleMessage[0]) - 2; i++)
	{
		if (i == 0)
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), RED);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
		battleMessage[i] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[i]);
		battleMessageRect[i].x = 20;  //controls the rect's x coordinate 
		battleMessageRect[i].y = 20 + 50 * i; // controls the rect's y coordinte
		battleMessageRect[i].w = 60; // controls the width of the rect
		battleMessageRect[i].h = 50; // controls the height of the rect
	}
	playerHp = "Your HP:  " + std::to_string(character->getHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->getHealth());

	for (int i = amountOfMenuRects; i < amountOfAllBattleRects; i++)
	{
		if(i == 3)
			surfaceMessage[i] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	battleMessage[i] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[i]);
	battleMessageRect[i].x = 20;  //controls the rect's x coordinate 
	battleMessageRect[i].w = 150; // controls the width of the rect
	battleMessageRect[i].h = 70; // controls the height of the rect
	battleMessageRect[i].y = WINDOW_HEIGHT - battleMessageRect[i].h* (i-2); // controls the rect's y coordinte
	}
}
void Fight::updateFightMenu()
{
	playerHp = "Your HP:  " + std::to_string(character->getHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->getHealth());
	
	surfaceMessage[currentAction] = TTF_RenderText_Solid(font, availableActions[currentAction].c_str(), RED);
	battleMessage[currentAction] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[currentAction]);

	surfaceMessage[amountOfAllBattleRects - 2] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
	battleMessage[amountOfAllBattleRects - 2] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[3]);

	surfaceMessage[amountOfAllBattleRects - 1] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	battleMessage[amountOfAllBattleRects - 1] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[4]);

	for (int i = 0; i < amountOfMenuRects; i++)
	{
		if (i != currentAction)
		{
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
			battleMessage[i] = SDL_CreateTextureFromSurface(sdlSetup->getRenderer(), surfaceMessage[i]);
		}
	}
}
Fight::~Fight()
{
	for (int i = 0; i < amountOfAllBattleRects; i++)
	{
		SDL_FreeSurface(surfaceMessage[i]);
		SDL_DestroyTexture(battleMessage[i]);
	}
}
