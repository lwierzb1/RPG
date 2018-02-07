#include "Fight.h"

Fight::Fight(SDL_setup *sdlsetup, MainCharacter *mainCharacter, Character *enemyCharacter, Environment *environment)
{
	quit = false;
	currentAction = ATTACK;
	character = mainCharacter;
	character->prepareToFight("data/characterFight.png", 10, 1, 200, 300, 150, 170);
	enemy = enemyCharacter;
	enemy->prepareToFight("data/enemyAttack42.png", 42, 1, 250,-25, 360, 400);
	this->sdlsetup = sdlsetup;
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
		sdlsetup->beginRender();
		forestArea->drawArena();
		if (character->mayAttack == true)
			switch (sdlsetup->getMainEvent()->type)
			{
			case SDL_KEYDOWN:

				switch (sdlsetup->getMainEvent()->key.keysym.sym)
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
						character->setDefence(character->getDefence() + 5);
						enemy->mayAttack = true;
					}
					else
						return false;
					break;
				default:
					break;
				}

				break;
			default:
				break;
			}
		for (int i = 0; i < 5; i++)
			SDL_RenderCopy(sdlsetup->getRenderer(), Message[i], NULL, &Message_rect[i]);
		character->drawStady();
		enemy->drawStady();
		if (character->isAttacking == true && character->mayAttack == true)
			performAttack(character,enemy);
		else if (enemy->mayAttack == true)
			performAttack(enemy,character);
		else
		{
			enemy->playAnimation(0, 17, 0, 150);
			character->playAnimation(1, 1, 0, 100);
		}
		
		sdlsetup->endRender();
		if (character->getHealth() == 0)
		{


			SDL_Surface* surfaceMessage;
			SDL_Texture* messageLost;
			SDL_Rect message_rectLost;
			surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE LOST press any key...", RED);
			messageLost = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage);
			message_rectLost.x = 100;  //controls the rect's x coordinate 
			message_rectLost.y = 150;  // controls the rect's y coordinte
			message_rectLost.w = 500; // controls the width of the rect
			message_rectLost.h = 200; // controls the height of the rect
			enemy->prepareToFight("data/enemyWin25.png", 25, 1, 250, -25, 360, 400);
			while (enemy->playAnimation(0, 24, 0, 100))
			{
				sdlsetup->beginRender();
				character->playAnimation(0, 0, 0, 100);
				forestArea->drawArena();
				character->drawStady();
				enemy->drawStady();
				sdlsetup->endRender();
			}
			enemy->setCurrentFrame(19);
			while (sdlsetup->getMainEvent()->type != SDL_KEYDOWN)
			{
				sdlsetup->beginRender();
				enemy->playAnimation(19, 24, 0, 150);
				character->playAnimation(0, 0, 0, 100);
				forestArea->drawArena();
				character->drawStady();
				enemy->drawStady();
				for (int i = 3; i < 5; i++)
					SDL_RenderCopy(sdlsetup->getRenderer(), Message[i], NULL, &Message_rect[i]);
				SDL_RenderCopy(sdlsetup->getRenderer(), messageLost, NULL, &message_rectLost);
				sdlsetup->endRender();
			}
				quit = true;
		}
		else if (enemy->getHealth() == 0)
		{
			SDL_Surface* surfaceMessage;
			SDL_Texture* messageLost;
			SDL_Rect message_rectLost;
			surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE WON press any key...", RED);
			messageLost = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage);
			message_rectLost.x = 100;  //controls the rect's x coordinate 
			message_rectLost.y = 150;  // controls the rect's y coordinte
			message_rectLost.w = 500; // controls the width of the rect
			message_rectLost.h = 200; // controls the height of the rect
			enemy->prepareToFight("data/enemyLose17.png", 17, 1, 250, -25, 360, 400);
			while (enemy->playAnimation(0, 16, 0, 300))
			{
				sdlsetup->beginRender();
				character->playAnimation(0, 0, 0, 100);
				forestArea->drawArena();
				character->drawStady();
				enemy->drawStady();
				sdlsetup->endRender();
			}
			enemy->setCurrentFrame(16);
			while (sdlsetup->getMainEvent()->type != SDL_KEYDOWN)
			{
				sdlsetup->beginRender();
				enemy->playAnimation(16, 16, 0, 150);
				character->playAnimation(0, 0, 0, 100);
				forestArea->drawArena();
				character->drawStady();
				enemy->drawStady();
				for (int i = 3; i < 5; i++)
					SDL_RenderCopy(sdlsetup->getRenderer(), Message[i], NULL, &Message_rect[i]);
				SDL_RenderCopy(sdlsetup->getRenderer(), messageLost, NULL, &message_rectLost);
				sdlsetup->endRender();
			}
			giveExperienceToMainCharacter();
			quit = true;
		}

	}

	return false;
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
		{
			victim->playAnimation(0, 17, 0, 150);
		}
		else
			victim->playAnimation(1, 1, 0, 100);
	}

}
void Fight::configFightMenu()
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), RED);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
		Message[i] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[i]);
		Message_rect[i].x = 20;  //controls the rect's x coordinate 
		Message_rect[i].y = 20 + 50 * i; // controls the rect's y coordinte
		Message_rect[i].w = 60; // controls the width of the rect
		Message_rect[i].h = 50; // controls the height of the rect
	}
	playerHp = "Your HP:  " + std::to_string(character->getHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->getHealth());
	for (int i = 3; i < 5; i++)
	{
		if(i == 3)
			surfaceMessage[i] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	Message[i] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[i]);
	Message_rect[i].x = 20;  //controls the rect's x coordinate 
	Message_rect[i].w = 150; // controls the width of the rect
	Message_rect[i].h = 70; // controls the height of the rect
	Message_rect[i].y = WINDOW_HEIGHT - Message_rect[i].h* (i-2); // controls the rect's y coordinte
	}
}
void Fight::updateFightMenu()
{
	playerHp = "Your HP:  " + std::to_string(character->getHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->getHealth());
	
	surfaceMessage[currentAction] = TTF_RenderText_Solid(font, availableActions[currentAction].c_str(), RED);
	Message[currentAction] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[currentAction]);

	surfaceMessage[3] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
	Message[3] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[3]);

	surfaceMessage[4] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	Message[4] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[4]);

	for (int i = 0; i < 3; i++)
	{
		if (i != currentAction)
		{
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
			Message[i] = SDL_CreateTextureFromSurface(sdlsetup->getRenderer(), surfaceMessage[i]);
		}
	}
}

Fight::~Fight()
{
	for (int i = 0; i < 3; i++)
	{
		SDL_FreeSurface(surfaceMessage[i]);
		SDL_DestroyTexture(Message[i]);
	}
}
