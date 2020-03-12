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
	map = new TileMap(tileMap, mRenderer, filePath, this);
	std::cerr << " yes papi" << std::endl;
}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
	delete mario;
	mario = NULL;
	delete luigi;
	luigi = NULL;
	
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

void GameScreen::CreateCoin(Vector2D position)
{
	//Coin* coin;
	//coin = new Coin(mRenderer, "Images/CoinSheet.png", position);
	mCoins.push_back(new Coin(mRenderer, "Images/CoinSheet.png", position, false));
}

void GameScreen::CreateMario(Vector2D position)
{
	CharacterMario* mario;
	mario = new CharacterMario(mRenderer, "Images/MarioSheet.png", position, FACING_RIGHT, true);
}

void GameScreen::CreateLuigi(Vector2D position)
{
	CharacterLuigi* luigi;
	luigi = new CharacterLuigi(mRenderer, "Images/LuigiSheet.png", position, FACING_LEFT, true);
}

void GameScreen::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* koopaCharacter;
	koopaCharacter = new CharacterKoopa(mRenderer, "Images/KoopaSheet.png", position, direction, true, speed);
	mKoopas.push_back(koopaCharacter);
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
