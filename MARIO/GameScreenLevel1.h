#pragma once
#include <SDL.h>
#include <vector>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "Character.h"
#include "CharacterLuigi.h"
#include "CharacterMario.h"
#include "CharacterKoopa.h"
#include "Collisions.h"
#include "LevelMap.h"
#include "Coin.h"

class Character;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void UpdatePowBlock(float deltaTime);
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
private:
	Texture2D* mBackgroundTexture;
	CharacterMario* mario;	
	CharacterLuigi* luigi;
	vector<CharacterKoopa*> mKoopas;
	vector<Coin*> mCoins;

	Vector2D mPos;
	Vector2D lPos;
	bool SetUpLevel();
	void SetLevelMap();
	LevelMap* mLevelMap;
	PowBlock* mPowBlock;
};

