#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

GameScreen::GameScreen(SDL_Renderer* renderer, std::string filePath)
{
	mRenderer = renderer;
	if (map != NULL)
	{
		delete map;
		map = NULL;
	}
	map = new TileMap(tileMap, mRenderer, filePath);
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
	delete map;
	map = NULL;
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
}

bool GameScreen::CheckMapColl(GameObject* obj)
{
	if (map != NULL)
	{
		for (int i = 0; i < map->tileMap.size(); i++)
		{
			if (map->tileMap[i]->collidable == true)
			{
				if (Collisions::Instance()->Box(obj->GetCollisionBox(), map->tileMap[i]->GetCollisionBox()))
				{
					return true;
				}
			}
		}
		return false;
	}
	return false;
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
