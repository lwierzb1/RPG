#include "stdafx.h"
#include "Main.h"


Main::Main(int passedScreenWidth, int passedScreenHeight)
{
	quit = false;
	cameraX = 0;
	cameraY = 0;
	screenWidth = passedScreenWidth;
	screenHeight = passedScreenHeight;
	sdlSetup = new SDL_Setup(&quit, screenWidth, screenHeight);
	forestArea = new Environment(sdlSetup, screenWidth, screenHeight, &cameraX, &cameraY);
	character = new MainCharacter(sdlSetup->GetRenderer(), "data/character.png", (WINDOW_WIDTH) / 2, (WINDOW_HEIGHT) / 2,100,120, &cameraX, &cameraY, 6, 4, CollisionRectangle((WINDOW_WIDTH) / 2, (WINDOW_HEIGHT) / 2 *1.25, 100, 120*0.3), sdlSetup);
	enemy = new Character(sdlSetup->GetRenderer(), "data/enemyCharacter.png", 140, 140, 160,200, &cameraX, &cameraY, 1, 1, CollisionRectangle(0,0,160,200), sdlSetup);
}
Main::Main()
{
	quit = false;
}
Main::~Main()
{
	delete sdlSetup;
	delete character;
	delete forestArea;
	delete character;
	delete enemy;
}
void Main::GameLoop(void)
{
	while (!quit && sdlSetup->GetMainEvent()->type != SDL_QUIT)// if player dont push X
	{
		sdlSetup->BeginRender();
		character->Update(forestArea);
		forestArea -> DrawBack();
		enemy->Draw();
		character->DrawStady();
		if (character->CheckIfEnemyIsColidingCharacter(enemy))
		{
			MainCharacter tempMainCharacter = *character;
			Character tempEnemy = *enemy;
		
			Fight *fight;
			fight = new Fight(sdlSetup, &tempMainCharacter, &tempEnemy, forestArea);
			while (fight->FightLoop());
			if (tempMainCharacter.GetHealth() > 0 && tempEnemy.GetHealth() == 0)
				character->SetExperience(tempMainCharacter.GetExperience());
			else if (tempEnemy.GetHealth() > 0 && tempMainCharacter.GetHealth() > 0)
				character->SetHealth(tempMainCharacter.GetHealth());
			character->BrushAsideCharacter(5);
		}
		character->ResetKeyState();
		forestArea -> DrawFront(character->GetY());
		forestArea->Update();
		sdlSetup -> EndRender();
	}
}
bool Main::GetQuit(void)
{
	return quit;
}
void Main::SetQuit(bool updateQuit)
{
	quit = updateQuit;
}