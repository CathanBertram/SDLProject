#include <iostream>
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "PowBlock.h"
#include "GameManager.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, std::string filePath) : GameScreen(renderer, filePath)
{
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	mBackgroundTexture = NULL;
}

void GameScreenLevel1::Render()
{
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE, mBackgroundYPos);
	for (int i = 0; i < map->tileMap.size(); i++)
	{
		for (int j = 0; j < map->tileMap[i].size(); j++)
		{
			map->tileMap[i][j]->Render();
		}
	}
	if (mario->GetDead() == false)
		mario->Render();
	if (luigi->GetDead() == false)
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

	for (unsigned int i = 0; i < mQuestionBlock.size(); i++)
	{
		mQuestionBlock[i]->Render();
	}
	flag->Render();
	GameScreen::Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	UpdateEnemies(deltaTime, e);
	if (mScreenshake)
	{
		ShakeScreen(deltaTime);
	}

	if (mario->GetDead() == false)
	{
		mPos = mario->GetPosition();
		GameManager::Instance()->collision->ObjectCollChecks(mario, deltaTime, map);
		mario->Update(deltaTime, e);
	}
	if (luigi->GetDead() == false)
	{
		lPos = luigi->GetPosition();
		GameManager::Instance()->collision->ObjectCollChecks(luigi, deltaTime, map);
		luigi->Update(deltaTime, e);
	}

	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);
		GameManager::Instance()->collision->CoinCollisions(mCoins[i], map, deltaTime);
	}
	for (unsigned int i = 0; i < mQuestionBlock.size(); i++)
	{
		mQuestionBlock[i]->Update(deltaTime, e);
	}
	UpdatePowBlock(deltaTime);
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (mario->GetDead() == false)
		{
			if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
			{
				mCoins[i]->MoveOOB();
				GameManager::Instance()->scoreManager->IncreaseScore(100);
			}
		}
		if (luigi->GetDead() == false)
		{
			if (GameManager::Instance()->collision->Box(luigi->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
			{
				mCoins[i]->MoveOOB();
				GameManager::Instance()->scoreManager->IncreaseScore(100);
			}
		}
	}
	for (int i = 0; i < mQuestionBlock.size(); i++)
	{
		if (mario->GetDead() == false)
		{
			if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), mQuestionBlock[i]->GetCollisionBox()))
			{
				if (!mQuestionBlock[i]->IsBroken())
				{
					mQuestionBlock[i]->DecreaseHits();
					CreateCoin(Vector2D(mQuestionBlock[i]->GetPosition().x, mQuestionBlock[i]->GetPosition().y - mCoins[0]->GetSingleHeight()), true);
					mCoins.back()->Jump(deltaTime, 300);
				}
			}
		}
		if (luigi->GetDead() == false)
		{
			if (GameManager::Instance()->collision->Box(luigi->GetCollisionBox(), mQuestionBlock[i]->GetCollisionBox()))
			{
				if (!mQuestionBlock[i]->IsBroken())
				{
					mQuestionBlock[i]->DecreaseHits();
					CreateCoin(Vector2D(mQuestionBlock[i]->GetPosition().x, mQuestionBlock[i]->GetPosition().y - mCoins[0]->GetSingleHeight()), true);
					mCoins.back()->Jump(deltaTime, 300);
				}
			}
		}
	}
	GameScreen::Update(deltaTime, e);
	if (mario->GetDead() == false )
	{
		if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), flag->GetCollisionBox()))
		{
			levelOver = true;
			GameManager::Instance()->gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
		}
	}
	if (levelOver == false)
	{
		if (luigi->GetDead() == false )
		{
			if (GameManager::Instance()->collision->Box(luigi->GetCollisionBox(), flag->GetCollisionBox()))
			{
				levelOver = true;
				GameManager::Instance()->gameScreenManager->ChangeScreen(SCREEN_LEVEL2);
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
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

