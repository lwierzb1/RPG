#include "Fight.h"

Fight::Fight(SDL_Setup *sdlSetup, MainCharacter *mainCharacter, Character *enemyCharacter, Environment *environment)
{
	quit = false;
	currentAction = attack;
	character = mainCharacter;
	character->PrepareToFight("data/characterFight.png", 10, 1, 200, 300, 150, 170);
	enemy = enemyCharacter;
	enemy->PrepareToFight("data/enemyAttack42.png", 42, 1, 250,-25, 360, 400);
	this->sdlSetup = sdlSetup;
	forestArea = environment;
	TTF_Init();
	font = TTF_OpenFont("C:/Users/Lukasz/Documents/R/win-library/3.4/rmarkdown/rmd/ioslides/ioslides-13.5.1/fonts/OpenSans.ttf", 10);
	keyboardState = SDL_GetKeyboardState(NULL);
	ConfigFightMenu();

}
bool Fight::FightLoop()
{
	while (!quit)
	{
		sdlSetup->BeginRender();
		forestArea->DrawArena();
		if (character->mayAttack == true)
			switch (sdlSetup->GetMainEvent()->type)
			{
			case SDL_KEYDOWN:

				switch (sdlSetup->GetMainEvent()->key.keysym.sym)
				{
				case SDLK_s:
					currentAction ++;
					UpdateFightMenu();
					break;
				case SDLK_w:
					currentAction --;
					UpdateFightMenu();
					break;
				case SDLK_SPACE:
					if (currentAction == attack)
						character->isAttacking = true;
					else if (currentAction == defence)
					{
						character->SetDefence(character->GetDefence() + 5);
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
			SDL_RenderCopy(sdlSetup->GetRenderer(), Message[i], NULL, &Message_rect[i]);
		character->DrawStady();
		enemy->DrawStady();
		if (character->isAttacking == true && character->mayAttack == true)
			PerformAttack(character,enemy);
		else if (enemy->mayAttack == true)
			PerformAttack(enemy,character);
		else
		{
			enemy->PlayAnimation(0, 17, 0, 150);
			character->PlayAnimation(1, 1, 0, 100);
		}
		
		sdlSetup->EndRender();
		if (character->GetHealth() == 0)
		{


			SDL_Surface* surfaceMessage;
			SDL_Texture* messageLost;
			SDL_Rect message_rectLost;
			surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE LOST press any key...", RED);
			messageLost = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage);
			message_rectLost.x = 100;  //controls the rect's x coordinate 
			message_rectLost.y = 150;  // controls the rect's y coordinte
			message_rectLost.w = 500; // controls the width of the rect
			message_rectLost.h = 200; // controls the height of the rect
			enemy->PrepareToFight("data/enemyWin25.png", 25, 1, 250, -25, 360, 400);
			while (enemy->PlayAnimation(0, 24, 0, 100))
			{
				sdlSetup->BeginRender();
				character->PlayAnimation(0, 0, 0, 100);
				forestArea->DrawArena();
				character->DrawStady();
				enemy->DrawStady();
				sdlSetup->EndRender();
			}
			enemy->SetCurrentFrame(19);
			while (sdlSetup->GetMainEvent()->type != SDL_KEYDOWN)
			{
				sdlSetup->BeginRender();
				enemy->PlayAnimation(19, 24, 0, 150);
				character->PlayAnimation(0, 0, 0, 100);
				forestArea->DrawArena();
				character->DrawStady();
				enemy->DrawStady();
				for (int i = 3; i < 5; i++)
					SDL_RenderCopy(sdlSetup->GetRenderer(), Message[i], NULL, &Message_rect[i]);
				SDL_RenderCopy(sdlSetup->GetRenderer(), messageLost, NULL, &message_rectLost);
				sdlSetup->EndRender();
			}
				quit = true;
		}
		else if (enemy->GetHealth() == 0)
		{
			SDL_Surface* surfaceMessage;
			SDL_Texture* messageLost;
			SDL_Rect message_rectLost;
			surfaceMessage = TTF_RenderText_Solid(font, "YOU HAVE WON press any key...", RED);
			messageLost = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage);
			message_rectLost.x = 100;  //controls the rect's x coordinate 
			message_rectLost.y = 150;  // controls the rect's y coordinte
			message_rectLost.w = 500; // controls the width of the rect
			message_rectLost.h = 200; // controls the height of the rect
			enemy->PrepareToFight("data/enemyLose17.png", 17, 1, 250, -25, 360, 400);
			while (enemy->PlayAnimation(0, 16, 0, 300))
			{
				sdlSetup->BeginRender();
				character->PlayAnimation(0, 0, 0, 100);
				forestArea->DrawArena();
				character->DrawStady();
				enemy->DrawStady();
				sdlSetup->EndRender();
			}
			enemy->SetCurrentFrame(16);
			while (sdlSetup->GetMainEvent()->type != SDL_KEYDOWN)
			{
				sdlSetup->BeginRender();
				enemy->PlayAnimation(16, 16, 0, 150);
				character->PlayAnimation(0, 0, 0, 100);
				forestArea->DrawArena();
				character->DrawStady();
				enemy->DrawStady();
				for (int i = 3; i < 5; i++)
					SDL_RenderCopy(sdlSetup->GetRenderer(), Message[i], NULL, &Message_rect[i]);
				SDL_RenderCopy(sdlSetup->GetRenderer(), messageLost, NULL, &message_rectLost);
				sdlSetup->EndRender();
			}
			GiveExperienceToMainCharacter();
			quit = true;
		}

	}

	return false;
}
void Fight::GiveExperienceToMainCharacter()
{
	character->SetExperience(character->GetExperience()+100);
}
void Fight::PerformAttack(Character *aggressor, Character *victim)
{
	std::string aggressorClassName = typeid(*aggressor).name();
	victim->mayAttack = false;
	if (!aggressor->PlayAnimation(0, aggressor->GetAmountOfXFrames() - 1, 0, 100))
	{
		aggressor->PlayAnimation(0, 0, 0, 100);
		aggressor->isAttacking = false;
		victim->mayAttack = true;
		aggressor->mayAttack = false;
		if(aggressor->GetStrength() <= victim->GetDefence())
			victim->SetHealth(victim->GetHealth() - 1);
		else
			victim->SetHealth(victim->GetHealth() - (aggressor->GetStrength() - victim->GetDefence()));
		if (victim->GetHealth() < 0)
			victim->SetHealth(0);
		UpdateFightMenu();
	}
	else
	{
		if (aggressorClassName.find("MainCharacter") != std::string::npos)
		{
			victim->PlayAnimation(0, 17, 0, 150);
		}
		else
			victim->PlayAnimation(1, 1, 0, 100);
	}

}
void Fight::ConfigFightMenu()
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), RED);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
		Message[i] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[i]);
		Message_rect[i].x = 20;  //controls the rect's x coordinate 
		Message_rect[i].y = 20 + 50 * i; // controls the rect's y coordinte
		Message_rect[i].w = 60; // controls the width of the rect
		Message_rect[i].h = 50; // controls the height of the rect
	}
	playerHp = "Your HP:  " + std::to_string(character->GetHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->GetHealth());
	for (int i = 3; i < 5; i++)
	{
		if(i == 3)
			surfaceMessage[i] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
		else
			surfaceMessage[i] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	Message[i] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[i]);
	Message_rect[i].x = 20;  //controls the rect's x coordinate 
	Message_rect[i].w = 150; // controls the width of the rect
	Message_rect[i].h = 70; // controls the height of the rect
	Message_rect[i].y = WINDOW_HEIGHT - Message_rect[i].h* (i-2); // controls the rect's y coordinte
	}
}
void Fight::UpdateFightMenu()
{
	playerHp = "Your HP:  " + std::to_string(character->GetHealth());
	enemyHp = "Enemy HP:  " + std::to_string(enemy->GetHealth());
	
	surfaceMessage[currentAction] = TTF_RenderText_Solid(font, availableActions[currentAction].c_str(), RED);
	Message[currentAction] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[currentAction]);

	surfaceMessage[3] = TTF_RenderText_Solid(font, enemyHp.c_str(), White);
	Message[3] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[3]);

	surfaceMessage[4] = TTF_RenderText_Solid(font, playerHp.c_str(), White);
	Message[4] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[4]);

	for (int i = 0; i < 3; i++)
	{
		if (i != currentAction)
		{
			surfaceMessage[i] = TTF_RenderText_Solid(font, availableActions[i].c_str(), White);
			Message[i] = SDL_CreateTextureFromSurface(sdlSetup->GetRenderer(), surfaceMessage[i]);
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
