#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, bool gravity)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mCollisionRadius = 15.0f;
	frame = 1;
	gravityEnabled = gravity;
}

GameObject::~GameObject()
{
	delete mRenderer;
	mRenderer = NULL;
	delete mTexture;
}

void GameObject::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x),(int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

void GameObject::Update(float deltaTime, SDL_Event e)
{
	if (gravityEnabled)
	{
		AddGravity(deltaTime);
	}
}

void GameObject::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition;
}

Vector2D GameObject::GetPosition()
{
	return mPosition;
}

void GameObject::AddGravity(float deltaTime)
{
	if (mPosition.y < SCREEN_HEIGHT - 42)
	{
		mPosition.y += GRAVITY * deltaTime;
	}
}
