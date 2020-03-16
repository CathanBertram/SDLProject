#include "GameObject.h"

GameObject::GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity)
{
	mRenderer = renderer;
	mTexture = new Texture2D(mRenderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mCollisionRadius = 15.0f;
	frame = 1;
	gravityEnabled = gravity;
	mCircle = Circle2D(mTexture->GetWidth() / 2, mPosition);
}

GameObject::~GameObject()
{
	mRenderer = NULL;
 	delete mRenderer;
	delete mTexture;
}

void GameObject::Render()
{
	mTexture->Render(mPosition, SDL_FLIP_NONE);
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

void GameObject::SetPositionX(Vector2D newPosition)
{
	mPosition.x = newPosition.x;
}

void GameObject::SetPositionY(Vector2D newPosition)
{
	mPosition.y = newPosition.y;
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
