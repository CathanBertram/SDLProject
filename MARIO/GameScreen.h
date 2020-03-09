#pragma once
#include "Main.h"
#include "TileMap.h"
#include "GameObject.h"
#include "Collisions.h"

class Tile;
class TileMap;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	bool CheckMapColl(GameObject* obj);

	vector<Tile*> tileMap;
	TileMap* map;

protected:
	SDL_Renderer* mRenderer;
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;

	void DoScreenshake();
	void ShakeScreen(float deltaTime);
};

