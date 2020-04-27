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
#include "QuestionBlock.h"
#include "Flag.h"
#include "GameOver.h"

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

	bool levelOver;

	vector<vector<Tile*> > tileMap;
	TileMap* map;

protected:
	SDL_Renderer* mRenderer;
	bool mScreenshake;
	bool gameEnd;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;


	void DoScreenshake();
	void ShakeScreen(float deltaTime);

	CharacterMario* mario;
	CharacterLuigi* luigi;
	Flag* flag;
	GameOver* gameOver;
	vector<CharacterKoopa*> mKoopas;
	vector<Coin*> mCoins;
	vector<PowBlock*> mPowBlock;
	vector<QuestionBlock*> mQuestionBlock;

	void SetUpLevel();

	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreatePowBlock(Vector2D position);
	void CreateCoin(Vector2D position, bool gravity);
	void CreateQuestion(Vector2D position);
	void CreateGameOver();

	void UpdatePowBlock(float deltaTime);
	void UpdateEnemies(float deltaTime, SDL_Event e);

};

