#include "Flag.h"
#include "GameManager.h"

Flag::Flag(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity) :GameObject(renderer, imagePath, startPosition, gravity)
{
	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();
	mPosition.y = mPosition.y - mSingleSpriteHeight + 32;
}

Flag::~Flag()
{
}

void Flag::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x - GameManager::Instance()->camera->GetRect().x),(int)(mPosition.y - GameManager::Instance()->camera->GetRect().y), mSingleSpriteWidth, mSingleSpriteHeight };

	mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
}

void Flag::Update(float deltaTime, SDL_Event e)
{
}
