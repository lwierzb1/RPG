#include "Tree.h"

Tree::Tree(SDL_setup *sdlSetup, int x, int y, int *cameraX, int *cameraY)
{
	Properties properties = PropertiesParser::Read("GameConfig.properties");

	this->x = x;
	this->y = y;

	this->cameraX = cameraX;
	this->cameraY = cameraY;
	
	trunk = new Sprite(sdlSetup->getRenderer(), "data/environment/treeTrunk.png", x, y, 
			stoi(properties.getProperty("TrunkWidth")), 
			stoi(properties.getProperty("TrunkHeight")), cameraX, cameraY, 
			CollisionRectangle(stoi(properties.getProperty("TrunkCollisionX")),
							   stoi(properties.getProperty("TrunkCollisionY")),
							   stoi(properties.getProperty("TrunkCollisionWidth")),
							   stoi(properties.getProperty("TrunkCollisionHeight"))));
	
	branch = new Sprite(sdlSetup->getRenderer(), "data/environment/treeBranch.png", 
							   x - stoi(properties.getProperty("BranchX")), 
							   y - stoi(properties.getProperty("BranchY")),
							   stoi(properties.getProperty("BranchWidth")),
							   stoi(properties.getProperty("BranchHeight")), 
							   cameraX, cameraY, CollisionRectangle());
}
void Tree::drawTree()
{
	trunk->draw();
	branch->draw();
}
int Tree::getX()
{
	return x;
}
int Tree::getY()
{
	return y;
}
Sprite* Tree::getTrunk()
{
	return trunk;
}
Sprite* Tree::getBranch()
{
	return branch;
}
Tree::~Tree()
{
	delete trunk;
	delete branch;
}
