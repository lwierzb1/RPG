#include "MainCharacter.h"

MainCharacter::MainCharacter(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect, SDL_Setup *passedSDL)
	:Character(passedRenderer,FilePath,x,y,w,h,passedCameraX,passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect,passedSDL)
{
	strength = 15;
	key = idle;
	//sdlSetup = passedSDL;
	timeCheck = SDL_GetTicks();
	speed = 3;
	beginX = (WINDOW_WIDTH ) / 2;
	beginY = (WINDOW_HEIGHT) / 2;
	isAttacking = false;
	mayAttack = true;
	SetHeightCrop(GetImageHeight() / AMOUNT_OF_ROWS_CHAR);
	SetWidthCrop(GetImageWidth() / AMOUNT_OF_COLUMNS_CHAR);
	keyboardState = SDL_GetKeyboardState(NULL);
}
void MainCharacter::Update(Environment *environment)
{
	scanKeys();
	moveCharacter();
	CheckCollision(environment);
	//update location of character
	x = *cameraX + beginX;
	y = -*cameraY + beginY;
	//std::cout << "X" << *cameraX << std::endl;
	//std::cout << "Y" << *cameraY << std::endl;
}
void MainCharacter::ResetKeyState()
{
	key = idle;
}
void MainCharacter::CheckCollision(Environment *environment)
{
	for (int i = 0; i < environment->GetTrees().size(); i++)
		if (IsColiding(environment->GetTrees()[i]->GetTrunk()->GetCollisonRect()))
			BrushAsideCharacter(10);
}
void MainCharacter::BrushAsideCharacter(int epsilon)
{
	switch (key)
	{
		case moveUp:
			*cameraY = *cameraY - epsilon;
			break;
		case moveDown:
			*cameraY = *cameraY + epsilon;
			break;
		case moveLeft:
			*cameraX = *cameraX + epsilon;
			break;
		case moveRight:
			*cameraX = *cameraX - epsilon;
			break;
		default:
			break;
	}
}
bool MainCharacter::CheckIfEnemyIsColidingCharacter(Character *enemyCharacter)
{
	if (IsColiding(enemyCharacter->GetCollisonRect()))
		return true;
	else
		return false;
}
void MainCharacter::scanKeys()
{
	if (keyboardState[SDL_SCANCODE_W])
	{
		PlayAnimation(1, 5, GO_UP, 150);
		key = moveUp;
	}
	else if (keyboardState[SDL_SCANCODE_S])
	{
		PlayAnimation(1, 5, GO_DOWN, 150);
		key = moveDown;
	}
	else if (keyboardState[SDL_SCANCODE_A])
	{
		PlayAnimation(1, 5, GO_LEFT, 150);
		key = moveLeft;
	}
	else if (keyboardState[SDL_SCANCODE_D])
	{
		PlayAnimation(1, 5, GO_RIGHT, 150);
		key = moveRight;
	}
}
void MainCharacter::moveCharacter()
{
	if (timeCheck + 10 < (int)SDL_GetTicks())
	{
		switch (key)
		{
			case moveUp:
				*cameraY = *cameraY + speed;
				break;
			case moveDown:
				*cameraY = *cameraY - speed;
				break;
			case moveLeft:
				*cameraX = *cameraX - speed;
				break;
			case moveRight:
				*cameraX = *cameraX + speed;
			default:
				break;
		}
		/*if (*cameraX < 0)
			*cameraX = 0;
		if (*cameraY > 0)
			*cameraY = 0;
			*/
		timeCheck = SDL_GetTicks();
	}
}
void MainCharacter::SetExperience(int exp)
{
	experience = exp;
}
int MainCharacter::GetExperience()
{
	return experience;
}
MainCharacter::~MainCharacter()
{

}
