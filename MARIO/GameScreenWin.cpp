#include "GameScreenWin.h"

GameScreenWin::GameScreenWin(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

GameScreenWin::~GameScreenWin()
{
	mBackgroundTexture = NULL;
}

void GameScreenWin::Render()
{
	mBackgroundTexture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenWin::Update(float deltaTime, SDL_Event e)
{
}

bool GameScreenWin::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundWin.png"))
	{
		std::cout << "Failted to load background texture!";
		return false;
	}
	return false;
}
