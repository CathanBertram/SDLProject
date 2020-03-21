#include "GameScreenLevel2.h"
#include "GameManager.h"

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer, std::string filePath) : GameScreen(renderer, filePath)
{
	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
}

void GameScreenLevel2::Render()
{
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE, mBackgroundYPos);
	for (int i = 0; i < map->tileMap.size(); i++)
	{
		for (int j = 0; j < map->tileMap[i].size(); j++)
		{
			map->tileMap[i][j]->Render();
		}
	}
	mario->Render();
	luigi->Render();
	for (unsigned int i = 0; i < mPowBlock.size(); i++)
	{
		mPowBlock[i]->Render();
	}
	for (unsigned int i = 0; i < mKoopas.size(); i++)
	{
		mKoopas[i]->Render();
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Render();
	}

	flag->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//UpdateEnemies(deltaTime, e);
	if (mScreenshake)
	{
		ShakeScreen(deltaTime);
	}

	GameManager::Instance()->collision->ObjectCollChecks(mario, deltaTime, map);
	GameManager::Instance()->collision->ObjectCollChecks(luigi, deltaTime, map);

	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);
	}
	UpdatePowBlock(deltaTime);
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
		{
			mCoins[i]->SetPosition(Vector2D(-1000, -1000));
		}
	}
	if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), flag->GetCollisionBox()))
	{
		GameManager::Instance()->gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
	}
}

bool GameScreenLevel2::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundLevel.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}

	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	return true;
}
