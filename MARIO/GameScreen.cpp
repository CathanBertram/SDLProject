#include <sstream>
#include "GameScreen.h"
#include "GameManager.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
	gameEnd = false;
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

	gameEnd = false;
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
	if (gameEnd)
	{
		gameOver->Render();
	}
}

void GameScreen::Update(float deltaTime, SDL_Event e)
{
	if (mario->GetDead() == false)
	{
		GameManager::Instance()->camera->SetPosition(Rect2D(mario->GetPosition().x, mario->GetPosition().y, mario->GetSingleWidth(), mario->GetSingleHeight()));
	}
	else
	{
		if (luigi->GetDead() == false)
		{
			GameManager::Instance()->camera->SetPosition(Rect2D(luigi->GetPosition().x, luigi->GetPosition().y, luigi->GetSingleWidth(), luigi->GetSingleHeight()));
		}
		else
		{
			//GameOver
			if (gameEnd == false)
			{
				CreateGameOver();
			}
		}
		if (e.key.keysym.sym == SDLK_SPACE)
		{
			GameManager::Instance()->gameScreenManager->ChangeScreen(GameManager::Instance()->gameScreenManager->GetCurrentScreen());
			gameEnd = false;
		}
	}
	if (gameEnd)
	{
		gameOver->Update(deltaTime, e);
	}
	GameManager::Instance()->camera->Update();
}


void GameScreen::UpdatePowBlock(float deltaTime)
{
	for (unsigned int i = 0; i < mPowBlock.size(); i++)
	{
		if (mario->GetDead() == false)
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
							mKoopas[i]->Injure();
						}
					}
				}
			}
		}
		if (luigi->GetDead() == false)
		{
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
							mKoopas[i]->Injure();
						}
					}
				}
			}
		}

		if (!mPowBlock[i]->IsAvailable())
		{
			mPowBlock.erase(mPowBlock.begin() + i);
		}
	}
}

void GameScreen::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!mKoopas.empty())
	{
		for (unsigned int i = 0; i < mKoopas.size(); i++)
		{
			mKoopas[i]->Update(deltaTime, e);

			GameManager::Instance()->collision->ObjectCollChecks(mKoopas[i], deltaTime, map);
			if (GameManager::Instance()->collision->CheckMapCollLeft(mKoopas[i], deltaTime, map) == true)
			{
				mKoopas[i]->Jump(deltaTime);
			}
			if (GameManager::Instance()->collision->CheckMapCollRight(mKoopas[i], deltaTime, map) == true)
			{
				mKoopas[i]->Jump(deltaTime);
			}


			if (mKoopas[i]->GetAlive())
			{
				mKoopas.erase(mKoopas.begin() + i);
			}

			//Collisions With Mario
			if (mKoopas[i]->GetInjured() == false)
			{
				if (mario->GetDead() == false)
				{
					if (GameManager::Instance()->collision->Circle(mario, mKoopas[i]))
					{
						//mario dies
						mario->SetDead();
					}
				}
				if (luigi->GetDead() == false)
				{
					if (GameManager::Instance()->collision->Circle(luigi, mKoopas[i]))
					{
						//luigi dies
						luigi->SetDead();
					}
				}
			}
			else if (mKoopas[i]->GetInjured() == true)
			{
				if (mario->GetDead() == false)
				{
					if (GameManager::Instance()->collision->Circle(mario, mKoopas[i]))
					{
						//Kill Koopa And Increase Score
						mKoopas.erase(mKoopas.begin() + i);
						GameManager::Instance()->scoreManager->IncreaseScore(100);
					}
				}

				if (luigi->GetDead() == false)
				{
					if (GameManager::Instance()->collision->Circle(luigi, mKoopas[i]))
					{
						//Kill Koopa And Increase Score
						mKoopas.erase(mKoopas.begin() + i);
						GameManager::Instance()->scoreManager->IncreaseScore(100);
					}
				}
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
		CreateCoin(map->GetCoinPos(i), false);
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

void GameScreen::CreateCoin(Vector2D position, bool gravity)
{
	mCoins.push_back(new Coin(mRenderer, "Images/CoinSheet.png", position, gravity));
}

void GameScreen::CreateQuestion(Vector2D position)
{
	mQuestionBlock.push_back(new QuestionBlock(mRenderer, "Images/QuestionBlockSheet.png", position, false));
}

void GameScreen::CreateGameOver()
{
	gameOver = new GameOver(mRenderer, "Images/GameOver.png", Vector2D(0, 0), true);
	gameEnd = true;
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
