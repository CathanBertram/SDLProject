#include "QuestionBlock.h"
QuestionBlock::QuestionBlock(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity) : GameObject(renderer, imagePath, startPosition, gravity)
{
	mPosition = startPosition;
	mCollisionRadius = 15.0f;
	frame = 0;
	slice = 0;
	mSingleSpriteWidth = mTexture->GetWidth() / 7;
	mSingleSpriteHeight = mTexture->GetHeight();

	numOfHits = rand() % 10;
}

QuestionBlock::~QuestionBlock()
{
}

void QuestionBlock::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void QuestionBlock::Update(float deltaTime, SDL_Event e)
{
	frame += deltaTime * 10;
	if (numOfHits <=0)
	{
		isBroken = true;
	}
	if (frame > cFrameTime)
	{
		if (!isBroken)
		{
			slice++;
			frame = 0;
			if (slice >= 6)
			{
				slice = 0;
			}
		}
		else
		{
			slice = 6;
		}
	}
}