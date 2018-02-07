#include "stdafx.h"
#include "Main.h"


Main::Main(int passedScreenWidth, int passedScreenHeight)
{
	quit = false;
	cameraX = 0;
	cameraY = 0;
	screenWidth = passedScreenWidth;
	screenHeight = passedScreenHeight;
	sdlSetup = new SDL_setup(&quit, screenWidth, screenHeight);
	forestArea = new Environment(sdlSetup, screenWidth, screenHeight, &cameraX, &cameraY);
	character = new MainCharacter(sdlSetup->getRenderer(), "data/character.png", (WINDOW_WIDTH) / 2, (WINDOW_HEIGHT) / 2,100,120, &cameraX, &cameraY, 6, 4, CollisionRectangle((WINDOW_WIDTH) / 2, (WINDOW_HEIGHT) / 2 *1.25, 100, 120*0.3), sdlSetup);
	enemy = new Character(sdlSetup->getRenderer(), "data/enemyCharacter.png", 140, 140, 160,200, &cameraX, &cameraY, 1, 1, CollisionRectangle(0,0,160,200), sdlSetup);
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
	while (!quit && sdlSetup->getMainEvent()->type != SDL_QUIT)// if player dont push X
	{
		sdlSetup->beginRender();
		character->update(forestArea);
		forestArea -> drawBack();
		enemy->draw();
		character->drawStady();
		if (character->checkIfEnemyisColidingCharacter(enemy))
		{
			MainCharacter tempMainCharacter = *character;
			Character tempEnemy = *enemy;
		
			Fight *fight;
			fight = new Fight(sdlSetup, &tempMainCharacter, &tempEnemy, forestArea);
			while (fight->fightLoop());
			if (tempMainCharacter.getHealth() > 0 && tempEnemy.getHealth() == 0)
				character->setExperience(tempMainCharacter.getExperience());
			else if (tempEnemy.getHealth() > 0 && tempMainCharacter.getHealth() > 0)
				character->setHealth(tempMainCharacter.getHealth());
			character->brushAsideCharacter(5);
		}
		character->ResetKeyState();
		forestArea -> drawFront(character->getY());
		forestArea->update();
		sdlSetup -> endRender();
	}
}
bool Main::getQuit(void)
{
	return quit;
}
void Main::setQuit(bool updateQuit)
{
	quit = updateQuit;
}