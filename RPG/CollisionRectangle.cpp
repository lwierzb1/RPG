#include "CollisionRectangle.h"


CollisionRectangle::CollisionRectangle(int x, int y, int w, int h)
{
	offsetX = x;
	offsetY = y;
	SetRectangle(0, 0,w, h);
}
CollisionRectangle::CollisionRectangle() 
{
	offsetX = 0;
	offsetY = 0;
	SetRectangle(0, 0, 0, 0);
}
void CollisionRectangle::SetRectangle(int x, int y, int w, int h)
{
	collisionRect.x = x + offsetX;
	collisionRect.y = y + offsetY;
	collisionRect.w = w;
	collisionRect.h = h;
}
int CollisionRectangle::GetRectangleX()
{
	return collisionRect.x;
}
int CollisionRectangle::GetRectangleY()
{
	return collisionRect.y;
}
void CollisionRectangle::SetRectangleX(int x)
{
	collisionRect.x = x + offsetX;
}
void CollisionRectangle::SetRectangleY(int y)
{
	collisionRect.y = y + offsetY;
}
SDL_Rect CollisionRectangle::GetRectangle()
{
	return collisionRect;
}
CollisionRectangle::~CollisionRectangle()
{
}
