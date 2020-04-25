#include "GameOver.h"
#include "GameManager.h"

GameOver::GameOver(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity) : GameObject(renderer, imagePath, startPosition, gravity)
{
	gravityEnabled = gravity;
	mPosition.x = GameManager::Instance()->camera->GetPosition().x;
	mPosition.y = 0 - SCREEN_HEIGHT;
}

GameOver::~GameOver()
{
}

void GameOver::Render()
{
	GameObject::Render();
}

void GameOver::Update(float deltaTime, SDL_Event e)
{
	if (mPosition.y < 0)
	{
		mPosition.y += 240 * deltaTime;
	}
}
