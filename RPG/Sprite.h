#pragma once
#include "stdafx.h"
#include "CollisionRectangle.h"
class Sprite
{
public:
	Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int*passedCameraX, int*passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect);
	Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int*passedCameraX, int*passedCameraY, CollisionRectangle passedCollisonRect);
	Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, CollisionRectangle passedCollisonRect);
	Sprite();
	~Sprite();

	void draw();

	void drawStady();
	virtual void setX(int x);
	void setY(int y);
	void setPosition(int x, int y);

	int getWidth();
	int getHeight();
	void setWidthCrop(int w);
	void setHeightCrop(int h);
	void setCurrentFrame(int frame);

	int getImageWidth();
	int getImageHeight();
	int playAnimation(int beginFrame, int endFrame, int row, int speed);
	
	bool isColiding(CollisionRectangle theColider);
	CollisionRectangle getCollisonRect();
	SDL_Rect getRect();
	void setPicture(std::string Path, int amountOfXFrames, int amountOfYFrames);
	SDL_Texture* getImagetexture();
	void setAmountOfXFrames(int xFrames);
	void setAmountOfYFrames(int yFrames);
	int getAmountOfXFrames();
	int getAmountOfYFrames();
	void prepareToFight(std::string Path, int amountOfXFrames, int amountOfYFrames, int x, int y, int w, int h);
private:
	SDL_Texture *image;
	SDL_Texture *collisionImage;
	SDL_Rect rect;
	SDL_Rect crop;
	SDL_Rect  Camera;
	SDL_Renderer *renderer;

	int imageWidth;
	int imageHeight;
	int currentFrame;
	int animationDelay;
	int amountOfXFrames;
	int amountOfYFrames;
protected:
	int x;
	int y;
	int width;
	int height;
	int *cameraX;
	int *cameraY;
	CollisionRectangle collisonRect;
};

