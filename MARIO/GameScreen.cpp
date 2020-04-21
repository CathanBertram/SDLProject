#include <sstream>
#include "GameScreen.h"
#include "GameManager.h"

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

	SetUpLevel();
}

GameScreen::~GameScreen()
{
	//Delete Character Variables
	mRenderer = NULL;
	delete mario;
	mario = NULL;
	delete luigi;
	luigi = NULL;

	//Clear Vectors
	mKoopas.clear();
	mCoins.clear();
	tileMap.clear();
	mPowBlock.clear();
}

void GameScreen::Render()
{
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	GameManager::Instance()->camera->SetPosition(Rect2D(mario->GetPosition().x, mario->GetPosition().y, mario->GetSingleWidth(), mario->GetSingleHeight()));
	GameManager::Instance()->camera->Update();
}

void GameScreen::CreateCoin(Vector2D position)
{
	mCoins.push_back(new Coin(mRenderer, "Images/CoinSheet.png", position, false));
}

void GameScreen::CreateQuestion(Vector2D position)
{
	mQuestionBlock.push_back(new QuestionBlock(mRenderer, "Images/QuestionBlockSheet.png", position, false));
}

void GameScreen::UpdatePowBlock(float deltaTime)
{
	for (unsigned int i = 0; i < mPowBlock.size(); i++)
	{
		if (GameManager::Instance()->collision->Box(mario->GetCollisionBox(), mPowBlock[i]->GetCollisionBox()))
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
		if (GameManager::Instance()->collision->Box(luigi->GetCollisionBox(), mPowBlock[i]->GetCollisionBox()))
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

void GameScreen::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mKoopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < mKoopas.size(); i++)
		{
			GameManager::Instance()->collision->ObjectCollChecks(mKoopas[i], deltaTime, map);
			if (mKoopas[i]->GetPosition().y > 0.0f)
			{
				if (mKoopas[i]->GetPosition().x < (float)(-mKoopas[i]->GetCollisionBox().w * 0.5f) ||
					mKoopas[i]->GetPosition().x > SCREEN_WIDTH - (float)(mKoopas[i]->GetCollisionBox().w * 0.55f))
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
				if (GameManager::Instance()->collision->Circle(Circle2D(mKoopas[i]->GetCollisionRadius(), mKoopas[i]->GetPosition()), Circle2D(mario->GetCollisionRadius(), mario->GetPosition())))
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

void GameScreen::SetUpLevel()
{
	//Create Characters
	mario = new CharacterMario(mRenderer, "Images/MarioSheet.png", map->GetMarioPos(), FACING_RIGHT, true);
	luigi = new CharacterLuigi(mRenderer, "Images/LuigiSheet.png", map->GetLuigiPos(), FACING_RIGHT, true);
	flag = new Flag(mRenderer, "Images/Flag.png", map->GetFlagPos(), true);
	//Create Koopas
	for (unsigned i = 0; i < map->GetKoopaSize(); i++)
	{
		CreateKoopa(map->GetKoopaPos(i), FACING_LEFT, KOOPA_SPEED);
	}
	//Create PowBlocks
	for (unsigned i = 0; i < map->GetPowBlockSize(); i++)
	{
		CreatePowBlock(map->GetPowBlockPos(i));
	}
	//Create Coins
	for (unsigned i = 0; i < map->GetCoinSize(); i++)
	{
		CreateCoin(map->GetCoinPos(i));
	}
	for (int i = 0; i < map->GetQuestionSize(); i++)
	{
		CreateQuestion(map->GetQuestionPos(i));
	}
}

void GameScreen::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter;
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/KoopaSheet.png", position, direction, true, speed);
	mKoopas.push_back(koopaCharacter);
}

void GameScreen::CreatePowBlock(Vector2D position)
{
	mPowBlock.push_back(new PowBlock(mRenderer, position));
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
