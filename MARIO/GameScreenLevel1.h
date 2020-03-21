#pragma once
#include <SDL.h>
#include <vector>
#include "Commons.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "Collisions.h"
#include "LevelMap.h"


class Character;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer, std::string filePath);
	~GameScreenLevel1();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
	Texture2D* mBackgroundTexture;

	Vector2D mPos;
	Vector2D lPos;
	bool SetUpLevel();
};

