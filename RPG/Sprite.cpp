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
	SetPicture(FilePath,this-> amountOfXFrames,this->amountOfYFrames);
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
	SetPicture(FilePath, amountOfXFrames, amountOfYFrames);
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
	SetPicture(FilePath, 1, 1);

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
void Sprite::SetAmountOfXFrames(int xFrames)
{
	amountOfXFrames = xFrames;
}
void Sprite::SetAmountOfYFrames(int yFrames)
{
	amountOfYFrames = yFrames;
}
void Sprite::PrepareToFight(std::string Path, int amountOfXFrames, int amountOfYFrames, int x, int y, int w, int h)
{

	this->x = x;
	this->y = y;
	width = w;
	height = h;
	this->amountOfXFrames = amountOfXFrames;
	this->amountOfYFrames = amountOfYFrames;
	SetPicture(Path, amountOfXFrames, amountOfYFrames);

}
void Sprite::SetPicture(std::string Path, int amountOfXFrames, int amountOfYFrames)
{
	image = IMG_LoadTexture(renderer, Path.c_str());

	if (image == NULL)
	{
		std::cout << ("Unable to load image %s! SDL Error: %s\n", "f/f1.bmp", SDL_GetError());
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
SDL_Texture* Sprite::GetImageTexture()
{
	return image;
}
void Sprite::Draw()
{
	Camera.x = rect.x - *cameraX;
	Camera.y = rect.y + *cameraY;

	collisonRect.SetRectangleX(rect.x - *cameraX);
	collisonRect.SetRectangleY(rect.y + *cameraY);

	SDL_RenderCopy(renderer, image, &crop, &Camera);
	SDL_RenderCopy(renderer, collisionImage, NULL, &collisonRect.GetRectangle());
}

void Sprite::DrawStady()
{
	SDL_RenderCopy(renderer, image, &crop, &rect);
	SDL_RenderCopy(renderer, collisionImage, NULL, &collisonRect.GetRectangle());
}
void Sprite::SetX(int x)
{
	rect.x = x;
}
void Sprite::SetY(int y)
{
	rect.y = y;
}
void Sprite::SetHeightCrop(int h)
{
	crop.h = h;
}
void Sprite::SetWidthCrop(int w)
{
	crop.w = w;
}
int Sprite::GetImageHeight()
{
	return imageHeight;
}
int Sprite::GetImageWidth()
{
	return imageWidth;
}
void Sprite::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}
void Sprite::SetCurrentFrame(int frame)
{
	currentFrame = frame;
}
int Sprite::PlayAnimation(int beginFrame, int endFrame, int row, int speed)
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
bool Sprite::IsColiding(CollisionRectangle theColider)
{
	int x = collisonRect.GetRectangle().x;
	int y = collisonRect.GetRectangle().y;
	int w = collisonRect.GetRectangle().w;
	int h = collisonRect.GetRectangle().h;
	int coliderX = theColider.GetRectangleX();
	int coliderY = theColider.GetRectangleY();
	int coliderW = theColider.GetRectangle().w;
	int coliderH = theColider.GetRectangle().h;

	return !(x + w <= coliderX || y + h <= coliderY ||x >= coliderX + coliderW || y >= coliderY + coliderH);
}
int Sprite::GetAmountOfXFrames()
{
	return amountOfXFrames;
}
int Sprite::GetAmountOfYFrames()
{
	return amountOfYFrames;
}
int Sprite::GetWidth()
{
	return width;
}
int Sprite::GetHeight()
{
	return height;
}
CollisionRectangle Sprite::GetCollisonRect()
{
	return collisonRect;
}
SDL_Rect Sprite::GetRect()
{
	return rect;
}
Sprite::~Sprite()
{
	SDL_DestroyTexture(image);
	

}
