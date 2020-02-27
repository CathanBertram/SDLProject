#include <iostream>
#include "GameScreenIntro.h"
#include "Texture2D.h"

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenIntro::~GameScreenIntro()
{
	mBackgroundTexture = NULL;
}

void GameScreenIntro::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
}

bool GameScreenIntro::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundSplash.png"))
	{
		std::cout << "Failted to load background texture!";
		return false;
	}
	return false;
}
