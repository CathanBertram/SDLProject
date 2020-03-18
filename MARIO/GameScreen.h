#pragma once
#include "Main.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Collisions.h"
#include "Coin.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "PowBlock.h"

class Tile;
class TileMap;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	GameScreen(SDL_Renderer* renderer, std::string filePath);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	bool CheckMapColl(Character* obj);
	bool CheckMapCollV2(Character* obj);
	bool CheckMapCollLR(Character* obj);
	bool CheckMapCollLeft(Character* obj, float deltaTime);
	bool CheckMapCollRight(Character* obj, float deltaTime);
	bool CheckMapCollUp(Character* obj);
	bool CheckMapCollDown(Character* obj);
	void ObjectCollChecks(Character* obj, float deltaTime);

	vector<vector<Tile*> > tileMap;
	TileMap* map;


	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreatePowBlock(Vector2D position);
	void CreateCoin(Vector2D position);

protected:
	SDL_Renderer* mRenderer;
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	void DoScreenshake();
	void ShakeScreen(float deltaTime);

	CharacterMario* mario;
	CharacterLuigi* luigi;
	vector<CharacterKoopa*> mKoopas;
	vector<Coin*> mCoins;
	vector<PowBlock*> mPowBlock;
};

