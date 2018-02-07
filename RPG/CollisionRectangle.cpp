#include "CollisionRectangle.h"


CollisionRectangle::CollisionRectangle(int x, int y, int w, int h)
{
	offsetX = x;
	offsetY = y;
	setRectangle(0, 0,w, h);
}
CollisionRectangle::CollisionRectangle() 
{
	offsetX = 0;
	offsetY = 0;
	setRectangle(0, 0, 0, 0);
}
void CollisionRectangle::setRectangle(int x, int y, int w, int h)
{
	collisionRect.x = x + offsetX;
	collisionRect.y = y + offsetY;
	collisionRect.w = w;
	collisionRect.h = h;
}
int CollisionRectangle::getRectangleX()
{
	return collisionRect.x;
}
int CollisionRectangle::getRectangleY()
{
	return collisionRect.y;
}
void CollisionRectangle::setRectangleX(int x)
{
	collisionRect.x = x + offsetX;
}
void CollisionRectangle::setRectangleY(int y)
{
	collisionRect.y = y + offsetY;
}
SDL_Rect CollisionRectangle::getRectangle()
{
	return collisionRect;
}
CollisionRectangle::~CollisionRectangle()
{
}
