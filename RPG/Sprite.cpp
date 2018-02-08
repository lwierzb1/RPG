#include "Sprite.h"

Sprite::Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int*passedCameraX, int*passedCameraY, int amountOfXFrames, int amountOfYFrames, CollisionRectangle passedCollisonRect)
{
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	collisonRect = passedCollisonRect;
	image = NULL;
	renderer = passedRenderer;
	this->amountOfXFrames = amountOfXFrames;
	this->amountOfYFrames = amountOfYFrames;
	setPicture(FilePath, this->amountOfXFrames, this->amountOfYFrames);
	/*collisionImage = IMG_LoadTexture(renderer, "Data/Debug/CollisionBox.png");
	if (collisionImage == NULL)
	{
	std::cout << "Couldn't load Collision Image" << FilePath.c_str() << std::endl;
	}*/
	currentFrame = 0;
	cameraX = passedCameraX;
	cameraY = passedCameraY;
	Camera.x = rect.x;
	Camera.y = rect.y;
	Camera.h = rect.h;
	Camera.w = rect.w;
}
Sprite::Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, int*passedCameraX, int*passedCameraY, CollisionRectangle passedCollisonRect)
{
	this->x = x;
	this->y = y;
	width = w;
	height = h;
	collisonRect = passedCollisonRect;
	image = NULL;
	renderer = passedRenderer;
	amountOfXFrames = 1;
	amountOfYFrames = 1;
	setPicture(FilePath, amountOfXFrames, amountOfYFrames);
	currentFrame = 0;
	/*collisionImage = IMG_LoadTexture(renderer, "Data/Debug/CollisionBox.png");
	if (collisionImage == NULL)
	{
	std::cout << "Couldn't load Collision Image" << FilePath.c_str() << std::endl;
	}*/
	cameraX = passedCameraX;
	cameraY = passedCameraY;

	Camera.x = rect.x;
	Camera.y = rect.y;
	Camera.h = rect.h;
	Camera.w = rect.w;
}
Sprite::Sprite(SDL_Renderer *passedRenderer, std::string FilePath, int x, int y, int w, int h, CollisionRectangle passedCollisonRect)
{
	this->x = x;
	this->y = y;

	width = w;
	height = h;
	collisonRect = passedCollisonRect;
	image = NULL;
	renderer = passedRenderer;
	this->amountOfXFrames = amountOfXFrames;
	this->amountOfYFrames = amountOfYFrames;
	setPicture(FilePath, 1, 1);

	/*collisionImage = IMG_LoadTexture(renderer, "Data/Debug/CollisionBox.png");
	if (collisionImage == NULL)
	{
	std::cout << "Couldn't load Collision Image" << FilePath.c_str() << std::endl;
	}*/
	currentFrame = 0;

}
Sprite::Sprite()
{

}
void Sprite::setAmountOfXFrames(int xFrames)
{
	amountOfXFrames = xFrames;
}
void Sprite::setAmountOfYFrames(int yFrames)
{
	amountOfYFrames = yFrames;
}
void Sprite::changeImage(std::string Path, int amountOfXFrames, int amountOfYFrames, int x, int y, int w, int h)
{

	this->x = x;
	this->y = y;
	width = w;
	height = h;
	this->amountOfXFrames = amountOfXFrames;
	this->amountOfYFrames = amountOfYFrames;
	setPicture(Path, amountOfXFrames, amountOfYFrames);

}
void Sprite::setPicture(std::string Path, int amountOfXFrames, int amountOfYFrames)
{
	image = IMG_LoadTexture(renderer, Path.c_str());

	if (image == NULL)
	{
		std::cout << ("Unable to load image %s! SDL Error: %s\n", Path.c_str(), SDL_GetError());
	}
	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;
	SDL_QueryTexture(image, NULL, NULL, &imageWidth, &imageHeight);

	crop.x = 0;
	crop.y = 0;
	crop.w = imageWidth / amountOfXFrames;
	crop.h = imageHeight / amountOfYFrames;
}
SDL_Texture* Sprite::getImagetexture()
{
	return image;
}
void Sprite::draw()
{
	Camera.x = rect.x - *cameraX;
	Camera.y = rect.y + *cameraY;

	collisonRect.setRectangleX(rect.x - *cameraX);
	collisonRect.setRectangleY(rect.y + *cameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);
	SDL_RenderCopy(renderer, collisionImage, NULL, &collisonRect.getRectangle());
}

void Sprite::drawStady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
	SDL_RenderCopy(renderer, collisionImage, NULL, &collisonRect.getRectangle());
}
void Sprite::setX(int x)
{
	rect.x = x;
}
void Sprite::setY(int y)
{
	rect.y = y;
}
void Sprite::setHeightCrop(int h)
{
	crop.h = h;
}
void Sprite::setWidthCrop(int w)
{
	crop.w = w;
}
int Sprite::getImageHeight()
{
	return imageHeight;
}
int Sprite::getImageWidth()
{
	return imageWidth;
}
void Sprite::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void Sprite::setCurrentFrame(int frame)
{
	currentFrame = frame;
}
int Sprite::playAnimation(int beginFrame, int endFrame, int row, int speed)
{

	if (animationDelay + speed < (int)SDL_GetTicks())
	{
		if (endFrame <= currentFrame)
		{
			currentFrame = beginFrame;
			return 0;
		}
		else
			currentFrame++;
		crop.x = currentFrame * imageWidth / amountOfXFrames;
		crop.y = row * imageHeight / amountOfYFrames;
		crop.w = imageWidth / amountOfXFrames; //six frames in width
		crop.h = imageHeight / amountOfYFrames; //four frames in height
		animationDelay = SDL_GetTicks();
	}
	return 1;
}
bool Sprite::isColiding(CollisionRectangle theColider)
{
	int x = collisonRect.getRectangle().x;
	int y = collisonRect.getRectangle().y;
	int w = collisonRect.getRectangle().w;
	int h = collisonRect.getRectangle().h;
	int coliderX = theColider.getRectangleX();
	int coliderY = theColider.getRectangleY();
	int coliderW = theColider.getRectangle().w;
	int coliderH = theColider.getRectangle().h;

	return !(x + w <= coliderX || y + h <= coliderY || x >= coliderX + coliderW || y >= coliderY + coliderH);
}
int Sprite::getAmountOfXFrames()
{
	return amountOfXFrames;
}
int Sprite::getAmountOfYFrames()
{
	return amountOfYFrames;
}
int Sprite::getWidth()
{
	return width;
}
int Sprite::getHeight()
{
	return height;
}
CollisionRectangle Sprite::getCollisonRect()
{
	return collisonRect;
}
SDL_Rect Sprite::getRect()
{
	return rect;
}
Sprite::~Sprite()
{
	SDL_DestroyTexture(image);

}
