#include "Coin.h"

Coin::Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity) : GameObject(renderer, imagePath, startPosition, gravity)
{
	mPosition = startPosition;
	mCollisionRadius = 15.0f;
	frame = 0;
	slice = 0;
	mSingleSpriteWidth = mTexture->GetWidth() / 4;
	mSingleSpriteHeight = mTexture->GetHeight();
	mPosition.x += (TILE_WIDTH - mSingleSpriteWidth)/2;
	mPosition.y += (TILE_HEIGHT - mSingleSpriteHeight)/2;
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
