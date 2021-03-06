#include "Environment.h"

Environment::Environment(SDL_setup *sdlSetup, int screenWidth, int screenHeight, int *cameraX, int *cameraY)
{
	this->sdlSetup = sdlSetup;
	for (int i = 0; i < COLUMNS_GRASS; i++)
		for (int j = 0; j < ROWS_GRASS; j++)
			grass[i][j] = new Sprite(sdlSetup->getRenderer(), "data/environment/grass.png", screenWidth * i, screenHeight * j, screenWidth, screenHeight, cameraX, cameraY, CollisionRectangle(0, 0, 0, 0));
	
	this->cameraX = cameraX;
	this->cameraY = cameraY;
	keyPressed = true;
	
	arena = new Sprite(sdlSetup->getRenderer(), "data/environment/forestArena.png", 0, 0, screenWidth, screenHeight, CollisionRectangle());
	mode = gamePlay;
	loadFromFile();
}
void Environment::drawBack()
{
	for (int i = 0; i < COLUMNS_GRASS; i++)
		for (int j = 0; j < ROWS_GRASS; j++)
			grass[i][j]->draw();
	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
			(*i)->drawTree();
}
void Environment::drawFront(int characterY)
{
	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
	{
		if ((*i)->getY() >= characterY)
			(*i)->drawTree();
	}
}
void Environment::saveToFile()
{
	string treesPosition = "";
	
	Properties properties;
	
	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
		treesPosition += to_string((*i)->getX()) + "$" + to_string((*i)->getY()) + "$";
	
	properties.AddProperty("Trees", treesPosition);
	PropertiesParser::Write("Map.properties", properties);
	
	cout << "Level saved!" << endl;
}
void Environment::loadFromFile()
{
	vector<string> tree;
	Properties properties = PropertiesParser::Read("Map.properties");
	string line = properties.getProperty("Trees");
	char x[] = "$";
	tree = PropertiesParser::Split(line, x);
	//current number of iteration
	int iteration = 0;
	//temp X for Tree
	int tempX = 0;
	//temo Y for Tree
	int tempY = 0;
	for (vector<string>::iterator i = tree.begin(); i != tree.end(); ++i)
	{
		if(iteration%2 != 0) // every second value is Y 
			tempY = stoi((*i));
		else
			tempX = stoi((*i)); // first,third,fifth... is X
		if (iteration % 2 != 0 && iteration != 0) //every two iteration create tree
			trees.push_back(new Tree(sdlSetup, tempX, tempY, cameraX, cameraY));
		iteration++;
	}
}
void Environment::update()
{
	if (mode == levelCreation)
	{
		if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F11)
			{
				saveToFile();
				keyPressed = true;
			}
		}
		if (sdlSetup->getMainEvent()->type == SDL_KEYUP)
		{
			if (keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F11)
				keyPressed = false;
		}
		if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F1)
			{
				trees.push_back(new Tree(sdlSetup, *cameraX + 100 + (WINDOW_WIDTH) / 2 ,-*cameraY + 100 + (WINDOW_HEIGHT) / 2 , cameraX, cameraY));
				keyPressed = true;
			}
		}
		if (sdlSetup->getMainEvent()->type == SDL_KEYUP)
		{
			if (keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F1)
				keyPressed = false;
		}
		if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
		{
			if (!keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F2)
			{
				if (trees.size() > 0)
				{
					delete trees[trees.size() - 1]; //delete last tree
					trees.pop_back(); // get rid of it in vector
				}
				keyPressed = true;
			}
		}
		if (sdlSetup->getMainEvent()->type == SDL_KEYUP)
		{
			if (keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F2)
				keyPressed = false;
		}
	}
	if (sdlSetup->getMainEvent()->type == SDL_KEYDOWN)
	{
		if (!keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F12)
		{
			if (mode == levelCreation)
			{
				cout << "LEVEL CREATION MODE OFF" << endl;
				mode = gamePlay;
			}
			else if (mode == gamePlay)
			{
				cout << "LEVEL CREATION MODE ON" << endl;
				mode = levelCreation;
			}
			keyPressed = true;
		}
	}
	if (sdlSetup->getMainEvent()->type == SDL_KEYUP)
	{
		if (keyPressed && sdlSetup->getMainEvent()->key.keysym.sym == SDLK_F12)
			keyPressed = false;
	}
}
vector<Tree*> Environment::getTrees()
{
	return trees;
}
void Environment::drawArena()
{
	arena->drawStady();
}
Environment::~Environment()
{
	for (int i = 0; i < COLUMNS_GRASS; i++)
		for (int j = 0; j < ROWS_GRASS; j++)
			delete grass[i][j];
	for (vector<Tree*>::iterator i = trees.begin(); i != trees.end(); ++i)
		delete (*i);
	trees.clear();
}
