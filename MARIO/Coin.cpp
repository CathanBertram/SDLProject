#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mCollisionRadius = 15.0f;
	frame = 0;
	slice = 0;
	mSingleSpriteWidth = mTexture->GetWidth() / 4;
	mSingleSpriteHeight = mTexture->GetHeight();
	std::cerr << mSingleSpriteWidth << "   " << mSingleSpriteHeight << std::endl;
}

Coin::~Coin()
{
}

void Coin::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void Coin::Update(float deltaTime, SDL_Event e)
{
	frame += deltaTime * 10;
	if (frame > cFrameTime)
	{
		slice++;
		frame = 0;
	}
	if (slice >= 4)
	{
		slice = 0;
	}
}
