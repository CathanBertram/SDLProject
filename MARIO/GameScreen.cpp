#include <sstream>
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

	//Create Characters
	mario = new CharacterMario(mRenderer, "Images/MarioSheet.png", map->GetMarioPos(), FACING_RIGHT, true);
	luigi = new CharacterLuigi(mRenderer, "Images/LuigiSheet.png", map->GetLuigiPos(), FACING_RIGHT, true);
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
	for (int i = 0; i < map->GetLevelHeight(); i++)
	{
		for (int j = 0; j < map->GetLevelWidth(); j++)
		{
			std::cout << map->GetTileAt(i, j);
		}
		std::cout << std::endl;
	}
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
}

bool GameScreen::CheckMapColl(Character* obj)
{
	if (map != NULL)
	{
		for (int i = 0; i < map->tileMap.size(); i++)
		{
			for (int j = 0; j < map->tileMap[i].size(); j++)
			{
				if (map->tileMap[i][j]->collidable == true)
				{
					if (Collisions::Instance()->Box(obj->GetCollisionBox(), map->tileMap[i][j]->GetCollisionBox()))
					{
						return true;
					}
				}

			}
		}
		return false;
	}
	return false;
}

bool GameScreen::CheckMapCollV2(Character* obj)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, obj->GetPosition().x / TILE_WIDTH) == true || //Left
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth()) / TILE_WIDTH) == true || //Right
			map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true || //Top
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight()) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true) //Bottom
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool GameScreen::CheckMapCollLR(Character* obj)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, obj->GetPosition().x / TILE_WIDTH) == true || //Left
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth()) / TILE_WIDTH) == true) //Right
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool GameScreen::CheckMapCollLeft(Character* obj, float deltaTime)
{
	if (map != NULL)
	{
		if (map->GetTileAt(obj->GetPosition().y + (obj->GetSingleHeight() / 2)/ TILE_HEIGHT, obj->CheckLeftMovement(deltaTime).x / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool GameScreen::CheckMapCollRight(Character* obj, float deltaTime)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, (obj->CheckRightMovement(deltaTime).x + obj->GetSingleWidth()) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool GameScreen::CheckMapCollUp(Character* obj)
{
	if (map != NULL)
	{
		if (map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool GameScreen::CheckMapCollDown(Character* obj)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight()) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

void GameScreen::ObjectCollChecks(Character* obj, float deltaTime)
{
	//Check Collision To The Left
	if (CheckMapCollLeft(obj, deltaTime) == true)
	{
		obj->DisableLeftMovement();
	}
	else
	{
		obj->EnableLeftMovement();
	}

	//Check Collision To The Right
	if (CheckMapCollRight(obj, deltaTime) == true)
	{
		obj->DisableRightMovement();
	}
	else
	{
		obj->EnableRightMovement();
	}

	//Check Collision Up
	if (CheckMapCollUp(obj) == true)
	{
		obj->CancelJump();
	}

	//Check Collision Down
	for (int i = 0; i < 10; i++)
	{
		if (CheckMapCollDown(obj) == true)
		{
			obj->EnableJump();
			break;
		}
		else
		{
			obj->AddGravity(deltaTime);
			obj->DisableJump();
		}
	}
}

void GameScreen::CreateCoin(Vector2D position)
{
	mCoins.push_back(new Coin(mRenderer, "Images/CoinSheet.png", position, false));
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
