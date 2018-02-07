#include "MainCharacter.h"

MainCharacter::MainCharacter(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int *passedCameraX, int *passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect)
	:Character(passedRenderer,FilePath,x,y,w,h,passedCameraX,passedCameraY, amountOfXFrames, amountOfYFrames, passedCollisonRect)
{
	timeCheck = SDL_GetTicks();
	
	level = 1;
	strength = 15;
	initialHealth = health;
	experience = 0;
	speed = 3;
	luck = 5;
	experienceNeededToNextLevel = 100;
	isAttacking = false;
	mayAttack = true;
	
	beginX = (WINDOW_WIDTH ) / 2;
	beginY = (WINDOW_HEIGHT) / 2;
	
	setHeightCrop(getImageHeight() / AMOUNT_OF_ROWS_CHAR);
	setWidthCrop(getImageWidth() / AMOUNT_OF_COLUMNS_CHAR);
	
	key = idle;
	keyboardState = SDL_GetKeyboardState(NULL);
}
void MainCharacter::update(Environment *environment)
{
	scanKeys();
	moveCharacter();
	CheckCollision(environment);
	//update location of character
	x = *cameraX + beginX;
	y = -*cameraY + beginY;
	//std::cout << "X" << x << std::endl;
	//std::cout << "Y" << y << std::endl;
}
void MainCharacter::ResetKeyState()
{
	key = idle;
}
void MainCharacter::CheckCollision(Environment *environment)
{
	for (int i = 0; i < environment->getTrees().size(); i++)
		if (isColiding(environment->getTrees()[i]->getTrunk()->getCollisonRect()))
			brushAsideCharacter(10);
}
void MainCharacter::brushAsideCharacter(int epsilon)
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
bool MainCharacter::checkIfEnemyisColidingCharacter(Character *enemyCharacter)
{
	if (isColiding(enemyCharacter->getCollisonRect()))
		return true;
	else
		return false;
}
void MainCharacter::scanKeys()
{
	if (keyboardState[SDL_SCANCODE_W])
	{
		playAnimation(1, 5, GO_UP, 150);
		key = moveUp;
	}
	else if (keyboardState[SDL_SCANCODE_S])
	{
		playAnimation(1, 5, GO_DOWN, 150);
		key = moveDown;
	}
	else if (keyboardState[SDL_SCANCODE_A])
	{
		playAnimation(1, 5, GO_LEFT, 150);
		key = moveLeft;
	}
	else if (keyboardState[SDL_SCANCODE_D])
	{
		playAnimation(1, 5, GO_RIGHT, 150);
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
void MainCharacter::setExperience(int exp)
{
	experience += exp;
	if (experience >= experienceNeededToNextLevel)
	{
		level++;
		experienceNeededToNextLevel = 100 * level;
		experience = 0;
		levelUp();
	}
}
void MainCharacter::levelUp()
{
	luck += 5;
	strength += 5;
	defence += 5;
	health = initialHealth + (level -1) * 10;
	//every two levels give 1 speed
	if(level%2 == 0)
		speed += 1;
}
int MainCharacter::getExperience()
{
	return experience;
}
MainCharacter::~MainCharacter()
{

}
