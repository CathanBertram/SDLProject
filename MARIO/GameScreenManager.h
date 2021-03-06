#pragma once
#include <SDL.h>
#include"Commons.h"
#include "GameScreen.h"
#include "GameScreenIntro.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenWin.h"
#include "TileMap.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS newScreen);
	SCREENS GetCurrentScreen() { return currentScreen; }

private:
	SCREENS currentScreen;
	SDL_Renderer* mRenderer;
	GameScreen* mCurrentScreen;
	GameScreenIntro* tempScreenIntro;
	GameScreenLevel1* tempScreenL1;
	GameScreenLevel2* tempScreenL2;
	GameScreenWin* tempScreenWin;
};

