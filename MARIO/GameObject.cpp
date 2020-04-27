#include "GameObject.h"
#include "GameManager.h"

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
	mTexture = NULL;
	delete mTexture;
}

void GameObject::Render()
{
	mTexture->Render(Vector2D(mPosition.x - GameManager::Instance()->camera->GetRect().x, mPosition.y - GameManager::Instance()->camera->GetRect().y), SDL_FLIP_NONE);
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

void GameObject::SetOldPos()
{
	oldPos = mPosition;
}

void GameObject::AddGravity(float deltaTime)
{
		mPosition.y += GRAVITY * deltaTime;
}

void GameObject::MoveOOB()
{
	mPosition.x = -100;
	mPosition.y = -100;
	gravityEnabled = false;
}
