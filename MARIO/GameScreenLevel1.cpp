#include <iostream>
#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	mLevelMap = NULL;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	mBackgroundTexture = NULL;
	delete mario;
	mario = NULL;
	delete luigi;
	luigi = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	mKoopas.clear();
	mCoins.clear();
	tileMap.clear();
}

void GameScreenLevel1::Render()
{
	//mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE, mBackgroundYPos);
	for (int i = 0; i < map->tileMap.size(); i++)
	{
		map->tileMap[i]->Render();
	}
	mario->Render();
	luigi->Render();
	mPowBlock->Render();
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
	UpdateEnemies(deltaTime, e);
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
		mario->SetPosition(mPos);
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
}

void GameScreenLevel1::UpdatePowBlock(float deltaTime)
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (mario->IsJumping())
			{
				DoScreenshake();
				mPowBlock->TakeAHit();
				mario->CancelJump();
				for (unsigned int i = 0; i < mKoopas.size(); i++)
				{
					mKoopas[i]->Jump(deltaTime);
				}
			}
		}
	}
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), mPowBlock->GetCollisionBox()))
	{
		if (mPowBlock->IsAvailable())
		{
			if (luigi->IsJumping())
			{
				DoScreenshake();
				mPowBlock->TakeAHit();
				luigi->CancelJump();
				for (unsigned int i = 0; i < mKoopas.size(); i++)
				{
					mKoopas[i]->Jump(deltaTime);
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

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter;
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/KoopaSheet.png", position, mLevelMap, direction, true, speed);
	mKoopas.push_back(koopaCharacter);
}

void GameScreenLevel1::CreateCoin(Vector2D position)
{
	//Coin* coin;
	//coin = new Coin(mRenderer, "Images/CoinSheet.png", position);
	mCoins.push_back(new Coin(mRenderer, "Images/CoinSheet.png", position, false));
}

bool GameScreenLevel1::SetUpLevel()
{
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!";
		return false;
	}
	SetLevelMap();
	CreateCoin(Vector2D(200, 96));
	mario = new CharacterMario(mRenderer, "Images/MarioSheet.png", Vector2D(64, 330), mLevelMap, FACING_RIGHT, true);
	luigi = new CharacterLuigi(mRenderer, "Images/LuigiSheet.png", Vector2D(448, 330), mLevelMap, FACING_RIGHT, true);
	mPowBlock = new PowBlock(mRenderer, mLevelMap);
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

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);

}
