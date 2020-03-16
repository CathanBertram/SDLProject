#include <iostream>
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer, std::string filePath) : GameScreen(renderer, filePath)
{
	mLevelMap = NULL;
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
		map->tileMap[i]->Render();
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

}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//UpdateEnemies(deltaTime, e);
	if (mScreenshake)
	{
		ShakeScreen(deltaTime);
	}

	mPos = mario->GetPosition();
	lPos = luigi->GetPosition();
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	/*if (Collisions::Instance()->Circle(Circle2D(mario->GetCollisionRadius(), mario->GetPosition()), Circle2D(luigi->GetCollisionRadius(), luigi->GetPosition())))
	{
		mario->SetPosition(mPos);
		luigi->SetPosition(lPos);
	}*/
	if (CheckMapColl(mario))
	{
		mario->SetPositionY(mPos);
		mario->gravityEnabled = false;
	}
	else
	{
		mario->gravityEnabled = true;
	}
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		mario->SetPosition(mPos);
		luigi->SetPosition(lPos);
	}
	for (unsigned int i = 0; i < mCoins.size(); i++)
	{
		mCoins[i]->Update(deltaTime, e);
	}
	UpdatePowBlock(deltaTime);
	for (int i = 0; i < mCoins.size(); i++)
	{
		if (Collisions::Instance()->Box(mario->GetCollisionBox(), mCoins[i]->GetCollisionBox()))
		{
			score += 100;
			mCoins[i]->SetPosition(Vector2D(-1000, -1000));
		}
	}
	std::cerr << score << std::endl;
}

void GameScreenLevel1::UpdatePowBlock(float deltaTime)
{
	for (unsigned int i = 0; i < mPowBlock.size(); i++)
	{

		if (Collisions::Instance()->Box(mario->GetCollisionBox(), mPowBlock[i]->GetCollisionBox()))
		{
			if (mPowBlock[i]->IsAvailable())
			{
				if (mario->IsJumping())
				{
					DoScreenshake();
					mPowBlock[i]->TakeAHit();
					mario->CancelJump();
					for (unsigned int i = 0; i < mKoopas.size(); i++)
					{
						mKoopas[i]->Jump(deltaTime);
					}
				}
			}
		}
		if (Collisions::Instance()->Box(luigi->GetCollisionBox(), mPowBlock[i]->GetCollisionBox()))
		{
			if (mPowBlock[i]->IsAvailable())
			{
				if (luigi->IsJumping())
				{
					DoScreenshake();
					mPowBlock[i]->TakeAHit();
					luigi->CancelJump();
					for (unsigned int i = 0; i < mKoopas.size(); i++)
					{
						mKoopas[i]->Jump(deltaTime);
					}
				}
			}
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mKoopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mKoopas.size(); i++)
		{
			if (mKoopas[i]->GetPosition().y > 0.0f)
			{
				if (mKoopas[i]->GetPosition().x < (float)(-mKoopas[i]->GetCollisionBox().w*0.5f) ||
					mKoopas[i]->GetPosition().x > SCREEN_WIDTH - (float)(mKoopas[i]->GetCollisionBox().w*0.55f))
				{
					mKoopas[i]->SetAlive(false);
					mKoopas[i]->Jump(deltaTime);
				}
			}
			
			mKoopas[i]->Update(deltaTime, e);

			if ((mKoopas[i]->GetPosition().y > 0.0f || mKoopas[i]->GetPosition().y <= 64.0f) && (mKoopas[i]->GetPosition().x < 64.0f || mKoopas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore Collisions if behind pipe
				//mKoopas[i]->Jump(deltaTime);
			}
			else
			{
				if (Collisions::Instance()->Circle(Circle2D(mKoopas[i]->GetCollisionRadius(), mKoopas[i]->GetPosition()), Circle2D(mario->GetCollisionRadius(), mario->GetPosition())))
				{
					//Set Mario To Dead
				}
			}

			if (!mKoopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	std::cerr << "yes" << std::endl;
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundLevel.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
	SetLevelMap();
	CreateCoin(Vector2D(200, 96));
	//mPowBlock = new PowBlock(mRenderer, mLevelMap);
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

	mScreenshake = false;
	mBackgroundYPos = 0.0f;
	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
									{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
									{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };
	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}
	mLevelMap = new LevelMap(map);

}
