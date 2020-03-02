#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	map = new TileMap(tileMap, mRenderer, "Level/1.txt");
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

void GameScreen::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

void GameScreen::ShakeScreen(float deltaTime)
{
	mScreenshakeTime -= deltaTime;
	mWobble++;
	mBackgroundYPos = sin(mWobble);
	mBackgroundYPos *= 3.0f;

	if (mScreenshakeTime <=0.0f)
	{
		mScreenshake = false;
		mBackgroundYPos = 0.0f;
		mWobble = 0.0f;
	}

}
