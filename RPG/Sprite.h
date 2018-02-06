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

	void Draw();

	void DrawStady();
	virtual void SetX(int x);
	void SetY(int y);
	void SetPosition(int x, int y);

	int GetWidth();
	int GetHeight();
	void SetWidthCrop(int w);
	void SetHeightCrop(int h);
	void SetCurrentFrame(int frame);

	int GetImageWidth();
	int GetImageHeight();
	int PlayAnimation(int beginFrame, int endFrame, int row, int speed);
	
	bool IsColiding(CollisionRectangle theColider);
	CollisionRectangle GetCollisonRect();
	SDL_Rect GetRect();
	void SetPicture(std::string Path, int amountOfXFrames, int amountOfYFrames);
	SDL_Texture* GetImageTexture();
	void SetAmountOfXFrames(int xFrames);
	void SetAmountOfYFrames(int yFrames);
	int GetAmountOfXFrames();
	int GetAmountOfYFrames();
	void PrepareToFight(std::string Path, int amountOfXFrames, int amountOfYFrames, int x, int y, int w, int h);
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

